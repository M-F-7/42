/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:48:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 19:46:10 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <iomanip>
#include "../include/Account.hpp"

    int Account::_nbAccounts = 0;
    int Account::_totalAmount = 0;
    int Account::_totalNbDeposits = 0;
    int Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit ):_accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0){
    
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";created" << std::endl;
    _nbAccounts++;
    _totalAmount += initial_deposit;
}
Account::~Account( void ){
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";closed" << std::endl;
}


int Account::getNbAccounts(void) { return _nbAccounts; }
int Account::getTotalAmount(void) { return _totalAmount; }
int Account::getNbDeposits(void) { return _totalNbDeposits; }
int Account::getNbWithdrawals(void) { return _totalNbWithdrawals; }


void Account::_displayTimestamp(void) {
    std::time_t now = std::time(NULL);
    std::tm *ltm = std::localtime(&now);

    std::cout << "["
        << (ltm->tm_year + 1900)
        << std::setw(2) << std::setfill('0') << (ltm->tm_mon + 1)
        << std::setw(2) << std::setfill('0') << ltm->tm_mday
        << "_"
        << std::setw(2) << std::setfill('0') << ltm->tm_hour
        << std::setw(2) << std::setfill('0') << ltm->tm_min 
        << "] ";
}


void	Account::makeDeposit( int deposit ){

    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << _amount
              << ";deposit:" << deposit;
    _amount += deposit;
    _nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;
    std::cout << ";amount:" << _amount
              << ";nb_deposits:" << _nbDeposits << std::endl;
}


bool	Account::makeWithdrawal( int withdrawal ){

    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << _amount
              << ";withdrawal:";
    if (withdrawal > _amount) 
    {
        std::cout << "refused" << std::endl;
        return false;
    }
    std::cout << withdrawal;
    _amount -= withdrawal;
    _nbWithdrawals++;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;
    std::cout << ";amount:" << _amount
              << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
    return true;
}

int		Account::checkAmount( void ) const{
    return _amount;
}

void	Account::displayStatus( void ) const{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" <<_nbWithdrawals
              << std::endl;
}


void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts
              << ";total:" << _totalAmount
              << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals
              << std::endl;
}

