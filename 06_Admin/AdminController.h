/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AdminController.h
 * Author: hanne
 *
 * Created on March 29, 2024, 5:35 PM
 */

#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "AdminController.h"
#include "Account.h"
#include "UsrAccntsModel.h"
#include "CatalogModel.h"
#include "AdminView.h"

class AdminController {
private:
    Account *adminAcct;
    UsrAccntsModel *acctsModel;
    CatalogModel *catalogModel;
    AdminView *adminView;
public:
    AdminController(Account*, UsrAccntsModel*, CatalogModel*, AdminView*);
    void main();
    void changePassw();
    bool validatePassw(string&);
    void newAccount();
    void delAccount();
    void showCatalog();
    void addCtlgItem();
    void remCtlgItem();
    void remCtlgItemI();
    void repCtlgItem();
};

#endif /* ADMINCONTROLLER_H */

