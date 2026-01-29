/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisconnectUser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:44:31 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 12:36:22 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DisconnectUser.hpp"

DisconnectUser::DisconnectUser(IUserRepositoryPort *userRepo, IChannelRepositoryPort *channelRepo) : _userRepo(userRepo), _channelRepo(channelRepo) {}

void DisconnectUser::execute(int clientId)
{
	std::vector<Channel *> channels = this->_channelRepo->getChannels();
	std::vector<Channel *>::iterator it = channels.begin();
	std::vector<Channel *>::iterator ite = channels.end();

	User &user = this->_userRepo->getOrCreate(clientId);
	this->_userRepo->delUser(clientId);

	for (; it != ite; it++)
	{
		(*it)->deleteUser(user);
		(*it)->deleteInvitedUser(user);
		(*it)->deleteBannedUser(user);
	}
	throw ClientAUREVOIRById(clientId);
};
