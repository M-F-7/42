/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:17:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 15:01:40 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"
#include <sstream>

class JoinException : public StatusException
{
public:
	JoinException(std::string channelName, StatusCode status, std::string msg);
};

class BannedFromChanException : public JoinException
{
public:
	BannedFromChanException(std::string channelName);
};

class InviteOnlyChanException : public JoinException
{
public:
	InviteOnlyChanException(std::string channelName);
};

class ChanIsFullException : public JoinException
{
public:
	ChanIsFullException(std::string channelName);
};


class BadChanPassException: public JoinException{
public:
	BadChanPassException(std::string channelName);
};
