/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NeedMoreParamsException.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:51:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 09:56:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NeedMoreParamsException.hpp"

NeedMoreParamsException::NeedMoreParamsException(CommandType cmd) : StatusException()
{
	std::string msg = commandTypeToString(cmd);

	msg += " :Not enough parameters";
	this->setStatus(ERR_NEEDMOREPARAMS);
	this->setMsg(msg);
}
