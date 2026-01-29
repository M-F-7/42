/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:26:10 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 23:10:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandUser.hpp"

CommandUser::CommandUser(IUserRepositoryPort &userRepo, IPublisher &publisher) : _userRepo(userRepo), _publisher(publisher) {};
CommandUser::~CommandUser() {};

void CommandUser::execute(IRCMessage msg, unsigned long client_id)
{

    User &currUser = this->_userRepo.getOrCreate(client_id);
    Response response(currUser);

    if (!currUser.getUserName().empty())
        throw AlreadyRegisteredException();

    currUser.setUserName(msg.params[0]);
    currUser.setIsLogIdentified();
    if (currUser.getIsLog() != User::IDENTIFIED)
        return;
    this->_sendWelcome(response);
}

void CommandUser::_sendWelcome(Response &res)
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
