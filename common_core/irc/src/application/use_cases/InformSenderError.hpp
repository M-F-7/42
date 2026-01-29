/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformSenderError.hpp                              :+:      :+:    :+:   */
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

class InformSenderError
{
private:
	IPublisher &_publisher;

public:
	InformSenderError(IPublisher *publisher);
	void execute(User *sender, StatusException &error);
};
