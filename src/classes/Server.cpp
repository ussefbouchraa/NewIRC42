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

// Default constructor
Server::Server() : _port(0), _passWord(""), _serverRunning(false) {}

// Parameterized constructor
Server::Server(std::string port, std::string password)
    : _passWord(password), _serverRunning(false) {
  _port = static_cast<uint16_t>(std::stoi(port));
}

// Copy constructor
Server::Server(const Server &obj)
    : _port(obj._port), _passWord(obj._passWord), _fds(obj._fds),
      _clients(obj._clients), _channels(obj._channels) {}

// Assignment operator
Server &Server::operator=(const Server &obj) {
  if (this != &obj) {
    _port = obj._port;
    _passWord = obj._passWord;
    _fds = obj._fds;
    _clients = obj._clients;
    _channels = obj._channels;
  }
  return *this;
}

// Destructor
Server::~Server() { shutdownServer(); }

// Initialize the server and start listening for connections
bool Server::initializeServer() {
  try {
    if (!setupSocket())
      throw std::runtime_error("Failed to set up server socket.");
    if (!startListening())
      throw std::runtime_error("Failed to start listening on socket.");
    _serverRunning = true;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
}

// Set up the socket for the server
bool Server::setupSocket() {
  int serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    std::cerr << "Error creating socket." << std::endl;
    return false;
  }

  sockaddr_in serverAddress;
  std::memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(_port);

  if (bind(serverFd, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
    std::cerr << "Error binding socket to address." << std::endl;
    close(serverFd);
    return false;
  }

  pollfd serverPollFd;
  serverPollFd.fd = serverFd;
  serverPollFd.events = POLLIN;
  _fds.push_back(serverPollFd);

  return true;
}

// Start listening for client connections
bool Server::startListening() {
  if (listen(_fds[0].fd, SOMAXCONN) < 0) {
    std::cerr << "Error in listen." << std::endl;
    return false;
  }
  std::cout << "Server listening on port " << _port << std::endl;
  return true;
}

// Handle incoming connections
void Server::handleConnections() {
  while (_serverRunning) {
    if (poll(_fds.data(), _fds.size(), -1) < 0) {
      std::cerr << "Error in poll." << std::endl;
      break;
    }

    for (size_t i = 0; i < _fds.size(); ++i) {
      if (_fds[i].revents & POLLIN) {
        if (i == 0) {
          acceptNewClient();
        } else {
          processClientMessage(_fds[i].fd);
        }
      }
    }
  }
}

// Accept a new client and add to pollfd list
void Server::acceptNewClient() {
  int clientFd = accept(_fds[0].fd, NULL, NULL);
  if (clientFd < 0) {
    std::cerr << "Error accepting new client." << std::endl;
    return;
  }

  pollfd clientPollFd;
  clientPollFd.fd = clientFd;
  clientPollFd.events = POLLIN;
  _fds.push_back(clientPollFd);

  _clients[clientFd] = Client(clientFd);
  std::cout << "Accepted new client with fd: " << clientFd << std::endl;
}

// Shut down server, close all connections, and clear resources
void Server::shutdownServer() {
  _serverRunning = false;
  for (size_t i = 0; i < _fds.size(); ++i) {
    close(_fds[i].fd);
  }
  _fds.clear();
  _clients.clear();
  _channels.clear();
  std::cout << "Server shutdown complete." << std::endl;
}

// Additional command handling functions (implement as needed)
void Server::handleJoinCommand(
    int clientIndex) { /* Implement JOIN command logic */ }
void Server::handleListCommand(
    int clientIndex) { /* Implement LIST command logic */ }
void Server::handlePartCommand(
    int clientIndex) { /* Implement PART command logic */ }
void Server::handleTopicCommand(
    int clientIndex) { /* Implement TOPIC command logic */ }
void Server::handlePrivmsgCommand(
    int clientIndex) { /* Implement PRIVMSG command logic */ }
void Server::handleInviteCommand(
    int clientIndex) { /* Implement INVITE command logic */ }
void Server::handleKickCommand(
    int clientIndex) { /* Implement KICK command logic */ }
void Server::handleModeCommand(
    int clientIndex) { /* Implement MODE command logic */ }
void Server::handleNickCommand(
    int clientIndex) { /* Implement NICK command logic */ }
void Server::handlePassCommand(
    int clientIndex) { /* Implement PASS command logic */ }
void Server::handleUserCommand(
    int clientIndex) { /* Implement USER command logic */ }
