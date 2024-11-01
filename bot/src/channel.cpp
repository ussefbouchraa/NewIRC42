/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:24:50 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 23:24:50 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

// ################################## CHANNELS

void Bot::joinChannel(const std::string &channelName) {
  sendMessageToServer("JOIN " + channelName + "\r\n");
  _channelName = channelName;
}

void Bot::leaveChannel(const std::string &channelName) {
    sendMessageToServer("PART " + channelName + "\r\n");
}

void Bot::listChannels() { sendMessageToServer("LIST\r\n"); }

void Bot::setCurrentChannel(const std::string &channel) { _channelName = channel; }


