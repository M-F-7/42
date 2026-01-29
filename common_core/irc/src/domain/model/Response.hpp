/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:55:00 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 20:06:14 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "User.hpp"
#include "StatusCode.hpp"

class Response
{

public:
	Response(const User &dest);
	Response(const User &dest, std::string &message);
	Response(const User &dest, std::string &message, StatusCode statut);
	Response(const User &dest, std::string &message, StatusCode statut, User *sender);
	~Response();

	void setStatusCode(StatusCode statut);
	void setMsg(const std::string &message);
	void setSender(const User &other);

	StatusCode getStatusCode() const;
	std::string getMsg() const;
	User *getSender() const;
	const User &getTarget() const;

private:
	StatusCode _statusCode;
	std::string _msg;
	User *_sender;
	const User &_target;
};
