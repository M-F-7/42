/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformUser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:02:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:05:37 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InformUser.hpp"

InformUser::InformUser(IPublisher *publisher) : _publisher(*publisher) {};

void InformUser::execute(User &user, std::string msg)
{
	Response res(user);
	res.setMsg(msg);
	this->_publisher.publish(res);
}
