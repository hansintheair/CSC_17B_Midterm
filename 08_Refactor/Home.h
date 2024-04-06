/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Home.h
 * Author: hanne
 *
 * Created on April 6, 2024, 8:28 AM
 */

#ifndef HOME_H
#define HOME_H

#include <iostream>

using namespace std;

#include "DBModel.h"
#include "Account.h"
#include "Generics.h"

class Home {

    private:
        DBModel<Account> accounts;

    public:
        Home();
        void main();

};

#endif /* HOME_H */

