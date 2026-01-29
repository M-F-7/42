/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IParser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moss <moss@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:30:46 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 11:51:58 by moss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "IRCMessage.hpp"

class IParser
{
public:
	virtual ~IParser() {}
	virtual IRCMessage parseMessage(const std::string &line) = 0;
};
