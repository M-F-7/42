/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:24:02 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/12 09:56:32 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassException.hpp"

PassException::PassException(std::string pass, StatusCode status,
                             std::string msg) : StatusException()
{
    std::ostringstream oss;
    oss << pass << " :" << msg;
    this->setMsg(msg);
    this->setStatus(status);
}

PassNotMatch::PassNotMatch() : PassException("", ERR_PASSWDMISMATCH,
                                             "Password incorrect") {};
