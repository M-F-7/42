/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserNotInChannelException.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:33:20 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/02 23:43:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserNotInChannelException.hpp"

UserNotInChannelException::UserNotInChannelException(std::string &nick, std::string chan) : StatusException()
{
	std::string msg = nick;

	msg += " :He is not in this channel: " + chan;
	this->setStatus(ERR_USERNOTINCHANNEL);
	this->setMsg(msg);
}
