/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:46:37 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/10/03 10:46:37 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env.hpp"
#include <unistd.h>

void Env::getSysUsername() {
  char *username = getlogin();
  if (username == NULL) {
    _username = "unknown";
  }
}

Env::Env() {
  _domainName = "localhost";
  _port = 6667;
  _clientFdSocket = 0;
  getSysUsername();
  _botName = "botname";
  _nickname = "botnick";
}
