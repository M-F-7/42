/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moss <moss@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:23:15 by rwassim           #+#    #+#             */
/*   Updated: 2025/09/30 14:19:56 by moss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "CommandType.hpp"
#include "IParser.hpp"
#include "IRCMessage.hpp"
#include "NeedMoreParamsException.hpp"

class Parser : public IParser
{
public:
	Parser();
	Parser(const Parser &other);
	Parser &operator=(const Parser &other);
	~Parser();

	struct ParserOption
	{
		bool useRFC1459CaseMap;
		ParserOption() : useRFC1459CaseMap(true) {}
	};

	IRCMessage parseMessage(const std::string &line);
	IRCMessage parseMessage(const std::string &line, const ParserOption &option);
	static std::vector<std::string> extractLines(std::string &buffer);
	static bool isValidCommand(const std::string &command);
	static bool isValidNickname(const std::string &nickname);
	static void isValidKick(IRCMessage &msg);
	static void isValidPart(IRCMessage &msg);
	static void isValidPrivMsg(IRCMessage &msg);

private:
	static std::string trim(const std::string &str);
	static std::string toUpper(const std::string &s);
	static std::string toLower(const std::string &s);
	static std::string toLowerRFC1459(const std::string &s);
	static std::string foldLower(const std::string &s, bool useRFC1459);
	static CommandType stringToCommandType(const std::string &command);
	static std::string commandTypeToString(CommandType type);
	bool commandRequiresParams(const std::string &command) const;
	static std::vector<std::string> divideString(const std::string &str, char delim);
	static void parseParameters(const std::string &trimmed, std::string::size_type pos, IRCMessage &msg);
	static void validateCommandParameters(IRCMessage &msg, const std::string &command_str);
	static void validateModeString(const std::string &modeString, std::vector<std::string> &params);
	static bool isValidChannelName(const std::string &name);
};

#endif
