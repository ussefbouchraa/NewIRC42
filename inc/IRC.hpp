/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:49:55 by ybouchra          #+#    #+#             */
/*   Updated: 2024/10/12 20:19:05 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <map>
#include <limits>
#include <vector>
#include <sstream>


enum commands
{
    PASS, // Used to set a password when connecting to the server.
    NICK, // Sets the user's nickname.
    USER, // Sets the username, hostname, servername, and realname of a user.
    JOIN, // Joins a channel or channels.
    PART, // Leaves a channel or channels.
    PRIVMSG, // Sends a message to a user or channel.
    NOTICE, // Sends a notice to a user or channel.
    TOPIC, // Sets the topic for a channel.
    AWAY, // Sets or unsets the user's away status.
    MODE, // Sets channel modes or user modes.
    QUIT, // Disconnects from the server.
    WHO, // Retrieves information about users matching a given mask.
    NAMES, // Retrieves a list of users in a channel.
    LIST, // Lists all channels on the server.
    INVITE, // Invites a user to join a channel.
    KICK, // Kicks a user from a channel.
    KILL, // Disconnects a user from the server.
    PING, // Checks if the server is still alive.
    PONG, // Responds to a PING message from the server.
    UNKNOWN
};

#define ES_GREEN "\033[32m"
#define ES_RESET "\033[0m"
#define TOPICLEN 390
#define USERLEN 17
#define NICKLEN 17
#define CHANNELNAMELEN 18
#define LIMITCHANNELS  11
#define	INVALID_ARGUMENT_ERROR 3
#define VALIDMODES "+-itlkopsnmrbveqfcCz"
#define SERVERNAME std::string(":ircserver")



void		                        printHeader();
void		                        printUsage();
void                                printErrorAndExit(int errorCode);

int                                 stringToInt(const std::string& str);
std::string                         intToString(int num);
std::string                         trimFunc(std::string& str);
std::vector<std::string>            splitString(const std::string& str, char delimiter);




#endif 


