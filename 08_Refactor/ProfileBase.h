/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   ProfileBase.h
 * Author: hanne
 *
 * Created on April 6, 2024, 11:41 AM
 */

#ifndef PROFILEBASE_H
#define PROFILEBASE_H

#include <iostream>

using namespace std;

#include "Account.h"
#include "Generics.h"

class ProfileBase {
    protected:
        Account* account;
        Status status;

    public:
        ProfileBase(Account*);
    
        // Methods
        virtual void viewProfile();
        void changePassw();
        void changeEmail();

};

#endif /* PROFILEBASE_H */

