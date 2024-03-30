/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   UsrAccntController.h
 * Author: hanne
 *
 * Created on March 21, 2024, 5:56 PM
 */

#ifndef USRACCNTCONTROLLER_H
#define USRACCNTCONTROLLER_H

using namespace std;

#include "Account.h"
#include "UsrAccntsModel.h"
#include "UsrAccntView.h"
#include "CatalogModel.h"
#include "CartModel.h"

class UsrAccntController {
private:
    Account *userAcct;
    UsrAccntsModel *acctsModel;
    CatalogModel *catalogModel;
    CartModel *cartModel;
    UsrAccntView *usrAcctView;
public:
    UsrAccntController(Account*, UsrAccntsModel*, CatalogModel*, CartModel*, UsrAccntView*);
    void main();
    void profileMenu();
    void changeEmail();
    void changePassw();
    bool validatePassw(string&);
    void showCatalog();
    void showCart();
    void shopCatalog();
    void removeFrmCrt();
    void placeOrder();


};

#endif /* USRACCNTCONTROLLER_H */

