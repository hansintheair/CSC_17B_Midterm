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

class UsrAccntView {
public:
    char mainMenu(const string&);
    char profileMenu(const Account*);
    void newEmail(string&);
    void getPassw(const string&, string&, string);
    void getSearchName(string&);
    short unsigned int getQuantity(unsigned int&);
    char addToCartPrmpt(const string&, const unsigned int, const float);
    void viewCatalog(const CatalogItem*, int);
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
    void blank();
private:

};

#endif /* USRACCNTVIEW_H */

