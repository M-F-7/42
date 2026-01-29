/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:55:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 13:16:56 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Infrastructures.hpp"
#include "Container.hpp"

int main(int argc, char const **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	ServerConfig::setPassword(argv[2]);
	ServerConfig::setPort(static_cast<unsigned int>(std::atoi(argv[1])));
	ServerConfig::initStartupTime();

	Container container;

	container.networks->server->start(ServerConfig::getPort());
	return 0;
}
