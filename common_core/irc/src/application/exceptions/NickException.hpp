/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 16:36:44 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"
#include <sstream>

class NickException : public StatusException
{
protected:
	std::string _nick;

public:
	NickException(std::string nick, StatusCode status, std::string msg);
	virtual ~NickException() throw();
};

class NickNameAlreadyUsedException : public NickException
{
public:
	NickNameAlreadyUsedException(std::string nick);
	virtual ~NickNameAlreadyUsedException() throw();
};

class NoNickNameGivenException : public NickException
{
public:
	NoNickNameGivenException();
	virtual ~NoNickNameGivenException() throw();
};

class NickNameInvalid : public NickException
{
public:
	NickNameInvalid(std::string nick);
	virtual ~NickNameInvalid() throw();
};
