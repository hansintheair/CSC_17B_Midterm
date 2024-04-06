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

class Account {
    
    private:
        char name[MAXFLD];
        char email[MAXFLD];
        char passw[MAXFLD];
        char cartdb[MAXFLD];
        bool is_admin;

    public:
        Account();
        Account(string, string, string, string, bool);

        // Setters
        void setName(string);
        void setEmail(string);
        void setPassw(string);
        // Getters
        string getName();
        string getEmail();
        string getPassw();
        bool isAdmin();
        
        // Other Methods
        void display();


};

#endif /* ACCOUNT_H */

