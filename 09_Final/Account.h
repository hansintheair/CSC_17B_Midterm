/** \file */

/**
 * \anchor Account
 * \class Account
 * This class stores User and Admin account data and provides accessors for reading and manipulating user/admin attributes.
 * 
 * DBModel is used to store records of Account users in a binary database file.
 */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Account.h
 * Author: hanne
 *
 * Created on April 5, 2024, 6:13 PM
 */


#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <cstring>
#include <iostream>

#include "DBModel.h"
#include "Constants.h"

// Constants
const string ACCOUNTSDBPATH = "data/accounts.bin";

class Account {
    
    private:
        char name[MAXFLD];
        char email[MAXFLD];
        char passw[MAXFLD];
        char cartdb[MAXFLD];
        char histdb[MAXFLD];
        bool is_admin;

    public:
        Account();
        Account(string, string, string, string, string, bool);

        // Setters

        /// @brief Setter for account name
        /// @param name New name of user
        void setName(string name);
        
        /// @brief Setter for account email
        /// @param email New email of user
        void setEmail(string email);

        /// @brief Setter of account password
        /// @param passw New password of user
        void setPassw(string passw);
        
        // Getters
        
        /// @brief Getter for account name
        /// @return Account name
        string getName();

        /// @brief Getter for account email
        /// @return Account email
        string getEmail();

        /// @brief Getter for account password
        /// @return Account password
        string getPassw();

        /// @brief Getter for cart database path
        /// @return Cart database path
        string getCartDBPath();

        /// @brief Getter for purchase history database path
        /// @return Purchase history database path
        string getHistDBPath();

        /// @brief Check if account is admin
        /// @return True if admin
        bool isAdmin();
        
        // Other Methods

        /// @brief Display the account details
        void display() const;


};

#endif /* ACCOUNT_H */

