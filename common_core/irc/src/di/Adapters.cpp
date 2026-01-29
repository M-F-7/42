/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Adapters.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:42:42 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:13:23 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Adapters.hpp"
#include "FunnyPublisher.hpp"

Adapters::Adapters(Infrastructures &infra)
{
	sender = new Sender(infra.clientRepo);
	publisher = new FunnyPublisher(*sender);
}

Adapters::~Adapters()
{
	if (publisher)
		delete publisher;
	if (sender)
		delete sender;
}
