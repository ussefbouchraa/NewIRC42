/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:37:04 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 19:37:04 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

// ################################## CONNECTIONS

bool Bot::connectToServer() {
  _clientFdSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (_clientFdSocket < 0) {
    std::cerr << "Info: Error creating socket" << std::endl;
    return false;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(_port);
  if (inet_pton(AF_INET, _serverAddress.c_str(), &server.sin_addr) <= 0) {
    std::cerr << "Info: Invalid address" << std::endl;
    close(_clientFdSocket);
    return false;
  }

 if (connect(_clientFdSocket, (struct sockaddr *)&server, sizeof(server)) <
      0) {
    std::cerr << "Info: Connection failed" << std::endl;
    close(_clientFdSocket);
    return false;
  }

  return true;
}

void Bot::disconnectFromServer() {
  if (_clientFdSocket != -1) {
    close(_clientFdSocket);
    _clientFdSocket = -1;
    std::cout << "Info: Disconnecting from server" << std::endl;
  }
}

bool    Bot::registerBot() {
  sendMessageToServer("PASS " + _password + "\r\n");
  sendMessageToServer("NICK " + _nickname + "\r\n");
  sendMessageToServer("USER " + _username + " 0 * :" + _botName +
                      " IRC Bot\r\n");
  // if (!processServerResponse())
  //   return false;
  if (_autoJoinChannel == true) {
      std::cout << "Info: AutoJoin Active" << std::endl;
    joinChannel(_channelName);
  }
  return true;
}

int Bot::getClientFdSocket() const { return _clientFdSocket; }
int Bot::getPort() const { return _port; }
std::string Bot::getServerAddress() const { return _serverAddress; }
void Bot::setClientFdSocket(int clientFdSocket) {
  _clientFdSocket = clientFdSocket;
}
void Bot::setPort(int port) { _port = port; }
void Bot::setServerAddress(const std::string &serverAddress) {
  _serverAddress = serverAddress;
}
