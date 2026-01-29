/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformChannel.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:38:43 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 14:02:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Channel.hpp"
#include "IPublisher.hpp"
#include "Response.hpp"

class InformChannel
{
private:
	IPublisher &_publisher;

public:
	InformChannel(IPublisher *publisher);
	void execute(Channel &channel, User *sender, const std::string &msg);
};
