/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:36:02 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/10/03 10:36:02 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HPP
#define ENV_HPP

#include <iostream>
#include <string>
#include <vector>

class Env {
private:
  std::string _serverAddress;
  std::string _domainName;
  int _port;
  int _clientFdSocket;

  std::string _username;
  std::string _botName;
  std::string _nickname;
  std::string _password;

  std::string _channelName;

  bool _autoJoinChannel;
  bool _debug;
  bool _useRuntime;

  std::vector<std::string> _channels;
  std::vector<std::string> _masters;

  void handleServerAddr(const std::string &line);
  void handlePort(const std::string &line);
  void handleBotName(const std::string &line);

  // getters and setters
  std::string getServerAddress() const;
  void setServerAddress(const std::string &serverAddress);
  std::string getDomainName() const;
  void setDomainName(const std::string &domainName);
  int getPort() const;
  void setPort(int port);
  int getClientFdSocket() const;
  void setClientFdSocket(int clientFdSocket);
  std::string getUsername() const;
  void setUsername(const std::string &username);
  std::string getBotName() const;
  void setBotName(const std::string &botName);
  std::string getNickname() const;
  void setNickname(const std::string &nickname);
  std::string getPassword() const;
  void setPassword(const std::string &password);
  std::string getChannelName() const;
  void setChannelName(const std::string &channelName);
  bool isAutoJoinChannel() const;
  void setAutoJoinChannel(bool autoJoinChannel);
  bool isDebug() const;
  void setDebug(bool debug);
  bool isUseRuntime() const;
  void setUseRuntime(bool useRuntime);

public:
  Env();
  void getSysUsername();
  std::string resolveIP(const std::string &hostname);
};

#endif
