/** \file */

/**
 * \anchor Admin
 * \class Admin
 * This class serves as the Admin controller. It contains the nescessary functions 
 * to fascilitate the admin user role interactions.
 *  
 * Admin accounts have privilege to view/edit another Account, view store earnings, or modify the store Catalog.
 * 
 * Admin accounts are created or logged in from the Home class main menu.
 * 
 * There is one primary admin that cannot be deleted, called admin.
 * 
 * Admin record attributes are stored in Account objects.
 */

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
#include "ProfileBase.h"
#include "User.h"

class Admin : public ProfileBase{
    private:
    DBModel<Account>* accounts;

    public:
        Admin(Account*, DBModel<Account>*);
    
        // Methods
        
        /// @brief Main menu of Admin
        /// @return Action to take on AccountDB record
        Status main();

        /// @brief Display catalog
        void viewCatalog() override;

        /// @brief Display profile
        void viewProfile() override;
        
        /// @brief Delete user account
        void delSelfAccount() override;

        /// @brief Display accounts
        void viewAccounts();

        /// @brief Create a new account
        void createAccount();

        /// @brief Delete an existing account
        void delAccount();

        /// @brief Add a new item to the catalog
        void addCatalogItem();
        
        /// @brief Update an existing item in the catalog
        void updCatalogItem();

        /// @brief Delete an item from the catalog
        void delCatalogItem();

        /// @brief View the total earnings of the store
        void viewEarningsHist();
        
        /// @brief View and/or edit user profile, cart, and view orders history
        void viewEditUser();
};

#endif /* ADMIN_H */

