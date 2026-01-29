/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CannotSendToChanException.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:37:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:09:49 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"

class CannotSendToChanException : public StatusException
{
public:
	CannotSendToChanException(std::string chan);
};
