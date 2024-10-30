

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <map>
#include <vector>
#include <poll.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

// enum CommandType {
//     JOIN,
//     LIST,
//     PART,
//     TOPIC,
//     PRIVMSG,
//     INVITE,
//     KICK,
//     MODE,
//     NICK,
//     PASS,
//     USER,
//     PING,
//     PONG,
//     QUIT,
//     UNKNOWN
// };

class Server {
private:
    uint16_t _port;
    std::string _password;
    std::vector<pollfd> _fds;
    std::map<int, Client> _clients;
    std::map<std::string, Channel> _channels;
    std::map<commands, void (Server::*)(int)> _commandDispatcher;

    // Private helper methods for command handling
    void initializeCommandDispatcher();
    bool authenticateClient(int clientIndex);
    void addClient(int fd, const Client &client);
    void removeClient(int clientIndex);
    void broadcastToChannel(const std::string &channelName, const std::string &message, const Client &sender);
    void processIncomingMessage(int clientIndex);
    void disconnectClient(int clientIndex);
    bool isNicknameInUse(const std::string &nickname) const;
    Channel &getOrCreateChannel(const std::string &channelName);
    void removeChannelIfEmpty(const std::string &channelName);

    // Command handling methods
    void handleJoinCommand(int clientIndex);
    void handleListCommand(int clientIndex);
    void handlePartCommand(int clientIndex);
    void handleTopicCommand(int clientIndex);
    void handlePrivmsgCommand(int clientIndex);
    void handleInviteCommand(int clientIndex);
    void handleKickCommand(int clientIndex);
    void handleModeCommand(int clientIndex);
    void handleNickCommand(int clientIndex);
    void handlePassCommand(int clientIndex);
    void handleUserCommand(int clientIndex);
    void handlePingCommand(int clientIndex);
    void handlePongCommand(int clientIndex);
    void handleQuitCommand(int clientIndex);

public:
    Server(uint16_t port, const std::string &password);
    Server(const Server &other);
    Server &operator=(const Server &other);
    ~Server();

    // Public methods for server operations
    void start();
    void stop();
    void acceptNewConnection(int listenerFd);
    void handleClientActivity(int clientFd);
};

#endif // SERVER_HPP

