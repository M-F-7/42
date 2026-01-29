/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandType.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:30:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 17:36:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>

enum CommandType
{
	NICK,	 //  				OKK
	JOIN,	 //  				OKK
	KICK,	 //  				OKK
	PASS,	 //  				OKK
	PART,	 //  				OKK
	USER,	 //  				OKK
	QUIT,	 //					OKK
	PRIVMSG, //					OKK
	NOTICE,	 //				OKK
	TOPIC,	 //				OKK
	INVITE,
	MODE,
	CAP,
	PING,
	BOT,
	UNKNOWN
};

inline const char *commandTypeToString(CommandType type)
{
	switch (type)
	{
	case NICK:
		return "NICK";
	case JOIN:
		return "JOIN";
	case USER:
		return "USER";
	case PASS:
		return "PASS";
	case KICK:
		return "KICK";
	case PART:
		return "PART";
	case QUIT:
		return "QUIT";
	case PRIVMSG:
		return "PRIVMSG";
	case TOPIC:
		return "TOPIC";
	case INVITE:
		return "INVITE";
	case NOTICE:
		return "NOTICE";
	case MODE:
		return "MODE";
	case BOT:
		return "BOT";
	case PING:
		return "PING";
	case CAP:
		return "CAP";
	default:
		throw std::runtime_error("[commandTypeToString] Command Unknown!");
	}
}
