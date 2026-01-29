/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:05:33 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/17 11:06:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SendResponse.hpp"

SendResponse::SendResponse(IPublisher *publisher) : _publisher(publisher) {}

void SendResponse::execute(Response &resp) const
{
	this->_publisher->publish(resp);
};
