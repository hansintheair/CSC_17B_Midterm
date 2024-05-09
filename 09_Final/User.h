/** \file */

/**
 * \anchor User
 * \class User
 * This class serves as the User controller. It contains the nescessary functions 
 * to fascilitate the user role interactions.
 *  
 * User accounts can shop the Catalog and place orders.
 * 
 * User accounts are created or logged in from the Home class main menu.
 * 
 * User record attributes are stored in Account objects.
 */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   User.h
 * Author: hanne
 *
 * Created on April 6, 2024, 10:47 AM
 */


#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

#include "Account.h"
#include "Generics.h"
#include "Constants.h"
#include "ProfileBase.h"
#include "Catalog.h"

class User : public ProfileBase {
    private:
    DBModel<Catalog>* cart;
    DBModel<Catalog>* hist;
    
    // Methods
    void syncCart();
    
    public:
        User(Account*);
        ~User();
    
        // Methods

        /// @brief Main menu of User
        /// @return Action to take on AccountDB record
        Status main();

        /// @brief Display cart
        /// @param total Total price of items in cart
        void viewCart(float& total);

        /// @brief Display cart
        void viewCart();

        /// @brief Display purchase history
        void viewHist();

        /// @brief Calculate lifetime total spend at store
        /// @param total Lifetime total spent at store
        void getHistTotal(float& total);

        /// @brief Shop catalog (place items in cart)
        void shopCatalog();

        /// @brief Remove item from the cart
        void remFrmCart();

        /// @brief Place (complete) an order (purchase all items in cart)
        void placeOrder();
        
};

#endif /* USER_H */

