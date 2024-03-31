/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AdminView.h
 * Author: hanne
 *
 * Created on March 29, 2024, 5:35 PM
 */

#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include "CatalogItem.h"

class AdminView {
public:
    AdminView();
    char mainMenu(const string&);
    void addAccnt(string&, string&, string&, bool&);
    void getPassw(const string&, string&, string);
    void getAccountName(string&);
    void accntExistErr();
    void remAccnt();
    void viewCatalog(const CatalogItem*, int);
    void getNewItem(CatalogItem& newItem);
    void getItemName(string& name);
    void chgPasswSuccess();
    void acctDataCrrptErr();
    void acctValidtErr();
    void acctSaveErr();
private:

};

#endif /* ADMINVIEW_H */

