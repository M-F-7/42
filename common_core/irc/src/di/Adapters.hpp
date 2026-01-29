/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Adapters.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:41:58 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:13:46 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IPublisher.hpp"
#include "Infrastructures.hpp"
#include "Sender.hpp"

class Adapters
{
public:
	IPublisher *publisher;
	Sender *sender;

	Adapters(Infrastructures &infra);
	~Adapters();
};
