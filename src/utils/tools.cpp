/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:47:11 by ybouchra          #+#    #+#             */
/*   Updated: 2024/10/21 13:53:30 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
#include "Server.hpp"

void	printHeader()
{
	std::cout << "  __ _       _          " << std::endl;
	std::cout << " / _| |_    (_)_ __ ___ " << std::endl;
	std::cout << "| |_| __|   | | '__/ __|" << std::endl;
	std::cout << "|  _| |_    | | | | (__ " << std::endl;
	std::cout << "|_|  \\__|___|_|_|  \\___|" << std::endl;
	std::cout << "       |_____|          " << std::endl;
}

void	printUsage()
{
	std::cout << "Usage: ./ft_irc <port> <password>" << std::endl;
}

void printErrorAndExit(int errorCode)
{
	std::cerr << "Error: Code " << errorCode << " - " << "Invalid argument provided" << std::endl;
	exit(errorCode);
}

std::string trimFunc(std::string &str)
{
    if(str.empty())
        return "";
    std::size_t start = 0;
    while(str.size() > start && std::isspace(str[start]))
        start++;

    std::size_t end = str.size();
    while(end > start && std::isspace(str[end - 1]))
        end--;
    
    return str.substr(start, end - start) ;

}
std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> vec ;
    std::stringstream iss(str);
    std::string buff;

    if(str.empty())
        return vec;
    while (std::getline(iss, buff, delimiter)) {
        if(!buff.empty())
            vec.push_back(trimFunc(buff));
    }
    return vec;
}
std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

int stringToInt(const std::string& str) {
    std::stringstream ss(str);
    long long temp;  
    ss >> temp;

    if (ss.fail() || temp < std::numeric_limits<int>::min() || temp > std::numeric_limits<int>::max()) {
        return -1;
    }

    return static_cast<int>(temp);
}



Client *Server::getClientByNickName(std::string nick)
{
    for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->second.getNickName() == nick)
            return &it->second;
    }
    return NULL;
}

bool Server::checkUserName(std::string username)
{
    if(username.empty())
        return false;

    for (size_t i = 0; i < username.size(); ++i)
    {
        char c = username[i];
        if (!(isalpha(c) || isdigit(c) ))
            return false;
    }
    return true;
}

bool Server::checkNickName(std::string nickname)
{
        char c = nickname.at(0);
        if (!(isalpha(c)))
            return false;
    return true;
}

void Server::createChannel(std::string &channelname, std::string key)
{
    this->_channels.insert(std::make_pair(channelname, Channel(channelname, key)));
    if (!key.empty())
        this->_channels[channelname]._mode.requiredKey = true;

}

bool Server::findChannelName(std::string &channelName)
{
    if (this->_channels.empty() || channelName.empty())
        return (false);
    std::map<std::string, Channel>::iterator it = this->_channels.find(channelName);  
    return (it != this->_channels.end() );

}

bool Server::is_memberInChannel(std::string &channelName, Client cl)
{
    std::map<std::string, Client*>::iterator it = this->_channels[channelName]._clients.find(cl.getNickName());
    if (it != _channels[channelName]._clients.end() && it->first == cl.getNickName())
        return (true);
    return (false);
}

bool Server::isValidChannelKey(std::string &key)
{
    if (key.empty())
        return (false);
    if (key.size() < 4 || key.size() >= 32)
        return (false);
    for (size_t i = 0; key.size() > i; i++)
    {
        if (key[i] == ' ' || (key.at(i) >= 9 && key.at(i) <= 13))
            return (false);
    }
    return (true);
}


bool Server::isValidChannelName(std::string &channelName)
{
    if (channelName.empty())
        return (false);
    if (channelName.at(0) != '#')
        return (false);
    if (!(channelName.size() >= 2 && channelName.size() <= CHANNELNAMELEN))
        return (false);
    size_t pos = channelName.find_first_of(",:?*!@ ");
    if (pos != std::string::npos) {
        return (false);
    }
    return (true);
}



void Server::disconnect(Client &cl)
{
  if (cl.getAuthenticate())
    {
        for ( std::map<std::string, Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
        {
            std::string channelname = it->second.getChannelName();
            if (is_memberInChannel(channelname, cl) )
                (*it).second.removeClient(cl, -1);
        }
    } 
      std::cout << "Client disconnected:  " << cl.getIP() << std::endl;
}