/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPublisher.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:27:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 20:00:04 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Response.hpp"

class IPublisher
{

public:
	virtual void publish(Response &response) = 0;
	virtual ~IPublisher() {};
};
