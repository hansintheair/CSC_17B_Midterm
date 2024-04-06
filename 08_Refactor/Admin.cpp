/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Admin.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 10:14 AM
 */

#include "Admin.h"
#include "Constants.h"

Admin::Admin(Account* account) {
    this->account = account;
}

Status Admin::main() {

    bool logout = false;
    char input;
    Status status = CLEAN;
    while (!logout) {
        
        cout << "\n---Admin Menu\n";
        cout << " - Account: " << account->getName() << "\n";
        cout << "[A] Change Password\n";
        cout << "[B] List accounts\n";
        cout << "[C] Create new account\n";
        cout << "[D] Remove account\n";
        cout << "[E] View Catalog\n";
        cout << "[F] Add item to Catalog\n";
        cout << "[G] Remove item from Catalog\n";
        cout << "[H] Update item in Catalog\n";
        cout << "[Q] Logout\n\n";

        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':  //Change password
//                changePassw();
                break;
            case 'b':  //List accounts
//                acctsModel->display();
                break;
            case 'c':  //Add account
//                newAccount();
                break;
            case 'd':  //Delete account
//                delAccount();
                break;
            case 'e':  //View catalog
//                showCatalog();
                break;
            case 'f':  //Add catalog item
//                addCtlgItem();
                break;
            case 'g':  //Remove catalog item
//                remCtlgItem();
                break;
            case 'h':  //Update catalog item
//                repCtlgItem();
                break;
            case 'i':  // DEBUG
//                remCtlgItemI();
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

