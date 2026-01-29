/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:53:34 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/24 16:47:46 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
    // std::cout << "PmergeMe default constructor called"
                // << std::endl;
    this->_start_timer_v = clock();
    this->_start_timer_d = clock();
    this->_vector_time = 0;
    this->_deque_time = 0;
    this->_has_odd_element = false;
}

PmergeMe::PmergeMe(int ac, char **av){
    // std::cout << "PmergeMe param constructor called"
                // << std::endl;
    this->_vector_time = 0;
    this->_deque_time = 0;
    this->_has_odd_element = ac % 2;

    char *end_stod;
    char *end_stodd;
    char *end_stoddd;

     for (int i = 1; i < ac - 1; i += 2) {
        double first = std::strtod(av[i], &end_stod);
        double second = std::strtod(av[i + 1], &end_stodd);

        if (first < 0 || first > std::numeric_limits<int>::max() || 
            second < 0 || second > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Numbers must be positive integers");
        }
        if (*end_stod || *end_stodd)
            throw std::invalid_argument("Invalid number format");
        
        this->_input_for_v.push_back(std::make_pair(first, second));
    }
    
    if (ac % 2 == 0) {
        double last = std::strtod(av[ac - 1], &end_stoddd);
        
        if (last < 0 || last > std::numeric_limits<int>::max())
            throw std::invalid_argument("Last number must be positive integer");
        if (*end_stoddd)
            throw std::invalid_argument("Invalid last number format");
        
        this->_input_for_v.push_back(std::make_pair(last, -1));
    }

    this->_input_for_d = this->_input_for_v;
}

PmergeMe::PmergeMe(const PmergeMe& other){
    // std::cout << "PmergeMe copy constructor called"
                // << std::endl
    *this = other;
}
    
PmergeMe& PmergeMe::operator=(const PmergeMe& other){
    // std::cout << "PmergeMe copy operator assignement called"
                // << std::endl
    if (this == &other)
        return *this;
        
    this->_input_for_v = other._input_for_v;
    this->_sorted_vector = other._sorted_vector;
    this->_sorted_deque = other._sorted_deque;
    this->_start_timer_v = other._start_timer_v;
    this->_start_timer_d = other._start_timer_d;
    this->_vector_time = other._vector_time;
    this->_deque_time = other._deque_time;
    this->_has_odd_element = other._has_odd_element;
    
    return *this;
}

PmergeMe::~PmergeMe(){
    // std::cout << "PmergeMe destrucor called"
                // << std::endl;        

}




/////////////////////BOTH////////////////////
void PmergeMe::sort(){
    
    print_not_sort();
    this->_start_timer_v = clock();
    sortVector();
    SetVectorTimer();

    
    print_sort_v();
    print_first_cont();

    //////DEQUE PART/////
    
    this->_start_timer_d = clock();
    sortDeque();
    SetDequeTimer();
    
    // print_sort_d();// pas obligatoire
    print_scd_cont();
    
    ////BONUS////
    // check_v_sorted();
    // check_d_sorted();
}


void PmergeMe::print_not_sort(){
    std::cout << "Before: ";
    
    for (std::vector<std::pair<double, double> >::iterator it = this->_input_for_v.begin(); it != this->_input_for_v.end(); ++it){  
        std::cout << it->first << " " << it->second << " ";
        if (!this->_has_odd_element && it + 2 == this->_input_for_v.end())
            break;
    }
    if (!this->_has_odd_element)
        std::cout << this->_input_for_v.rbegin()->first;
    std::cout << std::endl;
}




void PmergeMe::normalizePairs(std::vector<std::pair<double, double> >& pairs) {
    for (std::vector<std::pair<double, double> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it->second < it->first && it->second != -1)
            std::swap(it->first, it->second);
    }
}



void PmergeMe::splitPairs(const std::vector<std::pair<double, double> >& pairs,
                          std::vector<double>& bigs, std::vector<double>& smalls) {
    bigs.clear();
    smalls.clear();
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].second != -1)
            bigs.push_back(pairs[i].second);
        if (pairs[i].first != -1)
            smalls.push_back(pairs[i].first);
    }
}


std::vector<int> PmergeMe::jacobsthalSequence(size_t n) {
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while ((size_t)jacob.back() < n) {
        int value = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(value);
    }
    return jacob;
}


std::vector<int> PmergeMe::insertionOrder(size_t size) {
    std::vector<int> jacob = jacobsthalSequence(size);
    
    std::vector<int> order;
    if (size > 0)
        order.push_back(0);
    for (size_t k = 2; k < jacob.size() && jacob[k - 1] < (int)size; k++) {
        int debut = jacob[k - 1];
        int fin = std::min(jacob[k] - 1, (int)size - 1);
        for (int idx = fin; idx >= debut; --idx) {
            if (idx < (int)size)
                order.push_back(idx);
        }
    }
    return order; //return the order to chose the value that need to be push from small
}





// ///////VECTOR///////


void PmergeMe::insertSmalls_v(const std::vector<double>& smalls) {
    std::vector<int> order = insertionOrder(smalls.size());
    
    for (size_t i = 0; i < order.size(); i++) {
        double element = smalls[order[i]];
        std::vector<int>::iterator pos = std::lower_bound(this->_sorted_vector.begin(), this->_sorted_vector.end(), static_cast<int>(element));
        this->_sorted_vector.insert(pos, static_cast<int>(element)); // put elt just before the value >= elt
    }
}


