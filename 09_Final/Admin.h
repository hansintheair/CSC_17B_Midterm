/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Admin.h
 * Author: hanne
 *
 * Created on April 6, 2024, 10:14 AM
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

using namespace std;

#include "Account.h"
#include "Generics.h"
#include "ProfileBase.h"
#include "User.h"

class Admin : public ProfileBase{
    private:
    DBModel<Account>* accounts;

    public:
        Admin(Account*, DBModel<Account>*);
    
        // Methods
        Status main();
        void viewCatalog() override;
        void viewProfile() override;
        void viewAccounts();
        void createAccount();
        void delAccount();
        void addCatalogItem();
        void updCatalogItem();
        void delCatalogItem();
};

#endif /* ADMIN_H */

