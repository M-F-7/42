/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:45:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 16:29:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandPing.hpp"
#include "ServerConfig.hpp"

CommandPing::CommandPing(IUserRepositoryPort &userRepo, UseCases &usesCases)
    : _userRepo(userRepo), _usesCases(usesCases) {};

CommandPing::~CommandPing() {};

void CommandPing::execute(IRCMessage msg, unsigned long client_id)
{
    User &user = this->_userRepo.getOrCreate(client_id);
    Response res(user);
    res.setStatusCode(_PONG);
    res.setMsg("PONG :" + msg.params[0]);

    this->_usesCases.sendReponse->execute(res);
}