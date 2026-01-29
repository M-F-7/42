/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:27:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 14:17:17 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include "ICommand.hpp"
#include "CommandType.hpp"
#include "Infrastructures.hpp"
#include "Adapters.hpp"
#include "UseCases.hpp"
#include "CommandBus.hpp"

class Commands
{

public:
	std::map<CommandType, ICommand *> commandMap;
	CommandBus *commandBus;
	Commands(Infrastructures &infra, Adapters &adapters, UseCases &useCases);
	~Commands();
};
