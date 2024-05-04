/** \file */

/**
 * \anchor Home
 * \class Home
 * This class serves as the main entry point into the shopping store application. The `Home::main()` method launches 
 * the main menu from which all other parts of the application are accessible to the user. Users and admins use this page to log in.
 * 
 * User accounts:
 *   - User accounts can shop the catalog and place orders.
 * 
 * Admin accounts:
 *   - Admin accounts have the privilege to view/edit other accounts, view store earnings, or modify the store catalog.
 *   - There is one primary admin account that cannot be deleted.   
 *     Username: admin   
 *     Password: admin   
 */

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
#include "Constants.h"

class Home {

    private:
        DBModel<Account>* accounts;
    
        // Methods

        /// @brief Retrieves an authenticated user from AccountsDB.
        /// @param name The username of the user.
        /// @param passw The password of the user.
        /// @return A pointer to the user account if authentication is successful, otherwise nullptr.
        Account* authGetUser(string name, string passw);

    public:
        Home(DBModel<Account>*);
    
        // Methods
        
        /// @brief Main menu. Main entry point into the application.
        void main();

        /// @brief Create a new user
        void createUser();

        /// @brief Log in an existing user
        void loginUser();

};

#endif /* HOME_H */

