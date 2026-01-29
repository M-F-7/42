/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:12:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/10 09:12:48 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

const char *Exceptions::NotPermLimit::what() const throw()
{
	return "IsLimited = false";
}

const char *Exceptions::NotPermPass::what() const throw()
{
	return "PassUp = false";
}

const char *Exceptions::NotPermTheme::what() const throw()
{
	return "ThemeUp = false";
}
