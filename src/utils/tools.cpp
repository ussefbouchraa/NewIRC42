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
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    return str;
}

std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}