/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UseCases.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:08:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 15:57:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "InformChannel.hpp"
#include "InformSenderError.hpp"
#include "InformUser.hpp"
#include "Adapters.hpp"
#include "SendResponse.hpp"
#include "DisconnectUser.hpp"
#include "Infrastructures.hpp"

class UseCases

{
public:
	UseCases(Adapters &adapters, Infrastructures &infra);
	~UseCases();

	InformChannel *informChannel;
	InformSenderError *informSenderError;
	InformUser *informUser;
	SendResponse *sendReponse;
	DisconnectUser *disconnectUser;
};
