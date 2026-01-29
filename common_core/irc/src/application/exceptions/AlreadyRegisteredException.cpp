/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlreadyRegisteredException.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:36:22 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 20:33:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AlreadyRegisteredException.hpp"

AlreadyRegisteredException::AlreadyRegisteredException() : StatusException(ERR_ALREADYREGISTERED, ":Unauthorized command (already registered)") {};
