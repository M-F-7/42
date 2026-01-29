/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:00 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/01 12:05:56 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandBot.hpp"

CommandBot::CommandBot(IUserRepositoryPort &userRepo, UseCases &uc) : _uc(uc), _userRepo(userRepo)
{
}

CommandBot::~CommandBot()
{
}

void CommandBot::execute(IRCMessage, unsigned long id)
{
    std::string msg;
    User &user = this->_userRepo.getOrCreate(id);
    if (rand() % 2)
        msg ="PILE";
    else
        msg = "FACE";
    this->_uc.informUser->execute(user, msg);
}