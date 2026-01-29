/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartupTime.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:15:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 13:16:13 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StartupTime.hpp"

std::string ServerConfig::_startupTime = "";

void ServerConfig::initStartupTime() {
    std::time_t now = std::time(0);
    char* timeStr = std::ctime(&now);
    _startupTime = std::string(timeStr);
    // Supprimer le \n à la fin
    if (!_startupTime.empty() && _startupTime.back() == '\n') {
        _startupTime.pop_back();
    }
}

const std::string& ServerConfig::getStartupTime() {
    return _startupTime;
}