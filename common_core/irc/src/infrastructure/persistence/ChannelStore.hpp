/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelStore.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:13:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/01 10:05:35 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "IChannelRepository.hpp"

class ChannelStore : public IChannelRepositoryPort
{
private:
	std::map<std::string, Channel> _channels;
	Channel &addChannel(const std::string &name);

public:
	ChannelStore();
	~ChannelStore();

	std::vector<Channel *> getChannels();
	Channel *getChannel(std::string name);
	Channel &getOrCreate(std::string name);
	bool delChannel(std::string name);
};
