/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:01:55 by ybouchra          #+#    #+#             */
/*   Updated: 2024/10/14 08:22:58 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../inc/Client.hpp"

Client::Client()
{
    this->_clientFdSocket = -1;
    this->_nbrchannels = 0;
    this->_authenticate = false;
    this->_operStatus = false;
    this->_pass = false;
    this->_userName = "";
    this->_nickName = "";
    this->_IP = "";
}

Client::Client(const Client &obj)
{
    *this = obj;
}

Client &Client::operator=(const Client &obj)
{
    if (this != &obj)
    {
        this->_clientFdSocket = obj._clientFdSocket;
        this->_authenticate = obj._authenticate;
        this->_pass = obj._pass;
        this->_userName = obj._userName;
        this->_nickName = obj._nickName;
        this->_operStatus = obj._operStatus;
        this->_IP = obj._IP;
        this->_nbrchannels = obj._nbrchannels;
        this->_msg = obj._msg;
        this->stream = obj.stream;
    }
    return *this;
}

Client::~Client()
{
    this->_userName.clear();
    this->_nickName.clear();
    this->_IP.clear();
}

Client::Client(int clientFdSocket, bool authenticate) : _authenticate(authenticate)
{

    this->_userName = "";
    this->_nickName = "";
    this->_IP = "";
    this->_pass = false;
    this->_operStatus = false;
    this->_clientFdSocket = clientFdSocket;
    this->_nbrchannels = 0;
}

int Client::getClientFdSocket() const
{
    return this->_clientFdSocket;
}

bool Client::getAuthenticate() const
{
    return this->_authenticate;
}

std::string Client::getUserName() const
{
    return this->_userName;
}

std::string Client::getNickName() const
{
    return this->_nickName;
}

std::string Client::getIP() const
{
    return this->_IP;
}

Message &Client::getMessage()
{
    return this->_msg;
}

void Client::setClientFdSocket(int fd)
{
    this->_clientFdSocket = fd;
}

void Client::setAuthenticate(bool au)
{
    this->_authenticate = au;
}

void Client::setUserName(std::string userName)
{
    this->_userName = userName;
}

void Client::setNickName(std::string nickName)
{
    this->_nickName = nickName;
}

void Client::setIP(std::string IP)
{
    this->_IP = IP;
}

void Client::setMessage(Message msg)
{
    this->_msg.myAppend(msg);
}

void Client::setPass(bool b)
{
    this->_pass = b;
}


void Client::sendMsg(std::string str)
{
    stream += str;
}

bool Client::getPass() const
{
    return this->_pass;
}

int Client::getnbrChannels()
{
    return (this->_nbrchannels);
}
void Client::setnbrChannels(char sign)
{
    if (sign == '+')
        this->_nbrchannels++;
    else
        this->_nbrchannels--;
}

std::string Client::getTime() const
{
    std::time_t currentTime = std::time(0);
    std::tm *localTime = std::localtime(&currentTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%b %d, %Y at %I:%M %p", localTime);
    return std::string(buffer);
}

void Client::writeMessageToSocket()
    {
        while (!stream.empty()) {
            ssize_t n = send(this->_clientFdSocket, stream.c_str(), stream.size(), 0);
            
            if (n == -1) {
                std::cerr << "Failed to send message to client" << std::endl;
                break; 
            }
        
            if (n < (ssize_t)stream.size()) {
                stream.erase(0, n); 
            } else 
                stream.clear();
        }
    }

    void Client::consume_message(const std::string& s) 
    {
        this->_msg.consume_buffer(s);
    }