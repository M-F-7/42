/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:33:24 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 10:58:53 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandPass.hpp"

CommandPass::CommandPass(IUserRepositoryPort &userRepo) : _userRepo(userRepo) {};
CommandPass::~CommandPass() {};

void CommandPass::execute(IRCMessage msg, unsigned long client_id)
{
	User &currUser = this->_userRepo.getOrCreate(client_id);
	if (currUser.getIsLog() == User::CONNECTED || currUser.getIsLog() == User::IDENTIFIED)
		throw AlreadyRegisteredException();
	if (msg.params[0] != ServerConfig::getPassword())
		throw StatusException(ERR_PASSWDMISMATCH, currUser.getNickName() + " :Password incorrect");
	currUser.setIsLogConnected();
}
