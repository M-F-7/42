/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandCap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:43:33 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 23:04:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandCap.hpp"

CommandCap::CommandCap(IUserRepositoryPort &userRepo, UseCases &uc) : _uc(uc), _userRepo(userRepo)
{
}

CommandCap::~CommandCap()
{
}

void CommandCap::execute(IRCMessage, unsigned long id)
{
    std::string msg;
    User &user = this->_userRepo.getOrCreate(id);
    msg = "NO CAP";
    this->_uc.informUser->execute(user, msg);
}
