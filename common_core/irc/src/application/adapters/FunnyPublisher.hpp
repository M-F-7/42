/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FunnyPublisher.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:32:13 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:10:06 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "IPublisher.hpp"
#include <string>
#include <sstream>
#include "Sender.hpp"

class FunnyPublisher : public IPublisher
{

private:
	std::string formatStatus(StatusCode status);
	Sender &_sender;

public:
	FunnyPublisher(Sender &sender);
	~FunnyPublisher();

	void publish(Response &response);
};
