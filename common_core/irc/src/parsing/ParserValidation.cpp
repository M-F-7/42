/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserValidation.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:36:43 by rwassim           #+#    #+#             */
/*   Updated: 2025/10/02 10:36:43 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"
#include "Parser.hpp"

void Parser::validateCommandParameters(IRCMessage &msg, const std::string &command_str)
{
    switch (msg.command)
    {
    case NICK:
        if (msg.params.empty())
            throw StatusException(ERR_NONICKNAMEGIVEN, " :No nickname given");
        if (!isValidNickname(msg.params[0]))
            throw StatusException(ERR_ERRONEUSNICKNAME, msg.params[0] + " :Erroneous nickname");
        // if (ERR_NICKNAMEINUSE)
        break;

    case USER:
        if (msg.params.size() < 1)
            throw StatusException(ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
        for (size_t i = 0; i < 1; ++i)
        {
            if (msg.params[i].empty())
            {
                std::stringstream ss;
                ss << (i + 1);
                throw StatusException(ERR_NEEDMOREPARAMS, " USER :Invalid parameter at position " + ss.str());
            }
        }
        break;
    case PASS:
        if (msg.params.empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
        if (msg.params[0].empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "PASS :Password cannot be empty");
        break;

    case JOIN:
        if (msg.params.empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
        if (!isValidChannelName(msg.params[0]))
            throw StatusException(ERR_NOSUCHCHANNEL, msg.params[0] + " :No such channel");
        for (size_t i = 1; i < msg.params.size(); ++i)
        {
            if (!isValidChannelName(msg.params[i]))
            {
                for (; i < msg.params.size(); ++i)
                    msg.trailing.push_back(msg.params[i]);
                msg.params.resize(msg.params.size() - msg.trailing.size());
                break;
            }
        }
        break;

    case INVITE:
        if (msg.params.size() < 2)
            throw StatusException(ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
        break;
    case KICK:
        if (msg.params.size() < 2)
            throw StatusException(ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
        isValidKick(msg);
        // if (!isValidChannelName(msg.params[0]))
        //     throw StatusException(ERR_NOSUCHCHANNEL, msg.params[0] + " :No such channel");
        // if (!isValidNickname(msg.params[1]))
        //     throw StatusException(ERR_ERRONEUSNICKNAME, msg.params[1] + " :Erroneous nickname");
        break;

    case MODE:
        if (msg.params.empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
        if (msg.params.size() >= 1)
            validateModeString(msg.params[1], msg.params);
        break;

    case NOTICE:
        if (!msg.reason.empty())
            msg.params.push_back(":" + msg.reason);
        if (msg.params.size() < 2)
            throw StatusException(ERR_NEEDMOREPARAMS, "NOTICE :Not enough parameters");
        break;

    case PART:
        if (msg.params.empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "PART :Not enough parameters");
        if (msg.params.size() > 1)
            throw StatusException(ERR_TOOMANYTARGETS, "PART :Too many parameters");
        isValidPart(msg);
        // if (!isValidChannelName(msg.params[0]))
        //     throw StatusException(ERR_NOSUCHCHANNEL, msg.params[0] + " :No such channel");
        break;

    case PRIVMSG:
        if (msg.params.size() < 1)
            throw StatusException(ERR_NEEDMOREPARAMS, "PRIVMSG :Not enough parameters");
        isValidPrivMsg(msg);
        break;

    case CAP:
        break;
    case PING:
        if (msg.params.size() < 1)
            throw StatusException(ERR_NEEDMOREPARAMS, "PING :Not enough parameters");
        break;
    case BOT:
        break;
    case QUIT:
        break;
    case TOPIC:
        if (msg.params.empty())
            throw StatusException(ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
        if (!isValidChannelName(msg.params[0]))
            throw StatusException(ERR_NOSUCHCHANNEL, msg.params[0] + " :No such channel");
        break;

    default:
        throw StatusException(ERR_UNKNOWNCOMMAND, command_str + " :Unknown command");
        break;
    }
}

void Parser::validateModeString(const std::string &modeString, std::vector<std::string> &params)
{
    if (params.size() == 1)
        return;
    if (modeString.empty())
        return;
    bool hasOperator = (modeString[0] == '+' || modeString[0] == '-');
    if (!hasOperator)
        throw StatusException(ERR_UNKNOWNMODE, std::string(1, modeString[0]) + " :is unknown mode char to me");

    char currentOperator = modeString[0];
    size_t paramIndex = 1;

    for (size_t i = 1; i < modeString.length(); ++i)
    {
        char mode = modeString[i];

        if (mode == '+' || mode == '-')
        {
            currentOperator = mode;
            continue;
        }
        if (mode != 'i' && mode != 't' && mode != 'k' &&
            mode != 'o' && mode != 'l')
        {
            throw StatusException(ERR_UNKNOWNMODE, std::string(1, mode) + " :is unknown mode char to me");
        }
        if (mode == 'o')
            paramIndex++;
        if (mode == 'l' && currentOperator == '+')
            paramIndex++;
        if (mode == 'k' && currentOperator == '+')
            paramIndex++;

        // if ((mode == 'o' || mode == 'l' || mode == 'k') && currentOperator == '+')
        // {
        //     if (paramIndex >= params.size())
        //         throw StatusException(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
        //     paramIndex++;
        // }
        // else if (mode == 'k' && currentOperator == '-')
        // {
        //     if (paramIndex >= params.size())
        //         throw StatusException(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
        //     paramIndex++;
        // }
    }
    if (paramIndex >= params.size())
        throw StatusException(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
}

bool Parser::isValidChannelName(const std::string &name)
{
    if (name.empty() || name.length() > 50)
        return false;
    if (name[0] != '#' && name[0] != '&')
        return false;
    for (size_t i = 0; i < name.length(); ++i)
    {
        char c = name[i];
        if (c == ' ' || c == ',' || c == '\r' || c == '\n' || c == 7)
            return false;
    }

    return true;
}

bool Parser::isValidNickname(const std::string &nickname)
{
    if (nickname.empty() || nickname.length() > 9)
        return false;
    char first = nickname[0];
    if (!std::isalpha(first) && first != '[' && first != ']' &&
        first != '{' && first != '}' && first != '\\' && first != '|' &&
        first != '^' && first != '_' && first != '`')
        return false;
    for (size_t i = 1; i < nickname.length(); ++i)
    {
        char c = nickname[i];
        if (!std::isalnum(c) && c != '[' && c != ']' && c != '{' &&
            c != '}' && c != '\\' && c != '|' && c != '^' &&
            c != '_' && c != '`' && c != '-')
            return false;
    }

    return true;
}
void Parser::isValidKick(IRCMessage &msg)
{
    size_t i = 0;
    if (msg.trailing.size())
    {
        msg.reason = msg.trailing[0];
        msg.trailing.pop_back();
    }
    while (i < msg.params.size())
    {
        if (msg.params[i].empty() || (msg.params[i][0] != '&' && msg.params[i][0] != '#'))
            break;
        i++;
    }
    while (i < msg.params.size())
    {
        if (!msg.params[i].empty() && (msg.params[i][0] != ':'))
            msg.trailing.push_back(msg.params[i]);
        else
            break;
        i++;
    }
    if (!msg.trailing.size())
        throw StatusException(ERR_NEEDMOREPARAMS, ":User missing");
    msg.params.resize(msg.params.size() - msg.trailing.size());
    if (!msg.params.size())
        throw StatusException(ERR_NEEDMOREPARAMS, ":Channel missing");
}

void Parser::isValidPart(IRCMessage &msg)
{
    std::string tmp = msg.params[0];
    if (tmp.empty() || tmp[0] == ',' || tmp[tmp.size() - 1] == ',')
        throw StatusException(ERR_NOSUCHCHANNEL, tmp + " :Invalid channel name");
    msg.params.clear();
    for (;;)
    {
        size_t idx = tmp.find(',');
        if (idx == std::string::npos)
            break;
        msg.params.push_back(tmp.substr(0, idx));
        tmp = tmp.substr(idx + 1);
    }
    msg.params.push_back(tmp);
}

void Parser::isValidPrivMsg(IRCMessage &msg)
{
    if (msg.reason.empty())
        throw StatusException(ERR_NEEDMOREPARAMS, ":Message missing");
    msg.trailing.clear();
    size_t i = 0;
    for (; i < msg.params.size(); i++)
        if (msg.params[i].empty() || (msg.params[i][0] != '#' && msg.params[i][0] != '&'))
            break;
    for (; i < msg.params.size(); i++)
    {
        if (msg.params[i].empty() || msg.params[i][0] == '#' || msg.params[i][0] == '&')
            throw StatusException(ERR_NEEDMOREPARAMS, ":Invalid param position");
        msg.trailing.push_back(msg.params[i]);
    }
    msg.params.resize(msg.params.size() - msg.trailing.size());
}
