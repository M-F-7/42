/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoSuchNickException.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:37:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 14:40:30 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NoSuchNickException.hpp"

NoSuchNickException::NoSuchNickException(std::string &nick)
{
	std::string msg = nick + " :No such nick/channel";
	this->setStatus(ERR_NOSUCHNICK);
	this->setMsg(msg);
};
