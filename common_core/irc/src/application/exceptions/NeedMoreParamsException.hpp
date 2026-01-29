/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NeedMoreParamsException.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:43:15 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 09:51:29 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"
#include "CommandType.hpp"

class NeedMoreParamsException : public StatusException
{
public:
	NeedMoreParamsException(CommandType cmd);
};
