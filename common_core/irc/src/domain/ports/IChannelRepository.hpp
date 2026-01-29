/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IChannelRepository.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:02:46 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/01 10:05:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"
#include <map>

class IChannelRepositoryPort
{
public:
	virtual std::vector<Channel *> getChannels() = 0;
	virtual Channel *getChannel(std::string name) = 0;
	virtual Channel &getOrCreate(std::string name) = 0;
	virtual bool delChannel(std::string name) = 0;
	virtual ~IChannelRepositoryPort() {};
};
