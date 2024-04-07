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

Admin::Admin(Account* account) : ProfileBase(account) {
}

Status Admin::main() {
    bool logout = false;
    char input;
    while (!logout) {
        cout << "\n---Admin Menu\n";
        cout << " - Account: " << account->getName() << "\n";
        cout << "[A] View profile info\n";
        cout << "[B] Change e-mail\n";
        cout << "[C] Change Password\n";
        cout << "[D] List accounts\n";
        cout << "[E] Create new account\n";
        cout << "[F] Remove account\n";
        cout << "[G] View Catalog\n";
        cout << "[H] Add item to Catalog\n";
        cout << "[I] Remove item from Catalog\n";
        cout << "[J] Update item in Catalog\n";
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
//                acctsModel->display();
                break;
            case 'e':
//                newAccount();
                break;
            case 'f':
//                delAccount();
                break;
            case 'g':
//                showCatalog();
                break;
            case 'h':
//                addCtlgItem();
                break;
            case 'i':
//                remCtlgItem();
                break;
            case 'j':
//                repCtlgItem();
                break;
            case 'q':
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

void Admin::viewProfile() {
    ProfileBase::viewProfile();
    cout << "   Administrator\n";
}



