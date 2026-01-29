/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:37:23 by rwassim           #+#    #+#             */
/*   Updated: 2025/10/02 10:37:23 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"

Parser::Parser()
{
}

Parser::Parser(const Parser &other)
{
    *this = other;
}

Parser &Parser::operator=(const Parser &other)
{
    (void)other;
    return *this;
}

Parser::~Parser()
{
}

IRCMessage Parser::parseMessage(const std::string &line)
{
    ParserOption options;
    return parseMessage(line, options);
}

IRCMessage Parser::parseMessage(const std::string &line, const ParserOption &options)
{

    (void)options;
    
    IRCMessage msg;
    std::string trimmed = trim(line);
    if (trimmed.empty())
    {
        msg.command = UNKNOWN;
        throw NeedMoreParamsException(UNKNOWN);
    }
    if (trimmed.length() > 512)
    {
        msg.command = UNKNOWN;
        throw StatusException(ERR_UNKNOWNCOMMAND, "Message too long (max 512 characters)");
    }

    std::string::size_type pos = 0;
    if (trimmed[0] == ':')
    {
        std::string::size_type prefix_end = trimmed.find(' ');
        if (prefix_end == std::string::npos)
        {
            msg.command = UNKNOWN;
            throw StatusException(ERR_UNKNOWNCOMMAND, "Invalid prefix format");
        }
        msg.prefix = trimmed.substr(1, prefix_end - 1);
        pos = prefix_end + 1;
    }
    while (pos < trimmed.length() && trimmed[pos] == ' ')
        pos++;

    std::string::size_type cmd_end = trimmed.find(' ', pos);
    std::string command_str;
    
    if (cmd_end == std::string::npos)
        command_str = trimmed.substr(pos);
    else
        command_str = trimmed.substr(pos, cmd_end - pos);
    if (command_str.empty())
    {
        msg.command = UNKNOWN;
        throw StatusException(ERR_UNKNOWNCOMMAND, "Missing command");
    }
    try
    {
        msg.command = stringToCommandType(toUpper(command_str));
    }
    catch (std::invalid_argument &e)
    {
        msg.command = UNKNOWN;
        throw StatusException(ERR_UNKNOWNCOMMAND, command_str + " :Unknown command");
    }
    if (cmd_end == std::string::npos)
    {
        validateCommandParameters(msg, command_str);
        return msg;
    }
    pos = cmd_end + 1;
    parseParameters(trimmed, pos, msg);
    validateCommandParameters(msg, command_str);

    return msg;
}

