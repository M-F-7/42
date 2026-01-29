/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:37:15 by rwassim           #+#    #+#             */
/*   Updated: 2025/10/02 10:37:15 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"

bool Parser::commandRequiresParams(const std::string &command) const
{
    static const std::string commandNeedingParams[] = {
        "PASS", "NICK", "USER", "JOIN", "PRIVMSG", "NOTICE", "KICK",
        "INVITE", "TOPIC", "MODE", "PART", "PING"};

    for (size_t i = 0; i < sizeof(commandNeedingParams) / sizeof(commandNeedingParams[0]); ++i)
    {
        if (command == commandNeedingParams[i])
            return true;
    }
    return false;
}

CommandType Parser::stringToCommandType(const std::string &command)
{
    if (command == "NICK")
        return NICK;
    if (command == "JOIN")
        return JOIN;
    if (command == "KICK")
        return KICK;
    if (command == "PASS")
        return PASS;
    if (command == "USER")
        return USER;
    if (command == "QUIT")
        return QUIT;
    if (command == "PRIVMSG")
        return PRIVMSG;
    if (command == "NOTICE")
        return NOTICE;
    if (command == "TOPIC")
        return TOPIC;
    if (command == "INVITE")
        return INVITE;
    if (command == "MODE")
        return MODE;
    if (command == "PART")
        return PART;
    if (command == "CAP")
        return CAP;
    if (command == "BOT")
        return BOT;
    if (command == "PING")
        return PING;
    // if ()

    throw std::invalid_argument("Unknown command: " + command);
}

std::string Parser::commandTypeToString(CommandType type)
{
    switch (type)
    {
    case NICK:
        return "NICK";
    case JOIN:
        return "JOIN";
    case KICK:
        return "KICK";
    case PASS:
        return "PASS";
    case USER:
        return "USER";
    case QUIT:
        return "QUIT";
    case PRIVMSG:
        return "PRIVMSG";
    case NOTICE:
        return "NOTICE";
    case TOPIC:
        return "TOPIC";
    case INVITE:
        return "INVITE";
    case MODE:
        return "MODE";
    case PART:
        return "PART";
    case CAP:
        return "CAP";
    case BOT:
        return "BOT";
    case PING:
        return "PING";
    default:
        return "UNKNOWN";
    }
}

bool Parser::isValidCommand(const std::string &command)
{
    try
    {
        stringToCommandType(toUpper(command));
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
}