/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   CatalogItem.h
 * Author: hanne
 *
 * Created on March 16, 2024, 3:45 PM
 */

#ifndef CATALOGITEM_H
#define CATALOGITEM_H

#include <cstring>
using namespace std;

#include "Constants.h"

struct CatalogItem{
    char name[MAXNAME];  // Name doubles as ID, must be unique.
    char desc[MAXDESC];
    float price;
    unsigned int quant;
    
    CatalogItem operator-(const CatalogItem& other) const {
        CatalogItem temp_item;
        strncpy(temp_item.name, name, MAXNAME - 1);
        strncpy(temp_item.desc, desc, MAXDESC - 1);
        temp_item.price = price;
        temp_item.quant = quant;
        return temp_item;
    }
};

#endif /* CATALOGITEM_H */

