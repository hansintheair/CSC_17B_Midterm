/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Admin.h
 * Author: hanne
 *
 * Created on April 6, 2024, 10:14 AM
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

using namespace std;

#include "Account.h"
#include "Generics.h"

class Admin {
    private:
    Account* account;

    public:
        Admin(Account*);
    
        // Methods
        void main();

};

#endif /* ADMIN_H */

