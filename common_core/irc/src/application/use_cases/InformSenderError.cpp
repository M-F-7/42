/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformSenderError.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:02:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:05:37 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InformSenderError.hpp"

InformSenderError::InformSenderError(IPublisher *publisher) : _publisher(*publisher) {};

void InformSenderError::execute(User *sender, StatusException &error)
{
	Response res(*sender);
	res.setMsg(error.what());
	res.setStatusCode(error.getStatus());
	this->_publisher.publish(res);
}
