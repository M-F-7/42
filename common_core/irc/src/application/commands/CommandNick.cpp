/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:53:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 23:11:03 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandNick.hpp"
#include "StatusCode.hpp"
#include "StatusException.hpp"
#include "exceptions/NickException.hpp"

CommandNick::CommandNick(IUserRepositoryPort &userRepo, IPublisher &publisher) : _userRepo(userRepo), _publisher(publisher) {};
CommandNick::~CommandNick() {};

void CommandNick::execute(IRCMessage msg, unsigned long client_id)
{
    const User *existingUser = this->_userRepo.getByNickName(msg.params[0]);
    User &currentUser = this->_userRepo.getOrCreate(client_id);
    Response response(currentUser);

    if (existingUser)
        throw NickNameAlreadyUsedException(msg.params[0]);
    if (currentUser.getNickName().empty() && currentUser.getUserName().empty())
        response.setMsg(_formatMessage(currentUser, msg.params[0]));
    else if (currentUser.getUserName().empty())
        response.setMsg(_formatMessage(currentUser, currentUser.getNickName() + " changed his nickname to " + msg.params[0]));
    else if (currentUser.getNickName().empty())
    {
        currentUser.setNickName(msg.params[0]);
        currentUser.setIsLogIdentified();

        return this->_sendWelcome(response);
    }
    else
        response.setMsg(_formatMessage(currentUser, currentUser.getNickName() + " changed his nickname to " + msg.params[0]));
    currentUser.setNickName(msg.params[0]);
    currentUser.setIsLogIdentified();

    this->_publisher.publish(response);
}

std::string CommandNick::_formatMessage(User &user, std::string newNick)
{
    std::string msg;

    if (user.getNickName().empty())
        msg += "*!";
    else
        msg += user.getNickName() + "!";
    if (user.getUserName().empty())
        msg += "*@" + ServerConfig::getHost();
    else
        msg += user.getUserName() + "@" + ServerConfig::getHost();
    msg += " NICK :" + newNick;
    return msg;
}

// std::string CommandNick::_formatWelcomeMessage(User &user, std::string newNick)
// {
// 	std::string msg = "Welcome to the IRC 42 ";

// 	msg += newNick + "!" + user.getUserName() + "@" + ServerConfig::getHost();
// 	return msg;
// }

void CommandNick::_sendWelcome(Response &res)
{
    std::string msg;

    res.setStatusCode(RPL_WELCOME);
    msg += res.getTarget().getNickName();
    msg += " :Welcome to the Internet Relay Chat ";
    msg += res.getTarget().getNickName() + "!" + res.getTarget().getUserName() + "@" + ServerConfig::getHost();
    res.setMsg(msg);

    this->_publisher.publish(res);

    res.setStatusCode(RPL_YOURHOST);
    msg.clear();
    msg += res.getTarget().getNickName();
    msg += " :Your host is ";
    msg += ServerConfig::getHost();
    msg += ", running version 1.0";
    res.setMsg(msg);
    this->_publisher.publish(res);

    res.setStatusCode(RPL_CREATED);
    msg.clear();
    msg += res.getTarget().getNickName();
    msg += " :This server was created on ";
    msg += ServerConfig::getStartupTime();
    res.setMsg(msg);
    this->_publisher.publish(res);

    res.setStatusCode(RPL_MYINFO);
    msg.clear();
    msg += res.getTarget().getNickName();
    msg += " :1.0 o o";
    res.setMsg(msg);
    this->_publisher.publish(res);
}
