/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UsrAccntView.cpp
 * Author: hanne
 * 
 * Created on March 21, 2024, 5:56 PM
 */

#include <iostream>
using namespace std;

#include "UsrAccntView.h"

char UsrAccntView::mainMenu(const string& username) {
    cout << "\n--Big4Shopping--\n";
    cout << "--Signed in as " << username << "\n\n";
    cout << "A - User Profile\n";
    cout << "B - Shopping cart\n";
    cout << "C - Shop the catalog\n";
    cout << "Q - Logout\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

char UsrAccntView::profileMenu(const Account* usrAcct) {
    cout << "\n--Profile\n";
    cout << "Username: " << usrAcct->name << "\n";
    cout << "E-mail: " << usrAcct->email << "\n\n";

    cout << "A - Change e-mail\n";
    cout << "B - Change password\n";
    cout << "Q - Exit menu\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

void UsrAccntView::newEmail(string& email) {
    cout << "\n--Change Email\n";
    cout << "New e-mail: ";
    getline(cin, email);
}

void UsrAccntView::getPassw(const string& username, string& passw, string adj) {
    cout << "Enter " << (adj.length() > 0 ? (adj + " ") : "") << "password for " << username << ": ";
    getline(cin, passw);
}

void UsrAccntView::chgPasswSuccess() {
    cout << "Password change succeeded.\n";
}

void UsrAccntView::acctDataCrrptErr() {
    cout << "Error: Account data corruption.\n";
}

void UsrAccntView::acctSaveErr() {
    cout << "Error: Failed to save profile data.\n";
}

void UsrAccntView::acctValidtErr() {
    cout << "Error: Invalid password.\n";
}