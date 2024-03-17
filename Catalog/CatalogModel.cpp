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
#include <cstring>
using namespace std;

#include "CatalogModel.h"

CatalogModel::CatalogModel(string catalog_db) {

    // open file
    fstream file;
    file.open(catalog_db, ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    // get size of catalog database
    file.read(reinterpret_cast<char*> (&num_items), sizeof (num_items));

    CatalogItem temp_item;
    for (int i = 0; i < num_items; i++) {
        file.read(reinterpret_cast<char*> (&temp_item), sizeof (CatalogItem));
        strncpy(catalog[i].name, temp_item.name, MAXNAME - 1);
        strncpy(catalog[i].desc, temp_item.desc, MAXDESC - 1);
        catalog[i].quant = temp_item.quant;
        catalog[i].price = temp_item.price;
    }
}

CatalogModel::CatalogModel(const CatalogModel& orig) {
}

CatalogModel::~CatalogModel() {
}

void CatalogModel::createDB(string catalog_db) {

    fstream file;

    // check file existence
    file.open(catalog_db, ios::in | ios::binary);
    if (!file) {
        file.open(catalog_db, ios::out | ios::binary);
        short unsigned int num_items = 0;
        file.write(reinterpret_cast<char*> (&num_items), sizeof (num_items));
    }
    else {
        cout << "File " << catalog_db << " already exists.\n";
    }
}

