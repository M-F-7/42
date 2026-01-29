/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChanOperatorNeededException.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:33:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 20:24:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChanOperatorNeededException.hpp"

ChanOperatorNeededException::ChanOperatorNeededException(std::string channelName) : StatusException()
{
	std::string msg = channelName;

	msg += " :You're not channel operator";
	this->setStatus(ERR_CHANOPRIVSNEEDED);
	this->setMsg(msg);
}
