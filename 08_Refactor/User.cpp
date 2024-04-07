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

User::User(Account* account) : ProfileBase(account) {
    this->cart = new DBModel<Cart>(account->getCartDBPath());
}

User::~User(){
    // Clean up managed memory
    delete this->cart;
    this->cart = nullptr;
    delete this->catalog;
    this->catalog = nullptr;
}

Status User::main() {
    bool logout = false;
    char input;
    while (!logout) {
        cout << "\n---User Menu\n";
        cout << " - Signed in: " << account->getName() << "\n";
        cout << "[A] View profile Info\n";
        cout << "[B] Change e-mail\n";
        cout << "[C] Change password\n";
        cout << "[D] View Catalog\n";
        cout << "[E] Shop Catalog\n";
        cout << "[F] View Cart\n";
        cout << "[G] Remove from Cart\n";
        cout << "[H] Place order\n";
        cout << "[Q] Logout\n\n";
        
        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
                viewProfile();
                break;
            case 'b':
                changeEmail();
                break;
            case 'c':
                changePassw();
                break;
            case 'd':
                viewCatalog();
                break;
            case 'e':
                break;
            case 'f':
                viewCart();
                break;
            case 'g':
//                removeFrmCrt();
                break;
            case 'h':
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
//    cout << "STATUS: " << status << "\n";  //DEBUG
    return status;
}

void User::viewCart() {
    cout << "\n-- Cart\n";
    cart->open();
    if (cart->count() > 0) {
        cart->display();
    }
    else {
        cout << "\n   Cart is empty\n";
    }
    cart->close();
}
