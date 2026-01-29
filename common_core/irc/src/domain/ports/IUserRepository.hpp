/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUserRepository.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:49:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 16:51:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <User.hpp>

class IUserRepositoryPort
{
public:
	virtual User &getOrCreate(unsigned long id) = 0;
	virtual bool delUser(unsigned long id) = 0;
	virtual User *getByNickName(const std::string &nickName) = 0;

	virtual ~IUserRepositoryPort() {};
};
