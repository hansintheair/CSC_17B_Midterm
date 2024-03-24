/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   CartModel.h
 * Author: hanne
 *
 * Created on March 24, 2024, 4:01 PM
 */

#ifndef CARTMODEL_H
#define CARTMODEL_H

#include "CartItem.h"


class CartModel {
private:
    string catalog_db;
    CartItem catalog[MAXITEMS];
    unsigned short int num_items;
    short int findItem(string);
public:
    CartModel(string);
//    CatalogModel(const CatalogModel& orig);
    CartItem* getItems();
    CartItem* getItem(string);
    short unsigned int getSize();
    short unsigned int addItem(const CartItem&);
    void repItem(string, const CartItem&);
    void delItem(string);

    short unsigned int save();
    static void createDB(string);
//    virtual ~CatalogModel();
};

#endif /* CARTMODEL_H */

