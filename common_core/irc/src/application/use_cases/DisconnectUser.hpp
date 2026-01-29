/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisconnectUser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:43:58 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 16:15:25 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"
#include "IClientRepository.hpp"
#include "NetworkException.hpp"

class DisconnectUser
{
private:
	IUserRepositoryPort *_userRepo;
	IChannelRepositoryPort *_channelRepo;

public:
	DisconnectUser(IUserRepositoryPort *userRepo, IChannelRepositoryPort *channelRepo);
	void execute(int client_fd);
};
