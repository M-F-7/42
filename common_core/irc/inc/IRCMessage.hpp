/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:35:52 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 09:36:19 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "CommandType.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "CommandType.hpp"

struct IRCMessage
{
	std::string prefix;
	CommandType command;
	std::vector<std::string> params;
	std::vector<std::string> trailing;
	std::string reason;
};
