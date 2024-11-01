/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:52 by ybouchra          #+#    #+#             */
/*   Updated: 2024/10/12 20:05:36 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/IRC.hpp"
#include "../inc/Server.hpp"


int main(int argc, char const *argv[])
{
	if (argc != 3 )
	{
		printUsage();
		printErrorAndExit(INVALID_ARGUMENT_ERROR);
	}
	else
	{
		printHeader();
		
		std::cout <<  ES_GREEN << std::endl;
		
		std::cout << "<< ----- ft_irc ----- >>\n"  << std::endl;
		std::cout << "Port: " << argv[1] << std::endl;
		std::cout <<  "Pass: " << argv[2] <<  std::endl;
		
		std::cout << ES_RESET << std::endl;
			
		int port = std::stoi(argv[1]);
		Server test(port, argv[2]);
		test.start();
	}
	
	


	return 0;
}