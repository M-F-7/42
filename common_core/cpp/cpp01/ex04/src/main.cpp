/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 01:30:50 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int main(int ac, char **av){

    if (ac != 4)
    {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }
    std::string s1 = av[2];
    std::string s2 = av[3];

    std::string infilename = av[1];
    std::ifstream infile(infilename.c_str());
    if (!infile)
    {
        std::cerr << "Problem when opening the infile" << std::endl;
        return 1;
    }
    
    std::string outfilename = infilename + ".replace";
    std::ofstream outfile(outfilename.c_str());
    if (!outfile)
    {
        std::cerr << "Problem when creating the outfile" << std::endl;
        return 1;
    }
    std::string line;
    while(std::getline(infile, line))
    {
        unsigned long pos = 0;
        while ((pos = line.find(s1, 0)) != std::string::npos)
        {
            line = line.substr(0, pos) + s2 + line.substr(pos + s1.size());
            pos += s2.size();   
        }
        outfile << line;
        if (!infile.eof())
            outfile << std::endl;
    }
    infile.close();
    outfile.close();
    return 0;
}

