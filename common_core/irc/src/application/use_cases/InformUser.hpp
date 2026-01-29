/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformUser.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:02:30 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:04:16 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Channel.hpp"
#include "IPublisher.hpp"
#include "Response.hpp"

class InformUser
{
private:
	IPublisher &_publisher;

public:
	InformUser(IPublisher *publisher);
	void execute(User &user, std::string msg);
};
