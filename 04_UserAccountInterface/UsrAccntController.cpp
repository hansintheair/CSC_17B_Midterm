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
                showCatalog();
                break;
            case 'c':
                shopCatalog();
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
            case 'a': //Change e-mail
                changeEmail();
                break;
            case 'b': //Change password
                changePassw();
                break;
            case 'q': //Exit profile menu
                back = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
}

void UsrAccntController::changeEmail() {

    string newEmail;
    usrAcctView->newEmail(newEmail);

    strncpy(userAcct->email, newEmail.c_str(), MAXFLD - 1);

    short unsigned int code;
    code = acctsModel->repAcct(userAcct->name, *userAcct);
    if (code == 1) {
        usrAcctView->acctDataCrrptErr();
        return;
    }
    code = acctsModel->save();
    if (code == 1) {
        usrAcctView->acctSaveErr();
        return;
    }
    usrAcctView->chgPasswSuccess();
}

void UsrAccntController::changePassw() {

    string oldPassw, newPassw;

    usrAcctView->getPassw(userAcct->name, oldPassw, "old");
    if (!validatePassw(oldPassw)) {
        usrAcctView->acctValidtErr();
        return;
    }

    usrAcctView->getPassw(userAcct->name, newPassw, "new");

    strncpy(userAcct->passw, newPassw.c_str(), MAXFLD - 1);

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

bool UsrAccntController::validatePassw(string& passw) {
    if (passw == userAcct->passw) {
        return true;
    }
    return false;
}

void UsrAccntController::showCatalog() {
    usrAcctView->viewCatalog(catalogModel->getItems(), catalogModel->getSize());
}

void UsrAccntController::shopCatalog() {
    
    string search;
    usrAcctView->getSearchName(search);
    
    CatalogItem* item = catalogModel->getItem(search);
    if (item==nullptr) {
        usrAcctView->itemExistErr();
        return;
    }
    
    unsigned int quant;
    unsigned short int code;
    code = usrAcctView->getQuantity(quant);
    if (code==1) {
        usrAcctView->outOfRangeErr();
        return;
    } else if (code==2) {
        usrAcctView->invValErr();
    }
    
//    cout << "QUANTITY: " << quant << "\n";  //DEBUG
//    cout << "ALLOWED: " << item->quant << "\n";  //DEBUG
    if (item->quant < quant){
        usrAcctView->quantityErr(item->quant, search);
        return;
    }
    
    CatalogItem tempItem = *item;
    code = cartModel->addItem(tempItem);
//    cout << "CART CODE: " << code << "\n";  //DEBUG
    if (code > 0) {
        usrAcctView->cartFullErr();
    }
    code = cartModel->save();
    if (code == 1) {
        usrAcctView->itemSaveErr();
        return;
    }
}
