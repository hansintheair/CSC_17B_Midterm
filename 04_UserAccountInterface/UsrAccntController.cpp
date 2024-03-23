/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UsrAccntController.cpp
 * Author: hanne
 * 
 * Created on March 21, 2024, 5:56 PM
 */

#include "UsrAccntController.h"

UsrAccntController::UsrAccntController(Account *userAcct, UsrAccntsModel *acctsModel, CatalogModel *catalogModel, CatalogModel *cartModel, UsrAccntView *usrAcctView) {
    this->userAcct = userAcct;
    this->acctsModel = acctsModel;
    this->catalogModel = catalogModel;
    this->cartModel = cartModel;
    this->usrAcctView = usrAcctView;
}

void UsrAccntController::main() {
//    bool quit = false;
//    char input;
//    while (!quit) {
//        input = homeView->mainMenu();
//        input = tolower(input);
//        switch (input) {
//            case 'a':
//                loginUser();
//                break;
//            case 'b':
//                createUser();
//                break;
//            case 'q': //Quit
//                cout << "\n";
//                quit = true;
//                break;
//            default:
//                cout << "Unknown input, please try again\n";
//        };
//    }
//    cout << "QUITTING\n";
}

UsrAccntController::~UsrAccntController() {
    delete userAcct, acctsModel, catalogModel, cartModel;
    userAcct = nullptr;
    acctsModel = nullptr;
    catalogModel = nullptr;
    cartModel = nullptr;
}

