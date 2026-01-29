/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPing.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:44:26 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 16:02:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "UseCases.hpp"
#include "IUserRepository.hpp"

class CommandPing : public ICommand
{

private:
    IUserRepositoryPort &_userRepo;
    UseCases &_usesCases;

public:
    CommandPing(IUserRepositoryPort &userRepo, UseCases &usesCases);
    ~CommandPing();

    void execute(IRCMessage msg, unsigned long client_id);
};
