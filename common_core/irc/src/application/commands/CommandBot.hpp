/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBot.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:54:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/01 12:02:59 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "UseCases.hpp"
#include "IUserRepository.hpp"

class CommandBot : public ICommand
{
private:
    UseCases &_uc;
    IUserRepositoryPort &_userRepo;

public:
    CommandBot(IUserRepositoryPort &userRepo,UseCases &uc);
    ~CommandBot();

    void execute(IRCMessage msg, unsigned long client_id);
};
