/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   HomeController.cpp
 * Author: hanne
 * 
 * Created on March 18, 2024, 6:21 PM
 */

#include <string>
#include <cstring>
using namespace std;

#include "HomeController.h"

HomeController::HomeController(UsrAccntsModel *accntsModel, HomeView *homeView, CatalogModel *catlgModel) {
    this->accntsModel = accntsModel;
    this->homeView = homeView;
    this->catlgModel = catlgModel;
}

void HomeController::main() {
    bool quit = false;
    char input;
    while (!quit) {
        input = homeView->menu();
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

void HomeController::createUser() {

    string username, email, passw;
    homeView->userCreate(username, email, passw);
    Account temp_acct;
    strncpy(temp_acct.name, username.c_str(), MAXFLD - 1);
    strncpy(temp_acct.email, email.c_str(), MAXFLD - 1);
    strncpy(temp_acct.passw, passw.c_str(), MAXFLD - 1);
    temp_acct.admin = false;

    strncpy(temp_acct.cartdb, ("data/" + string(temp_acct.name) + ".bin").c_str(), MAXFLD - 1);
    CatalogModel::createDB(temp_acct.cartdb);

    accntsModel->addAcct(temp_acct);
    accntsModel->save();
}

void HomeController::loginUser() {
    string username, passw;
    homeView->userLogin(username, passw);

//    cout << "\nAttempting login for " << username << "\n";  //DEBUG
    Account *acct = nullptr;
    acct = accntsModel->getAcct(username, passw);
    
    if (!(acct==nullptr)){
//        cout << "cart database: " << acct->cartdb << "\n";  //DEBUG
        CatalogModel cartModel = CatalogModel(acct->cartdb);
        UsrAccntView userAcctView = UsrAccntView();

        UsrAccntController(
            acct,
            accntsModel,
            catlgModel,
            &cartModel,
            &userAcctView
        ).main();
    }
}

HomeController::~HomeController() {
//    delete homeView, accntsModel;
//    homeView = nullptr;
//    accntsModel = nullptr;
}
