/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserNotInChannelException.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:32:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 17:36:05 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"


class UserNotInChannelException : public StatusException
{
public:
	UserNotInChannelException(std::string& nick, std::string channel);
};
