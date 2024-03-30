/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   UsrAccntView.h
 * Author: hanne
 *
 * Created on March 21, 2024, 5:56 PM
 */

#ifndef USRACCNTVIEW_H
#define USRACCNTVIEW_H

#include "Account.h"
#include "CatalogItem.h"
#include "CartItem.h"

class UsrAccntView {
public:
    char mainMenu(const string&);
    char profileMenu(const Account*);
    void newEmail(string&);
    void getPassw(const string&, string&, string);
    void getSearchName(string&);
    void shopCtlgTitle();
    void remCartItmTitle();
    void placeOrderTitle();
    void viewCartTitle();
    short unsigned int getQuantity(unsigned int&);
    char addToCartPrmpt(const string&, const unsigned int, const float);
    char placeOrdrPrmpt();
    void viewCatalog(const CatalogItem*, int);
    void viewCartItem(const string&, const string&, const unsigned int, const float);
    void dispGrndTtl(float);
    void orderPlaced();
    void chgPasswSuccess();
    void acctDataCrrptErr();
    void acctSaveErr();
    void acctValidtErr();
    void itemExistErr();
    void itemSaveErr();
    void quantityErr(unsigned int, const string&);
    void cartFullErr();
    void outOfRangeErr();
    void invValErr();
    void failToUpdtErr(const string&);
    void failOrderErr();
    void blank();
private:

};

#endif /* USRACCNTVIEW_H */

