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



//// ******** part 1



/// ********* part 2
void Server:: handleClientMessage(int i)
{
        if (this->authenticateUser(i))
        {
            switch (this->_clients[i].getMessage().getCommand())
            {
            case (JOIN):
                joinCommand(i);
                break;
            case (LIST):
                listCommand(i);
                break;
            case (PART):
                partCommand(i);
                break;
            case (TOPIC):
                topicCommand(i);
                break;
            case (PRIVMSG):
                privmsgCommand(i);
                break;
            case (INVITE):
                inviteCommand(i);
                break;
            case (KICK):
                kickCommand(i);
                break;
            case (MODE):
                modeCommand(i);
                break;
            case (NICK):
                nickCommand(i);
                break;
            case PASS: case USER: case PING: case PONG :case QUIT: break;
            default:
                this->_clients[i].sendMsg(ERR_UNKNOWNCOMMAND(_clients[i].getNickName()));
            }
        }
}

bool Server::authenticateUser(int i)
{

    if (this->_clients[i].getAuthenticate())
        return true;
    else if (this->_clients[i].getMessage().getCommand() == PASS)
        this->passCommand(i);
    else if (this->_clients[i].getMessage().getCommand() == NICK)
        this->nickCommand(i);
    else if (!this->_clients[i].getNickName().empty() && this->_clients[i].getMessage().getCommand() == USER)
        this->userCommand(i);
    else
        this->_clients[i].sendMsg(ERR_NOTREGISTERED("*"));

    return false;
}