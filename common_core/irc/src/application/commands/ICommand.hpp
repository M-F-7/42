/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:11:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/01 11:57:44 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "CommandType.hpp"
#include "Parser.hpp"
#include "AlreadyRegisteredException.hpp"
#include "NeedMoreParamsException.hpp"
#include "JoinException.hpp"
#include "NoSuchChannelException.hpp"
#include "NotOnChannelException.hpp"
#include "ChanOperatorNeededException.hpp"
#include "UserNotInChannelException.hpp"
#include "CannotSendToChanException.hpp"
#include "NoSuchNickException.hpp"
#include "UseCases.hpp"

class ICommand
{
public:
	virtual void execute(IRCMessage msg, unsigned long client_id) = 0;
	virtual ~ICommand() {};
};
