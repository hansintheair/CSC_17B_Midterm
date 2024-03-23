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

class UsrAccntController {
private:
    Account *userAcct;
    UsrAccntsModel *acctsModel;
    CatalogModel *catalogModel;
    CatalogModel *cartModel;
    UsrAccntView *usrAcctView;
public:
    UsrAccntController(Account*, UsrAccntsModel*, CatalogModel*, CatalogModel*, UsrAccntView*);
    void main();
    void profileMenu();
    void changeEmail();


};

#endif /* USRACCNTCONTROLLER_H */

