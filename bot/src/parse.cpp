/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:35:34 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 19:35:34 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parse.hpp"
#include "../inc/Bot.hpp"

void Bot::parseArgs(int argc, char **argv) {
  if (argc <= 3) {
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
      std::cout << "tldr : ./bot start" << std::endl;
      std::cout << "Usage: bot [OPTION...]" << std::endl;
      std::cout
          << " -C, --config-file=FILE     use this user configuration file"
          << std::endl;
      std::cout << " -d, --debug                 emit debugging messages"
                << std::endl;
      std::cout << " -D, --default               reset all options to their "
                   "default values"
                << std::endl;
      std::cout
          << " -v, --version               output version information and "
             "exit";
      std::cout << " -h, --help                  display this help and exit"
                << std::endl;

      exit(0);
    } else if (arg == "-v" || arg == "--version") {
      std::cout << "Bot version 1.1" << std::endl;
      exit(0);
    } else if (arg == "-d" || arg == "--debug") {
      _debug = true;
    } else if (arg == "-D" || arg == "--default") {
        _env = Env();
    } else if (arg == "-i" || arg == "--interactive") {
      std::cout << "Interactive mode" << std::endl;
    } else if (arg == "-C" || arg == "--config-file") {
      this->parseConfigFile(argv[2]);
    } else {
      std::cerr << "Unknown option" << std::endl;
      exit(1);
    }
  }
}

void Bot::handleServerAddr(const std::string &line) {
  _domainName = line.substr(line.find("=") + 2);
  _serverAddress = resolveIP(_domainName);
  if (_serverAddress.empty()) {
    if (_debug)
      std::cerr << "Error: Unable to resolve address" << std::endl;
  }
}

void Bot::parseConfigFile(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  int index = 0;
  while (std::getline(file, line)) {
    if (line[0] == '#' || line.empty())
      continue;
    else if (!handleConfigLine(line)) {
      std::cerr << "Warning: Can't Parse line at Index :" << index << std::endl;
    } else {
      std::cerr << "Warning: Unknown configuration option at line: " << line
                << std::endl;
    }
    index++;
  }
}

bool Bot::handleConfigLine(const std::string &line) {

}

// std::string Bot::loadMasters(const std::string &line) {
//   if (line.find("{ ") == std::string::npos ||
//       line.find(" }") == std::string::npos) {
//     return "";
//   }
//   std::string _masters = line.substr(line.find("{") + 1, line.find("}") -
//   1); _masters = _masters.substr(1, _masters.length() - 2); return
//   _masters;
// }

bool Bot::isMaster(const std::string &user) {
  // inplementation or vector list
  return true;
}

bool Bot::minimumAllowedArgs() {
  if (_serverAddress.empty() || _port == 0 || _password.empty() ||
      _botName.empty() || _channelName.empty() || _username.empty() ||
      _nickname.empty())
    return false;
  return true;
}
