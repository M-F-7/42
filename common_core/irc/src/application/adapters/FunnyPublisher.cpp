/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FunnyPublisher.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:55:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 14:54:28 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FunnyPublisher.hpp"
#include "ServerConfig.hpp"
#include <iomanip>

FunnyPublisher::FunnyPublisher(Sender &sender) : _sender(sender) {};
FunnyPublisher::~FunnyPublisher() {};

void FunnyPublisher::publish(Response &response)
{
	std::string message;

	message += ":" + ServerConfig::getHost() + " ";

	if (response.getStatusCode())
		message += this->formatStatus(response.getStatusCode()) + " ";
	message += response.getMsg() + "\n";

	_sender.sendMessage(response.getTarget().getId(), message);
}

std::string FunnyPublisher::formatStatus(StatusCode status)
{
	std::ostringstream oss;
	oss << std::setw(3) << std::setfill('0') << static_cast<int>(status);
	return oss.str();
}
