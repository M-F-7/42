/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChanOperatorNeededException.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:33:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/12 16:36:32 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StatusException.hpp"

class ChanOperatorNeededException : public StatusException
{
public:
	ChanOperatorNeededException(std::string channel);
};
