/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:17:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 01:35:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinException.hpp"

JoinException::JoinException(std::string channelName, StatusCode status,
							 std::string msg) : StatusException()
{
	std::ostringstream oss;
	oss << channelName << " :" << msg;
	this->setMsg(msg);
	this->setStatus(status);
};
BannedFromChanException::BannedFromChanException(std::string channelName) : JoinException(channelName,
																						  ERR_BANNEDFROMCHAN, "Cannot join channel because banned from it") {};
InviteOnlyChanException::InviteOnlyChanException(std::string channelName) : JoinException(channelName,
																						  ERR_INVITEONLYCHAN, "Cannot join channel (+i)") {};

ChanIsFullException::ChanIsFullException(std::string channelName) : JoinException(channelName,
																				  ERR_CHANNELISFULL, "Cannot join channel (+l)") {};

BadChanPassException::BadChanPassException(std::string channelName) : JoinException(channelName,
																					ERR_BADCHANNELKEY, "Cannot join channel (+k)") {};
