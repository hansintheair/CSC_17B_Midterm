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
#include <iomanip>
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

    this->catalog_db = catalog_db;
}

//CatalogModel::CatalogModel(const CatalogModel& orig) {
//}
//
//CatalogModel::~CatalogModel() {
//}

// Search for a catalog item and return its index position.

short int CatalogModel::findItem(string name) {
    short unsigned int i = 0;
    short int pos = -1;
//    cout << "Searching for " << name << "\n";  //DEBUG

    while (i < num_items) {
//        cout << "Searching catalog item #" << i << "\n";  //DEBUG
        if (catalog[i].name == name) {
            pos = i;
            break; //item found
        }
        i++;
    }
    return pos;
}

short unsigned int CatalogModel::getSize() {
    return num_items;
}

// Display all items in the catalog.

void CatalogModel::display() {
    for (int i = 0; i < num_items; i++) {
        catalog[i].display();
        cout << "\n";
    }
}
// Display a specific item in the catalog.

void CatalogModel::display(string name) {
    short int idis = findItem(name);
//    cout << "index pos: " << idis << "\n"; //DEBUG
    if (idis > -1) {//item found
        catalog[idis].display();
    }
    else {
        cout << "Item " << name << " does not exist.\n";
    }
}

// Add an item to the end of the catalog.

void CatalogModel::addItem(const CatalogItem &item) {
    catalog[num_items] = item;
    num_items++;
}

void CatalogModel::repItem(string name, const CatalogItem& new_item) {
    short int irep = findItem(name);
//    cout << "index: " << irep << "\n";  //DEBUG
    if (irep > -1) { //item found
        catalog[irep] = new_item;
    } else {
        cout << "Item " << name << " does not exist.\n";
    }
}

void CatalogModel::delItem(string name) {
    short int idel = findItem(name);
    if (idel > -1) { //item found
        for (int i = idel; i < num_items; i++) {
            catalog[i] = catalog[i + 1];
        }
        num_items--;
    } else {
        cout << "Item " << name << " does not exist.\n";
    }
}

void CatalogModel::save() {

    fstream file;

    // check file existence
    file.open(catalog_db, ios::in | ios::binary);
    if (file) {
        file.close();
        file.open(catalog_db, ios::out | ios::binary);

        // get size of catalog database
        file.write(reinterpret_cast<char*> (&num_items), sizeof (num_items));

        CatalogItem temp_item;
        for (int i = 0; i < num_items; i++) {
            //            cout << "Write record " << i << endl;
            strncpy(temp_item.name, catalog[i].name, MAXNAME - 1);
            //            cout << "NAME: " << temp_item.name << endl;
            strncpy(temp_item.desc, catalog[i].desc, MAXDESC - 1);
            //            cout << "DESC: " << temp_item.desc << endl;
            temp_item.price = catalog[i].price;
            //            cout << "PRICE: " << temp_item.price << endl;
            temp_item.quant = catalog[i].quant;
            //            cout << "QUANT: " << temp_item.quant << endl;
            file.write(reinterpret_cast<char*> (&temp_item), sizeof (CatalogItem));
        }
    } else {
        cout << "Cannot save, file " << catalog_db << " does not exist.\n";
    }

    file.close();
}

void CatalogModel::createDB(string catalog_db) {

    fstream file;

    // check file existence
    file.open(catalog_db, ios::in | ios::binary);
    if (!file) {
        file.close();
        file.open(catalog_db, ios::out | ios::binary);
        short unsigned int num_items = 0;
        file.write(reinterpret_cast<char*> (&num_items), sizeof (num_items));
    } else {
        cout << "File " << catalog_db << " already exists.\n";
    }

    file.close();
}

