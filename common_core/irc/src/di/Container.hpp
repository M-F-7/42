/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Container.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:44:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 14:21:26 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Infrastructures.hpp"
#include "Adapters.hpp"
#include "Commands.hpp"
#include "Networks.hpp"
#include "UseCases.hpp"

class Container
{
public:
	Infrastructures *infra;
	Adapters *adapters;
	Commands *commands;
	Networks *networks;
	UseCases *use_cases;

	Container();
	~Container();
};
