/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:36:53 by rwassim           #+#    #+#             */
/*   Updated: 2025/10/02 10:36:53 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"

std::vector<std::string> Parser::divideString(const std::string &str, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delim))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> Parser::extractLines(std::string &buffer)
{
    std::vector<std::string> lines;
    std::string::size_type pos = 0;

    while ((pos = buffer.find("\r\n")) != std::string::npos)
    {
        std::string line = buffer.substr(0, pos);
        if (!line.empty())
            lines.push_back(line);
        buffer.erase(0, pos + 2);
    }
    return lines;
}

std::string Parser::trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string Parser::toUpper(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Parser::toLower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string Parser::toLowerRFC1459(const std::string &s)
{
    std::string result = s;
    for (size_t i = 0; i < result.length(); ++i)
    {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] - 'A' + 'a';
        else if (result[i] == '[')
            result[i] = '{';
        else if (result[i] == ']')
            result[i] = '}';
        else if (result[i] == '\\')
            result[i] = '|';
        else if (result[i] == '~')
            result[i] = '^';
    }
    return result;
}

std::string Parser::foldLower(const std::string &s, bool useRFC1459)
{
    return useRFC1459 ? toLowerRFC1459(s) : toLower(s);
}