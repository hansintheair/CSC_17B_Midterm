/** \file */

/**
 * \anchor ProfileBase
 * \class ProfileBase
 * This class serves as the Baseclass for both the User and Admin controllers. It contains the shared functions 
 * to fascilitate the user and admin role interactions.
 *  
 * ProfileBase record attributes are stored in Account objects.
 */

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
#include "Catalog.h"
#include "Generics.h"

class ProfileBase {
    protected:
        Account* account;
        DBModel<Catalog>* catalog;
        Status status;

    public:
        ProfileBase(Account*);
    
        // Methods

        /// @brief View user profile
        virtual void viewProfile();

        /// @brief View store catalog
        virtual void viewCatalog();

        /// @brief Change user password
        void changePassw();

        /// @brief Change user email
        void changeEmail();


};

#endif /* PROFILEBASE_H */

