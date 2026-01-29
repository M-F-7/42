/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartupTime.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:15:30 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 13:16:35 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string>
#include <ctime>

class ServerConfig {
private:
    static std::string _startupTime;

public:
    static void initStartupTime();
    static const std::string& getStartupTime();
};