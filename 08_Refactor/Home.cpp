/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Home.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 8:28 AM
 */

#include "Home.h"
#include "Cart.h"

Home::Home(DBModel<Account>* accounts) {
    this->accounts = accounts;
}

void Home::main() {
    bool quit = false;
    char input;
    
    cout << "\n--=Big4Shopping=--\n";
    
    while (!quit) {
        cout << "\n-- Main menu\n";
        cout << "[A] Login\n";
        cout << "[B] Create user\n";
        cout << "[Q] Exit\n\n";

        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
                loginUser();
                break;
            case 'b':
                createUser();
                break;
            case 'q': //Quit
                cout << "\n";
                quit = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "Exiting program\n";    
}

/// @brief Create a new user
void Home::createUser() {
    
    // Get new user data
    string name, email, passw, cart;
    cout << "\n-- Create user\n";
    cout << "   Enter username\n";
    safeGetLine(name, MAXFLD);
    cout << "   Enter e-mail address\n";
    safeGetLine(email, MAXFLD);
    cout << "   Enter password\n";
    safeGetLine(passw, MAXFLD);
    
    // Create cart database for new user
    cart = "data/" + name + ".crt";
    DBModel<Cart>::create(cart);
    
    // Add new user record to accounts database
    Account record = Account(name, email, passw, cart, 0);
    accounts->open();
    accounts->add(&record);
    accounts->close();
}

/// @brief Log in the user
void Home::loginUser() {
    
    // Get user login credentials
    string name, passw;
    cout << "\n-- Login\n";
    cout << "   Enter username\n";
    safeGetLine(name, MAXFLD);
    cout << "   Enter password\n";
    safeGetLine(passw, MAXFLD);
    
    Account* user = authGetUser(name, passw);
    
    // Do nothing if authentication failed.
    if (user == nullptr) {
        return;
    }
    
    // Log in (open user account menu)
    // TODO    
}

/// @brief Authenticate the user credentials and return a user if authenticated, otherwise return nullptr.
/// @param name The name of the account.
/// @param passw The password for the account.
/// @return The user account if authenticated, otherwise nullptr.
Account* Home::authGetUser(string name, string passw) {
    
    Account* user;
    int pos;
    
    // Check if account exists
    pos = accounts->find(name);
    if (!(pos < -1)) {
        cout << "\n   User not found.\n";
        delete user;
        user = nullptr;
    }
    
    // Get account
    user = accounts->get(pos);
    
    // Check if passwords match
    if (!(user->getPassw() == passw)) {
        cout << "\n   Invalid password.\n";
        delete user;
        user = nullptr;
    }
    
    return user;
}
