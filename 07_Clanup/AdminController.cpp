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
#include "CartModel.h"
#include "Generics.h"

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
            case 'a':  //Change password
                changePassw();
                break;
            case 'b':  //List accounts
                acctsModel->display();
                break;
            case 'c':  //Add account
                newAccount();
                break;
            case 'd':  //Delete account
                delAccount();
                break;
            case 'e':  //View catalog
                showCatalog();
                break;
            case 'f':  //Add catalog item
                addCtlgItem();
                break;
            case 'g':  //Remove catalog item
                remCtlgItem();
                break;
            case 'h':  //Update catalog item
                repCtlgItem();
                break;
            case 'i':  // DEBUG
                remCtlgItemI();
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

void AdminController::changePassw() {

    string oldPassw, newPassw;

    adminView->getPassw(adminAcct->name, oldPassw, "old");
    if (!validatePassw(oldPassw)) {
        adminView->acctValidtErr();
        return;
    }

    adminView->getPassw(adminAcct->name, newPassw, "new");

    strncpy(adminAcct->passw, newPassw.c_str(), MAXFLD - 1);

    short unsigned int code;
    code = acctsModel->repAcct(adminAcct->name, *adminAcct);
    if (code == 1) {
        adminView->acctDataCrrptErr();
    } else {
        code = acctsModel->save();
        if (code == 1) {
            adminView->acctSaveErr();
        }
    }
}

bool AdminController::validatePassw(string& passw) {
    if (passw == adminAcct->passw) {
        return true;
    }
    return false;
}

void AdminController::newAccount(){
    
    string username, email, passw;
    bool admin;
    adminView->addAccnt(username, email, passw, admin);
    Account temp_acct;
    strncpy(temp_acct.name, username.c_str(), MAXFLD - 1);
    strncpy(temp_acct.email, email.c_str(), MAXFLD - 1);
    strncpy(temp_acct.passw, passw.c_str(), MAXFLD - 1);
    temp_acct.admin = admin;

    if (!admin) {
        strncpy(temp_acct.cartdb, ("data/" + string(temp_acct.name) + ".bin").c_str(), MAXFLD - 1);
        CartModel::createDB(temp_acct.cartdb);
    }
    else {
        strncpy(temp_acct.cartdb, "", MAXFLD - 1);
    }

    acctsModel->addAcct(temp_acct);
    acctsModel->save();
}

void AdminController::delAccount(){
    string search;
    adminView->getAccountName(search);

    if (search != "admin"){
        short unsigned int code = acctsModel->delAcct(search);
        if (code > 0) {
            adminView->accntExistErr();
            return;
        }
        acctsModel->save();
        cout << "Successfully deleted account.\n";
    }
    else {
        cout << "admin is the primary admin account and cannot be deleted.\n";
    }
}

void AdminController::showCatalog() {
    adminView->viewCatalog(catalogModel->getItems(), catalogModel->getSize());
}

void AdminController::addCtlgItem() {
    cout << "--Add item to Catalog\n";
    
    CatalogItem tmpItem;
    adminView->getNewItem(tmpItem);
    
    catalogModel->addItem(tmpItem);
    catalogModel->save();
    
    cout << "Item added\n";
}

void AdminController::remCtlgItem() {
    cout << "--Remove item from Catalog\n";
    
    string item_name;
    adminView->getItemName(item_name);
    
    short unsigned int code;
    code = catalogModel->delItem(item_name);
    if (code > 0) {
        cout << "Error: That item does not exist.\n";
        return;
    }
    
    catalogModel->save();
    cout << "Item removed\n";
}

void AdminController::remCtlgItemI() {
    cout << "--Remove item from Catalog\n";
    
    int i;
    cout << "Index position of item: ";
    getNumeric(i);
    
    short unsigned int code;
    code = catalogModel->delItem(i);
    if (code > 0) {
        cout << "Error: That item does not exist.\n";
        return;
    }
    
    catalogModel->save();
    cout << "Item removed\n";
    cin.ignore();
}

void AdminController::repCtlgItem() {
    cout << "--Update item in Catalog\n";
       
//    cout << "NAME: " << item_name << "\n";  //DEBUG
    
    string item_name;
    adminView->getItemName(item_name);
    
    CatalogItem* item = catalogModel->getItem(item_name);
    if (item == nullptr) {
        cout << "Item " << item_name << " does not exist.\n";
        return;
    }
    
//    cout << "NAME: " << item->name << "\n";  //DEBUG
    
    cout << "\nEnter new values for the item.\n";
    adminView->getNewItem(*item);
    
    catalogModel->repItem(item_name, *item);
    catalogModel->save();    
}
