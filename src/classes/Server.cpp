#include "../../inc/Server.hpp"

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "replies.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

Server::Server(int port, const std::string &password)
    : _port(port), _passWord(password), _running(false)
{
}

Server::~Server()
{
    // Clean up resources
}

void Server::start()
{
    int server_fd = createSocket();
    bindSocket(server_fd);
    listenOnSocket(server_fd);

    _running = true;
    std::cout << "Server started on port " << _port << std::endl;

    struct pollfd fds[200];
    int nfds = 1;
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;

    while (_running)
    {
        int poll_count = poll(fds, nfds, -1);
        if (poll_count < 0)
        {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nfds; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == server_fd)
                {
                    int new_socket = acceptConnection(server_fd);
                    fds[nfds].fd = new_socket;
                    fds[nfds].events = POLLIN;
                    nfds++;

                    handleNewConnection(new_socket);
                }
                else
                {
                    handleClientMessage(fds[i].fd);
                }
            }
        }
    }
}

int Server::createSocket()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void Server::bindSocket(int server_fd)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Server::listenOnSocket(int server_fd)
{
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int Server::acceptConnection(int server_fd)
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return new_socket;
}

void Server::handleNewConnection(int new_socket)
{
    // Add new client to the clients map
    _clients[new_socket] = Client(new_socket, false);
    std::cout << "New connection established" << std::endl;
}

void Server::stop()
{
    _running = false;
    std::cout << "Server stopped." << std::endl;
}

void Server::handleClientMessage(Client &client, const std::string &message)
{
    // Code to handle messages from clients
}

void Server::sendMessageToClient(Client &client, const std::string &message)
{
    client.sendMsg(message);
}

void Server::broadcastMessage(const std::string &message)
{
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        sendMessageToClient(it->second, message);
    }
}

Client *Server::getClientByNickName(const std::string &nick)
{
    for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->second.getNickName() == nick)
            return &it->second;
    }
    return NULL;
}

bool Server::checkUserName(const std::string &username)
{
    if (username.empty())
        return false;
    for (size_t i = 0; i < username.size(); ++i)
    {
        char c = username[i];
        if (!std::isalnum(c) && c != '_')
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

void Server::createChannel(std::string &channelName, std::string key)
{
    this->_channels.insert(std::make_pair(channelName, Channel(channelName, key)));
    if (!key.empty())
        this->_channels[channelName]._mode.requiredKey = true;
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

void Server::handleClientMessage(int i)
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
        case PASS:
        case USER:
        case PING:
        case PONG:
        case QUIT:
            break;
        default:
            this->_clients[i].sendMsg(ERR_UNKNOWNCOMMAND(_clients[i].getNickName()));
        }
    }
}