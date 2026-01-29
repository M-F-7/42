/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UseCases.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:12:09 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 16:15:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UseCases.hpp"

UseCases::UseCases(Adapters &adapters, Infrastructures &infra)
{
	informChannel = new InformChannel(adapters.publisher);
	informSenderError = new InformSenderError(adapters.publisher);
	informUser = new InformUser(adapters.publisher);
	sendReponse = new SendResponse(adapters.publisher);
	disconnectUser = new DisconnectUser(infra.userRepo, infra.channelRepo);
}

UseCases::~UseCases()
{
	if (informChannel)
		delete informChannel;
	if (informSenderError)
		delete informSenderError;
	if (informUser)
		delete informUser;
	if (sendReponse)
		delete sendReponse;
	if (disconnectUser)
		delete disconnectUser;
}
