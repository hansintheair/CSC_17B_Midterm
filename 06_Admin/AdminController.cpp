/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminController.cpp
 * Author: hanne
 * 
 * Created on March 29, 2024, 5:35 PM
 */

using namespace std;

#include "AdminController.h"

AdminController::AdminController(Account* adminAcct, UsrAccntsModel *acctsModel, CatalogModel *catalogModel, AdminView *adminView) {
    this->adminAcct = adminAcct;
    this->acctsModel = acctsModel;
    this->catalogModel = catalogModel;
    this->adminView = adminView;
}

void AdminController::main() {
    bool logout = false;
    char input;
    while (!logout) {
        input = adminView->mainMenu(adminAcct->name);
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
            case 'g':
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
}

