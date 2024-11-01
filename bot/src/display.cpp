/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:08:24 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 23:08:24 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

void Bot::DisplayBotInfo() {
  std::cout << "#############  BotInfo   #####################" << std::endl;
  std::cout << "Server address: " << _serverAddress << std::endl;
  std::cout << "Port: " << _port << std::endl;
  std::cout << "Password: " << _password << std::endl;
  std::cout << "Bot name: " << _botName << std::endl;
  std::cout << "Auto-join Channel name: " << _channelName << std::endl;
  std::cout << "Nickname: " << _nickname << std::endl;
  std::cout << "##############################################" << std::endl;
}

void Bot::help(const std::string &id) {
  std::cout << "in help" << std::endl;
  if (isMaster(id) ){
    messageUser(id, "<--BotCommands--> ");
    messageUser(id, "<help> [user/channel]> Display this help message");
    messageUser(id, "<info> Display bot info");
    messageUser(id, "<unsub> remove user from masters");
    messageUser(id, "<sub> add user to masters");
    messageUser(id, "<uptime> Display bot uptime");
    messageUser(id, "<join> <channel> Join a channel");
    messageUser(id, "<whisper> <user> <message> Send an anonimous message to a user");
  }
  else {
    messageChannel(id, "You do not have permission to use this command");
  }
}

void Bot::info(const std::string &id) {
  if (isUser(id) && isMaster(id)) {
    messageUser(id, "BotInfo> ");
    messageUser(id, "Server address> " + _serverAddress);
    messageUser(id, "Port> " + std::to_string(_port));
    messageUser(id, "Password> " + _password);
    messageUser(id, "Bot name> " + _botName);
  } else {
    messageChannel(id, "You do not have permission to use this command");
  }
}
