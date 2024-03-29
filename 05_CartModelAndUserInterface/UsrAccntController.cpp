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

UsrAccntController::UsrAccntController(Account *userAcct, UsrAccntsModel *acctsModel, CatalogModel *catalogModel, CartModel *cartModel, UsrAccntView *usrAcctView) {
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
            case 'd':
                showCart();
                break;
            case 'e':
                removeFrmCrt();
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

void UsrAccntController::showCart() {
    usrAcctView->blank();
    CartItem* items = cartModel->getItems();
    unsigned int size = cartModel->getSize();
    float total = 0.0;
    CatalogItem cat_item;
    for (unsigned int i = 0; i < size; i++) {
        cat_item = *catalogModel->getItem(items[i].name);
        usrAcctView->viewCartItem(items[i].name, cat_item.desc, items[i].quant, items[i].quant * cat_item.price);
        total += items[i].quant * cat_item.price;
        if (i < size - 1) {
            usrAcctView->blank();
        }
    }
    usrAcctView->blank();
    usrAcctView->dispGrndTtl(total);
}

void UsrAccntController::shopCatalog() {

    usrAcctView->shopCtlgTitle();

    // Search for catalog item
    string search;
    usrAcctView->getSearchName(search);

    CatalogItem* item = catalogModel->getItem(search);
    if (item == nullptr) {
        usrAcctView->itemExistErr();
        return;
    }

    // Get quantity to buy
    unsigned int quant;
    unsigned short int code;
    code = usrAcctView->getQuantity(quant);
    if (code == 1) {
        usrAcctView->outOfRangeErr();
        return;
    } else if (code == 2) {
        usrAcctView->invValErr();
    }

    if (item->quant < quant) {
        usrAcctView->quantityErr(item->quant, search);
        return;
    }

    // Prompt user to OK adding item to cart
    bool cancel;
    char input;
    CartItem temp_item;
    CartItem* temp_cart_item = cartModel->getItem(item->name);
    strncpy(temp_item.name, item->name, MAXNAME);
    temp_item.quant = quant;
    while (!cancel) {
        input = usrAcctView->addToCartPrmpt(item->name, temp_item.quant, item->price);
        input = tolower(input);
        switch (input) {
            case 'y': //Add item to shopping cart

                // Update existing cart item
                if (!(temp_cart_item == nullptr)) {
                    temp_item = temp_item + *temp_cart_item;
                    //                    cout << "NAME: " << temp_item.name << "\n";  //DEBUG
                    //                    cout << "QUANT: " << temp_item.quant << "\n";  //DEBUG
                    code = cartModel->repItem(temp_item.name, temp_item);
                    if (code > 0) {
                        usrAcctView->cartFullErr();
                        return;
                    }
                }                    // Add new cart item
                else {
                    code = cartModel->addItem(temp_item);
                    if (code > 0) {
                        usrAcctView->cartFullErr();
                        return;
                    }
                }
                code = cartModel->save();
                cout << code;
                if (code == 1) {
                    usrAcctView->itemSaveErr();
                    return;
                }
                return;
            case 'n': //Cancel
                cout << "\n";
                cancel = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
}

void UsrAccntController::removeFrmCrt() {

    usrAcctView->remCartItmTitle();

    string search;
    usrAcctView->getSearchName(search);

    short unsigned int code = cartModel->delItem(search);
    if (code > 0) {
        usrAcctView->itemExistErr();
        return;
    }
}

void UsrAccntController::placeOrder() {
    
}