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
#include "Cart.h"
#include "Catalog.h"

class User : public ProfileBase {
    private:
    DBModel<Cart>* cart;
    
    public:
        User(Account*);
        ~User();
    
        // Methods
        Status main();
        void viewCart();
        void shopCatalog();
        void remFrmCart();
        
        
    

};

#endif /* USER_H */

