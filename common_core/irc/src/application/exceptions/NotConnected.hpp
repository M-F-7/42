/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotConnected.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:51:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/30 14:52:40 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusException.hpp"
#include "CommandType.hpp"

class NotConnected : public StatusException
{
private:
	std::string mgs;

public:
	NotConnected(CommandType cmd);
	virtual ~NotConnected() throw();

	virtual const char *what() const throw();
};
