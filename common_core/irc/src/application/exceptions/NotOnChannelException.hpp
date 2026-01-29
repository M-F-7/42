/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotOnChannelException.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:33:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 17:20:20 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"

class NotOnChannelException : public StatusException
{
public:
	NotOnChannelException(std::string channel);
};
