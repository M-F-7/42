/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandCap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:42:41 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 23:04:24 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "UseCases.hpp"
#include "IUserRepository.hpp"

class CommandCap : public ICommand
{
    UseCases &_uc;
    IUserRepositoryPort &_userRepo;
public:
    CommandCap(IUserRepositoryPort &userRepo,UseCases &uc);
    ~CommandCap();

    void execute(IRCMessage msg, unsigned long client_id);
};
