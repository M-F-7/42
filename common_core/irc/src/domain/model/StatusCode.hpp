/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:09:48 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 15:55:11 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum StatusCode
{
	NONE = 0,
	RPL_WELCOME = 1,
	RPL_YOURHOST = 2,
	RPL_CREATED = 3,
	RPL_MYINFO = 4,

	_PING = 5,
	_PONG = 6,

	RPL_CHANNELMODEIS = 324, // MODE
	RPL_UNIQOPIS = 325,		 // MODE
	RPL_NOTOPIC = 331,		 // TOPIC
	RPL_TOPIC = 332,		 // TOPIC

	RPL_INVITELIST = 346,		// MODE
	RPL_ENDOFINVITELIST = 347,	// MODE
	RPL_EXCEPTLIST = 348,		// MODE
	RPL_ENDOFEXCEPTLIST = 349,	// MODE
	RPL_BANLIST = 367,			// MODE
	RPL_ENDOFBANLIST = 368,		// MODE
	ERR_NOSUCHNICK = 401,		// PRIVMSG, NOTICE
	ERR_NOSUCHCHANNEL = 403,	// PART, KICK
	ERR_CANNOTSENDTOCHAN = 404, // PRIVMSG, NOTICE
	ERR_TOOMANYTARGETS = 407,	// PRIVMSG, NOTICE

	ERR_NORECIPIENT = 411, // PRIVMSG, NOTICE
	ERR_NOTEXTOSEND = 412, // PRIVMSG, NOTICE

	ERR_NONICKNAMEGIVEN = 431,	// nick   //moss
	ERR_ERRONEUSNICKNAME = 432, // nick
	ERR_NICKNAMEINUSE = 433,	// nick   //moss 1

	ERR_UNKNOWNCOMMAND = 421,

	ERR_USERNOTINCHANNEL = 441, // KICK
	ERR_NOTONCHANNEL = 442,		// KICK
	ERR_USERONCHANNEL = 443,	// INVITE

	ERR_NEEDMOREPARAMS = 461,	 // pass   //moss
	ERR_ALREADYREGISTERED = 462, // pass
	ERR_PASSWDMISMATCH = 464,	 // pass   //moss
	ERR_KEYSET = 467,			 // MODE

	ERR_CHANNELISFULL = 471,
	ERR_UNKNOWNMODE = 472,	  // MODE
	ERR_INVITEONLYCHAN = 473, // JOIN
	ERR_BANNEDFROMCHAN = 474, // JOIN
	ERR_BADCHANNELKEY = 475,  // JOIN

	ERR_NOCHANMODES = 477, // MODE  //moss pour topic

	ERR_CHANOPRIVSNEEDED = 482, // KICK,
};
