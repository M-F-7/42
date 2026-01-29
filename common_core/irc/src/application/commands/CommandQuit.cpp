/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:57:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/02 11:02:43 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandQuit.hpp"

CommandQuit::CommandQuit(IUserRepositoryPort &userRepo, InformChannel &informChannel, IChannelRepositoryPort &channelRepo, DisconnectUser &disconnectUser) : _userRepo(userRepo), _channelRepo(channelRepo), _informChannel(informChannel), _disconnectUser(disconnectUser) {};

CommandQuit::~CommandQuit() {}

void CommandQuit::execute(IRCMessage msg, unsigned long client_id)
{
	User &user = this->_userRepo.getOrCreate(client_id);
	std::vector<Channel *> channels = this->_channelRepo.getChannels();
	std::string message = ":" + user.getNickName() + "!" + user.getUserName() + "@" + ServerConfig::getHost() + " QUIT :";
	std::string server_msg = "[INFO] " + user.getNickName() + "!" + user.getUserName() + "@" + ServerConfig::getHost() + " has quit :";

	if (msg.params.size() == 0)
		message +=  "leaving", server_msg += "leaving";
	else{
		for (size_t i = 0; i < msg.params.size(); i++)
			message +=  msg.params[i] + " ", server_msg += msg.params[i] + " ";
	}

	
	std::cout << server_msg  << std::endl;
	for (size_t i = 0; i < channels.size(); i++)
		if (channels[i]->isInUsers(user))
			this->_informChannel.execute(*channels[i], &user, message);

	this->_disconnectUser.execute(client_id);
}
