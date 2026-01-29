/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:16:10 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/14 21:22:06 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"
#include "UseCases.hpp"

class CommandInvite : public ICommand
{
private:
    IUserRepositoryPort &userRepo;
    IChannelRepositoryPort &channelRepo;
    UseCases &useCases;
public:
    CommandInvite(IUserRepositoryPort &userRepo, UseCases &useCases, IChannelRepositoryPort &channelRepo);
    ~CommandInvite();
    
    void execute(IRCMessage msg, unsigned long client_id);
};
