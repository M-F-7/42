/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:44:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 15:50:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>
#include "StatusCode.hpp"

class StatusException : public std::exception
{
private:
	StatusCode _status;
	std::string _msg;

public:
	StatusException();
	StatusException(StatusCode status, std::string msg);
	virtual ~StatusException() throw();

	StatusCode getStatus() const;
	void setStatus(StatusCode status);
	std::string getMsg() const;
	void setMsg(std::string &msg);

	const char *what() const throw();
};
