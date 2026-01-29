/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:13:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/13 20:30:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IPublisher.hpp"
#include "PassException.hpp"
#include "ServerConfig.hpp"
#include "User.hpp"

class CommandPass : public ICommand
{

private:
	IUserRepositoryPort &_userRepo;

public:
	CommandPass(IUserRepositoryPort &userRepo);
	~CommandPass();

	void execute(IRCMessage msg, unsigned long client_id);
};
