/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infrastructures.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:46:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/17 14:41:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "PollReactor.hpp"
#include "IChannelRepository.hpp"
#include "IUserRepository.hpp"
#include "IClientRepository.hpp"
#include "IParser.hpp"

class Infrastructures
{
public:
	PollReactor pollReactor;
	IParser* parser;
	IChannelRepositoryPort *channelRepo;
	IUserRepositoryPort *userRepo;
	IClientRepositoryPort *clientRepo;

	Infrastructures();
	~Infrastructures();
};
