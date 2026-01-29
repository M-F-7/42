/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotOnChannelException.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:51:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 17:20:37 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NotOnChannelException.hpp"

NotOnChannelException::NotOnChannelException(std::string chan) : StatusException()
{
	std::string msg = chan;

	msg += " :You're not on that channel";
	this->setStatus(ERR_NOTONCHANNEL);
	this->setMsg(msg);
}
