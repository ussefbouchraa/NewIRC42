/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:12:04 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/10/30 16:12:04 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HPP
#define ENV_HPP

#include <iostream>
#include <string>
#include <system_error>
#include <vector>

enum state {
  INFO,
  DEBUG,

};

class env {
private:
  std::vector<std::string> args;

public:
  env(std::string line);
  env(std::string line, state mode);


  //class specific methodes
  bool  tokenize();
  bool init();

  //getters and setters


  std::vector<std::string>getArgs();

};

#endif
