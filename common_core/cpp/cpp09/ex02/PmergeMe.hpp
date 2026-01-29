/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:53:42 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/24 12:55:48 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include <ctime>
#include <iomanip>


class PmergeMe {
private:

    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);



    /////////BOTH///////////////

    static bool compare_pairs(const std::pair<double, double>& a, const std::pair<double, double>& b);

    void print_not_sort();

     bool _has_odd_element;               // elt isole
    

    std::vector<int> insertionOrder(size_t size);
    std::vector<int> jacobsthalSequence(size_t n);
    void splitPairs(const std::vector<std::pair<double, double> >& pairs,
                          std::vector<double>& bigs, std::vector<double>& smalls);
    void normalizePairs(std::vector<std::pair<double, double> >& pairs);

    void check_v_sorted();
    void check_d_sorted();
    /// /////////// VECTOR//////////////////////////


    
    void sortVector();
    void insertSmalls_v(const std::vector<double>& smalls);
    
    void SetVectorTimer();

    void print_sort_v();
    void print_first_cont();

    std::vector<std::pair<double, double> >_input_for_v;  
    std::vector<int> _sorted_vector;     // Resultat avec vector
    clock_t _start_timer_v;
    double _vector_time; 
    
    
    
    
    ///////////////DEQUE//////////////////
    
    
    void sortDeque();
    void insertSmalls_d(const std::vector<double>& smalls);     

    void SetDequeTimer();
    
    void print_sort_d();
    void print_scd_cont();

    
    std::vector<std::pair<double, double> >_input_for_d;
    std::deque<int> _sorted_deque;       // Resultat avec deque
    clock_t _start_timer_d;
    double _deque_time;             

    
public:
    
    PmergeMe(int ac, char **av);
    ~PmergeMe();

    void sort();
    
    double getVectorTime() const;
    double getDequeTime() const;
};