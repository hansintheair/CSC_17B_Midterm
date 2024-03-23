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

#include <cstring>
using namespace std;

#include "UsrAccntController.h"
#include "UsrAccntView.h"

UsrAccntController::UsrAccntController(Account *userAcct, UsrAccntsModel *acctsModel, CatalogModel *catalogModel, CatalogModel *cartModel, UsrAccntView *usrAcctView) {
    this->userAcct = userAcct;
    this->acctsModel = acctsModel;
    this->catalogModel = catalogModel;
    this->cartModel = cartModel;
    this->usrAcctView = usrAcctView;
}

void UsrAccntController::main() {
    bool logout = false;
    char input;
    while (!logout) {
        input = usrAcctView->mainMenu(userAcct->name);
        input = tolower(input);
        switch (input) {
            case 'a':
                profileMenu();
                break;
            case 'b':
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

void UsrAccntController::profileMenu() {
    bool back = false;
    char input;
    while (!back) {
        input = usrAcctView->profileMenu(userAcct);
        input = tolower(input);
        switch (input) {
            case 'a':
                changeEmail();
                break;
            case 'b':
                break;
            case 'q': //Logout
                cout << "\n";
                back = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "\n";
}

void UsrAccntController::changeEmail() {

    string newEmail;
    usrAcctView->newEmail(newEmail);

    strncpy(userAcct->email, newEmail.c_str(), MAXFLD - 1);

    short unsigned int code;
    code = acctsModel->repAcct(userAcct->name, *userAcct);
    if (code == 1) {
        usrAcctView->acctDataCrrptErr();
    } else {
        code = acctsModel->save();
        if (code == 1) {
            usrAcctView->acctSaveErr();
        }
    }




}
