/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Container.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:15:05 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:14:39 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Container.hpp"
#include "Adapters.hpp"

Container::Container()
{
	infra = new Infrastructures();
	adapters = new Adapters(*infra);
	use_cases = new UseCases(*adapters, *infra);
	commands = new Commands(*infra, *adapters, *use_cases);
	networks = new Networks(*infra, *commands->commandBus);
}

Container::~Container()
{
	if (infra)
		delete infra;
	if (adapters)
		delete adapters;
	if (use_cases)
		delete use_cases;
	if (commands)
		delete commands;
	if (networks)
		delete networks;
}
