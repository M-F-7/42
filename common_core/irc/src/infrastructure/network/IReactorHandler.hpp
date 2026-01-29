/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IReactorHandler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:57:16 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 10:30:08 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class IReactorHandler
{
public:
	virtual ~IReactorHandler() {};
	virtual void on_writable(int fd) = 0;
	virtual void on_readable(int fd) = 0;
	virtual void on_exitable(int fd) = 0;
	virtual void on_error(int fd) = 0;
};
