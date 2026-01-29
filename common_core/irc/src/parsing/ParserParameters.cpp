/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserParameters.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:37:04 by rwassim           #+#    #+#             */
/*   Updated: 2025/10/02 10:37:04 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"

void Parser::parseParameters(const std::string& trimmed, std::string::size_type pos, IRCMessage& msg)
{
    std::string params_part = trimmed.substr(pos);
    std::string::size_type trailing_pos = params_part.find(" :");
    
    std::string regular_params;
    
    if (trailing_pos != std::string::npos)
    {
        regular_params = params_part.substr(0, trailing_pos);
        std::string trailing_content = params_part.substr(trailing_pos + 2);
        if (!trailing_content.empty())
            msg.trailing.push_back(trailing_content);
    }
    else
    {
        regular_params = params_part;
    }
    
    if (!regular_params.empty())
    {
        std::istringstream iss(regular_params);
        std::string param;
        while (iss >> param)
        {
            if (param.length() > 200)
                throw StatusException(ERR_UNKNOWNCOMMAND, "Parameter too long");
            msg.params.push_back(param);
        }
    }

    if (msg.command == PRIVMSG || msg.command == NOTICE)
    {
        if (!msg.trailing.empty())
        {
            msg.reason = msg.trailing[0];
            msg.trailing.clear();
        }
    }
    else if (msg.command == QUIT)
    {
        if (!msg.params.empty())
        {
            std::string quit_reason;
            for (size_t i = 0; i < msg.params.size(); ++i)
            {
                if (i > 0) quit_reason += " ";
                quit_reason += msg.params[i];
            }
            msg.reason = quit_reason;
        }
        if (!msg.trailing.empty())
        {
            if (!msg.reason.empty()) msg.reason += " ";
            msg.reason += msg.trailing[0];
            msg.trailing.clear();
        }
    }
}