void PmergeMe::sortVector() {
    if (this->_input_for_v.empty())
        return;

    normalizePairs(this->_input_for_v); //sort pairs

    std::vector<double> bigs;
    std::vector<double> smalls;
    
    splitPairs(this->_input_for_v, bigs, smalls); //first --> smalls, second bigs

    if (bigs.size() > 1) {
        this->_input_for_v.clear();
        for (size_t i = 0; i + 1 < bigs.size(); i += 2) {
            this->_input_for_v.push_back(std::make_pair(bigs[i], bigs[i + 1]));
        }
        if (bigs.size() % 2 == 1)
            this->_input_for_v.push_back(std::make_pair(bigs.back(), -1));
        sortVector(); // recusive call on input only fill by bigs
    } else {
        this->_sorted_vector.clear();
        for (size_t i = 0; i < bigs.size(); ++i)
            this->_sorted_vector.push_back(static_cast<int>(bigs[i]));
    }

    //jacob insert
    if (!smalls.empty())
        insertSmalls_v(smalls);
}


void PmergeMe::SetVectorTimer(){
    this->_vector_time = (double)(clock() - this->_start_timer_v) / CLOCKS_PER_SEC * 1000000.0; //without * 1e6 is to be in seconds
}


void PmergeMe::print_sort_v(){
    
    std::cout << "After: ";

    for (std::vector<int>::iterator it = this->_sorted_vector.begin(); it != this->_sorted_vector.end(); ++it){
            std::cout << *it << " ";
    }
    std::cout << std::endl;
}


void PmergeMe::print_first_cont(){
    
    std::cout << "Time to process a range of ";
    std::cout << this->_sorted_vector.size();
  
    std::cout <<  " elements with " 
                << "std::[vector] : " <<  std::fixed  << std::setprecision(5)  << this->_vector_time << " us" << std::endl;
    
}















/////////////////////DEQUE//////////////////////////


void PmergeMe::insertSmalls_d(const std::vector<double>& smalls) {
    std::vector<int> order = insertionOrder(smalls.size());
    
    for (size_t i = 0; i < order.size(); i++) {
        double element = smalls[order[i]];
        std::deque<int>::iterator pos = std::lower_bound(this->_sorted_deque.begin(), this->_sorted_deque.end(), static_cast<int>(element));
        this->_sorted_deque.insert(pos, static_cast<int>(element));
    }
}


void PmergeMe::sortDeque() {
    if (this->_input_for_d.empty())
        return;

    normalizePairs(this->_input_for_d); //sort pairs

    std::vector<double> bigs;
    std::vector<double> smalls;
    splitPairs(this->_input_for_d, bigs, smalls);  //first --> smalls, second bigs


    
    if (bigs.size() > 1) {
        this->_input_for_d.clear();
        for (size_t i = 0; i + 1 < bigs.size(); i += 2) {
            this->_input_for_d.push_back(std::make_pair(bigs[i], bigs[i + 1]));
        }
        if (bigs.size() % 2 == 1)
            this->_input_for_d.push_back(std::make_pair(bigs.back(), -1));
        sortDeque(); // recusive call on input only fill by bigs
    } else {
        this->_sorted_deque.clear();
        for (size_t i = 0; i < bigs.size(); ++i)
            this->_sorted_deque.push_back(static_cast<int>(bigs[i]));
    }

    //jacob insert
    if (!smalls.empty())
        insertSmalls_d(smalls);
}




void PmergeMe::SetDequeTimer(){
    this->_deque_time = (double)(clock() - this->_start_timer_d) / CLOCKS_PER_SEC * 1000000.0;// -> microseconds //without * 1e6 is to be in seconds
}



void PmergeMe::print_sort_d(){
    
    std::cout << "After: ";

    for (std::deque<int>::iterator it = this->_sorted_deque.begin(); it != this->_sorted_deque.end(); ++it){
            std::cout << *it << " ";
    }
    std::cout << std::endl;
}




void PmergeMe::print_scd_cont(){
    std::cout << "Time to process a range of ";
    std::cout << this->_sorted_deque.size();
    std::cout <<  " elements with " 
                << "std::[deque] : " 
                <<  std::fixed  
                << std::setprecision(5) 
                << this->_deque_time 
                << " us"<< std::endl; 
}




//////BONUS///////




void PmergeMe::check_v_sorted(){
   for (std::vector<int>::iterator it = this->_sorted_vector.begin(); it != this->_sorted_vector.end()- 1; ++it){
        if (*it > *(it + 1)){
            std::cout << "Vector is NOT sort ❌" << std ::endl;
            return ;
        }
    }     
    std::cout << "Vector is sort ✅" << std::endl; 
}

void PmergeMe::check_d_sorted(){
    
    for (std::deque<int>::iterator it = this->_sorted_deque.begin(); it != this->_sorted_deque.end() - 1; ++it){
        if (*it > *(it + 1)){
            std::cout << "Deque is NOT sort ❌" << std ::endl;
            return ;
        }
    }     
    std::cout << "Deque is sort ✅" << std::endl;
}