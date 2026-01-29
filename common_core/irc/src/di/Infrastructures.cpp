/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infrastructures.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moss <moss@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:44:09 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 11:54:48 by moss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Infrastructures.hpp"
#include "ChannelStore.hpp"
#include "UserStore.hpp"
#include "ClientStore.hpp"
#include "Parser.hpp"
// #include "FakeParser.hpp"

Infrastructures::Infrastructures()
{
	userRepo = new UserStore();
	channelRepo = new ChannelStore();
	clientRepo = new ClientStore();
	// parser = new FakeParser();
	parser = new Parser();
}

Infrastructures::~Infrastructures()
{
	if (userRepo)
		delete userRepo;
	if (channelRepo)
		delete channelRepo;
	if (clientRepo)
		delete clientRepo;
	if (parser)
		delete parser;
}
