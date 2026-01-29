/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:34:16 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 23:19:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandJoin.hpp"

CommandJoin::CommandJoin(IUserRepositoryPort &userRepo, IChannelRepositoryPort &channelRepo, UseCases &useCases) : _usesCases(useCases), _userRepo(userRepo), _channelRepo(channelRepo) {};

CommandJoin::~CommandJoin() {};

void CommandJoin::execute(IRCMessage msg, unsigned long client_id)
{
	User &currentUser = this->_userRepo.getOrCreate(client_id);
	Response response(currentUser);
	size_t password_index = 0;

	for (size_t i = 0; i < msg.params.size(); i++)
	{
		try
		{
			Channel &channel = this->_channelRepo.getOrCreate(msg.params[i]);

			if (channel.isBanned(currentUser.getNickName()))
				throw BannedFromChanException(channel.getName());
			if (channel.getIsLimited() && channel.getLimit() <= channel.getNbUsers())
				throw ChanIsFullException(channel.getName());
			if (channel.getInviteOnly() && !channel.isInvited(currentUser.getNickName()))
				throw InviteOnlyChanException(channel.getName());
			this->_checkChannelPass(channel, msg, &password_index);
			channel.addUser(currentUser);
			// if (channel.getTheme().empty())
				// this->_usesCases.informUser->execute(currentUser, channel.getName() + " :No topic is set");
			// else
				// this->_usesCases.informUser->execute(currentUser, currentUser.getNickName() + " " + channel.getName() + " :" + channel.getTheme());
			this->_usesCases.informChannel->execute(channel, &currentUser, currentUser.getNickName() + " JOIN " + channel.getName());

			std::string listUsers = "353 " + currentUser.getNickName() + " = " + channel.getName() + " :";
			std::map<User *, bool>::iterator it = channel.getUsers().begin();
			std::map<User *, bool>::iterator ite = channel.getUsers().end();
			for (; it != ite; ++it)
				listUsers += it->first->getNickName() + " ";
			this->_usesCases.informUser->execute(currentUser, listUsers);
		}
		catch (StatusException &e)
		{
			Response response(currentUser);
			response.setStatusCode(e.getStatus());
			response.setMsg(e.what());
			this->_usesCases.sendReponse->execute(response);
		}
	}
}
void CommandJoin::_checkChannelPass(Channel &currChannel, IRCMessage &msg, size_t *i)
{
	if (!currChannel.getPassUp())
		return;
	*i = *i + 1;
	if (msg.trailing.size() < *i - 1 || !msg.trailing.size())
		throw BadChanPassException(currChannel.getName());
	if (msg.trailing[*i - 1] != currChannel.getPass())
		throw BadChanPassException(currChannel.getName());
}
