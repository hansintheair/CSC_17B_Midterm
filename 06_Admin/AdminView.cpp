/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminView.cpp
 * Author: hanne
 * 
 * Created on March 29, 2024, 5:35 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;

#include "AdminView.h"

AdminView::AdminView() {
}

char AdminView::mainMenu(const string& username) {
    cout << "\n--Big4Shopping--\n";
    cout << "--Signed in as " << username << "\n";
    cout << "--ADMIN\n\n";
    cout << "A - Set Password\n";
    cout << "B - List accounts\n";
    cout << "C - Create new account\n";
    cout << "D - Remove account\n";
    cout << "E - View Catalog\n";
    cout << "F - Add item to Catalog\n";
    cout << "G - Remove item from Catalog\n";
    cout << "H - Update item in Catalog\n";
    cout << "Q - Logout\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

void AdminView::addAccnt(string& username, string& email, string& passw, bool& admin) {
    cout << "\n--Add user\n";
    cout << "Username: ";
//    cin.ignore();
    getline(cin, username);
    cout << "e-mail address: ";
    getline(cin, email);
    cout << "password: ";
    getline(cin, passw);
    
    bool valid = false;
    char choice;
    while (!valid){
        cout << "admin: ";
        cin.get(choice);
        cin.ignore();
        choice = tolower(choice);

        switch (choice) {
            case 'y':
                admin = true;
                valid = true;
                break;
            case 'n':
                admin = false;
                valid = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        }
    }
}

void AdminView::getPassw(const string& username, string& passw, string adj) {
    cout << "\n--Change password\n";
    cout << "Enter " << (adj.length() > 0 ? (adj + " ") : "") << "password for " << username << ": ";
    getline(cin, passw);
}

void AdminView::getAccountName(string& accntName) {
    cout << "\n--Delete account\n";
    cout << "Enter the account name: ";
    getline(cin, accntName);
}

void AdminView::viewCatalog(const CatalogItem* catalogItems, int size) {
    cout << "\n--Catalog\n\n";
    for (int i = 0; i < size; i++) {
        cout << "# " << i << "\n";
        cout << "Name: " << catalogItems[i].name << "\n";
        cout << "Description: " << catalogItems[i].desc << "\n";
        cout << "Price $" << fixed << setprecision(2) << catalogItems[i].price << "\n";
        cout << "Quantity: " << catalogItems[i].quant << "\n";
        if (i < size - 1) {
            cout << "\n";
        }
    }
}

void AdminView::getNewItem(CatalogItem& newItem) {
    string temp_input;
    cout << "Item name: ";
    getline(cin, temp_input);
    strncpy(newItem.name, temp_input.c_str(), MAXNAME -1 );
    cout << "Item description: ";
    getline(cin, temp_input);
    strncpy(newItem.desc, temp_input.c_str(), MAXDESC - 1);
    cout << "Item price: ";
    cin >> newItem.price;
    cout << "Item quantity: ";
    cin >> newItem.quant;
    cin.ignore();
}

void AdminView::getItemName(string& name) {
    cout << "Item name: ";
    getline(cin, name);
}

void AdminView::chgPasswSuccess() {
    cout << "Password change succeeded.\n";
}

void AdminView::acctDataCrrptErr() {
    cout << "Error: Account data corruption.\n";
}

void AdminView::acctValidtErr() {
    cout << "Error: Invalid password.\n";
}

void AdminView::acctSaveErr() {
    cout << "Error: Failed to save profile data.\n";
}

void AdminView::accntExistErr() {
    cout << "Error: That account does not exist.\n";
}