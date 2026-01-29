/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoSuchChannelException.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:51:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 17:03:41 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NoSuchChannelException.hpp"

NoSuchChannelException::NoSuchChannelException(std::string chan) : StatusException()
{
	std::string msg = chan;

	msg += " :No such channel";
	this->setStatus(ERR_NOSUCHCHANNEL);
	this->setMsg(msg);
}
