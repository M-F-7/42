/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CannotSendToChanException.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:37:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:09:53 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CannotSendToChanException.hpp"

CannotSendToChanException::CannotSendToChanException(std::string chan)
{
	std::string msg = chan + " :Cannot send to channel";
	this->setStatus(ERR_CANNOTSENDTOCHAN);
	this->setMsg(msg);
};
