/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:14 by ybouchra          #+#    #+#             */
/*   Updated: 2024/10/21 13:58:57 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include <arpa/inet.h> // For sockaddr_in and htons
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unistd.h> // For close()

#include "../../inc/Server.hpp"
#include <iostream>
#include <sstream)>
#include <stdexcept>

Server::Server(std::string port, const std::string &password)
    : _port(port), _password(password) {
  // handle string port
  initializeCommandDispatcher();
  std::cout << "Server initialized on port " << port
            << " with provided password.\n";
}

Server::Server(const Server &other)
    : _port(other._port), _password(other._password), _clients(other._clients),
      _channels(other._channels) {
  initializeCommandDispatcher();
}

// Assignment operator
Server &Server::operator=(const Server &other) {
  if (this != &other) {
    _port = other._port;
    _password = other._password;
    _clients = other._clients;
    _channels = other._channels;
    initializeCommandDispatcher();
  }
  return *this;
}

// Destructor
Server::~Server() {
  for (std::map<int, Client>::iterator it = _clients.begin();
       it != _clients.end(); ++it) {
    close(it->second.getClientFdSocket());
  }
  std::cout << "Server shutdown, all clients disconnected.\n";
}

// Initializes the command dispatcher
void Server::initializeCommandDispatcher() {
  _commandDispatcher[JOIN] = &Server::handleJoinCommand;
  _commandDispatcher[LIST] = &Server::handleListCommand;
  _commandDispatcher[PART] = &Server::handlePartCommand;
  _commandDispatcher[TOPIC] = &Server::handleTopicCommand;
  _commandDispatcher[PRIVMSG] = &Server::handlePrivmsgCommand;
  _commandDispatcher[INVITE] = &Server::handleInviteCommand;
  _commandDispatcher[KICK] = &Server::handleKickCommand;
  _commandDispatcher[MODE] = &Server::handleModeCommand;
  _commandDispatcher[NICK] = &Server::handleNickCommand;
  _commandDispatcher[PASS] = &Server::handlePassCommand;
  _commandDispatcher[USER] = &Server::handleUserCommand;
  _commandDispatcher[PING] = &Server::handlePingCommand;
  _commandDispatcher[PONG] = &Server::handlePongCommand;
  _commandDispatcher[QUIT] = &Server::handleQuitCommand;
}

bool Server::authenticateClient(int clientIndex) {
  Client &client = _clients[clientIndex];
  if (client.getAuthenticate()) {
    return true;
  }

  commands command = client.getMessage().getCommand();
  if (command == PASS && client.getMessage().getToken() == _password) {
    client.setAuthenticate(true);
    client.sendMsg("Password accepted.");
    return true;
  }

  client.sendMsg("Error: Authentication required. Use PASS command.");
  return false;
}

// Adds a client to the server
void Server::addClient(int fd, const Client &client) {
  if (_clients.find(fd) != _clients.end()) {
    throw std::runtime_error("Client with this FD already exists.");
  }

  _clients[fd] = client;
  pollfd newPollFd = {fd, POLLIN, 0};
  _fds.push_back(newPollFd);
  std::cout << "Client added with FD: " << fd << "\n";
}

// Removes a client from the server
void Server::removeClient(int clientIndex) {
  Client &client = _clients[clientIndex];
  disconnectClient(clientIndex);
  std::cout << "Client with FD " << client.getFd() << " removed.\n";
}

void Server::broadcastToChannel(const std::string &channelName,
                                const std::string &message,
                                const Client &sender) {
  if (_channels.find(channelName) == _channels.end()) {
    throw std::runtime_error("Channel does not exist.");
  }

  Channel &channel = _channels[channelName];
  channel.broadcastMessage(sender.getNickName() + ": " + message, sender);
}

// Processes incoming messages and dispatches commands
void Server::processIncomingMessage(int clientIndex) {
  Client &client = _clients[clientIndex];

  if (!authenticateClient(clientIndex)) {
    return;
  }

  CommandType command = client.getMessage().getCommand();
  if (_commandDispatcher.find(command) != _commandDispatcher.end()) {
    (this->*_commandDispatcher[command])(clientIndex);
  } else {
    client.sendMsg("Error: Unknown command.");
  }
}

// Disconnects a client and closes their connection
void Server::disconnectClient(int clientIndex) {
  Client &client = _clients[clientIndex];
  close(client.getFd());

  for (std::map<std::string, Channel>::iterator it = _channels.begin();
       it != _channels.end(); ++it) {
    it->second.removeClient(client);
  }

  _clients.erase(clientIndex);
  std::cout << "Client with FD " << client.getFd() << " disconnected.\n";
}

// Checks if a nickname is already in use
bool Server::isNicknameInUse(const std::string &nickname) const {
  for (std::map<int, Client>::const_iterator it = _clients.begin();
       it != _clients.end(); ++it) {
    if (it->second.getNickName() == nickname) {
      return true;
    }
  }
  return false;
}

// Adds a new channel if it doesn't exist
Channel &Server::getOrCreateChannel(const std::string &channelName) {
  if (_channels.find(channelName) == _channels.end()) {
    _channels[channelName] = Channel(channelName);
  }
  return _channels[channelName];
}

// Removes a channel if it's empty
void Server::removeChannelIfEmpty(const std::string &channelName) {
  std::map<std::string, Channel>::iterator it = _channels.find(channelName);
  if (it != _channels.end() && it->second.getClientCount() == 0) {
    _channels.erase(it);
    std::cout << "Channel " << channelName << " removed (empty).\n";
  }
}
