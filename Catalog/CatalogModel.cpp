/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CatalogModel.cpp
 * Author: hanne
 * 
 * Created on March 16, 2024, 3:40 PM
 */

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "CatalogModel.h"

CatalogModel::CatalogModel(string catalogDB) {

    // open file
    fstream file;
    file.open(catalogDB, ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file";
        return;
    }

    // get size of catalog database
    file.read(reinterpret_cast<char*> (&numItems), sizeof (numItems));

    CatalogItem tempItem;
    for (int i = 0; i < numItems; i++) {
        file.read(reinterpret_cast<char*> (&tempItem), sizeof (CatalogItem));
        catalog[i].name = tempItem.name;
        catalog[i].desc = tempItem.desc;
        catalog[i].quant = tempItem.quant;
        catalog[i].price = tempItem.price;
    }
}

CatalogModel::CatalogModel(const CatalogModel& orig) {
}

CatalogModel::~CatalogModel() {
}

