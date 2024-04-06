/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   User.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 10:47 AM
 */

#include "User.h"

User::User(Account* account) {
    this->account = account;
}

Status User::main() {
    bool logout = false;
    char input;
    Status status = CLEAN;
    while (!logout) {
        
        cout << "\n---User Menu--\n";
        cout << " - Signed in: " << account->getName() << "\n";
        cout << "[A] User Profile\n";
        cout << "[B] View Catalog\n";
        cout << "[C] Shop Catalog\n";
        cout << "[D] View Cart\n";
        cout << "[E] Remove from Cart\n";
        cout << "[F] Place order\n";
        cout << "[Q] Logout\n\n";
        
        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
//                profileMenu();
                break;
            case 'b':
//                showCatalog();
                break;
            case 'c':
//                shopCatalog();
                break;
            case 'd':
//                showCart();
                break;
            case 'e':
//                removeFrmCrt();
                break;
            case 'f':
//                placeOrder();
                break;
            case 'q': //Logout
                cout << "\n";
                logout = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "Logging out\n";
    return status;
}

