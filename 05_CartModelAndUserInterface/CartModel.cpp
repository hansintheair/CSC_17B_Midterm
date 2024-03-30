/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CartModel.cpp
 * Author: hanne
 * 
 * Created on March 24, 2024, 4:01 PM
 */

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "CartModel.h"

CartModel::CartModel(string catalog_db) {

    // open file
    fstream file;
    file.open(catalog_db, ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    // get size of catalog database
    file.read(reinterpret_cast<char*> (&num_items), sizeof (num_items));

    CartItem temp_item;
    for (int i = 0; i < num_items; i++) {
        file.read(reinterpret_cast<char*> (&temp_item), sizeof (CartItem));
        strncpy(catalog[i].name, temp_item.name, MAXNAME - 1);
        catalog[i].quant = temp_item.quant;
    }

    this->catalog_db = catalog_db;
}

//CartModel::CartModel(const CartModel& orig) {
//}
//
//CartModel::~CartModel() {
//}

// Search for a catalog item and return its index position.

short int CartModel::findItem(string name) {
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

short unsigned int CartModel::getSize() {
    return num_items;
}

// Display all items in the catalog.

CartItem* CartModel::getItems() {
    return catalog;
}

// Display a specific item in the catalog.

CartItem* CartModel::getItem(string name) {
    short int idis = findItem(name);
    //    cout << "index pos: " << idis << "\n"; //DEBUG
    if (idis > -1) {//item found
        return &catalog[idis];
    } else {
        return nullptr;
    }
}

// Add an item to the end of the catalog.

short unsigned int CartModel::addItem(const CartItem &item) {
    if (num_items < MAXITEMS) {
        catalog[num_items] = item;
        num_items++;
        return 0;
    }
    return 1;
}

short unsigned int CartModel::repItem(string name, const CartItem& new_item) {
    short int irep = findItem(name);
    //    cout << "index: " << irep << "\n";  //DEBUG
    if (irep > -1) { //item found
        catalog[irep] = new_item;
    } else {
        return 1;
    }
    return 0;
}

short unsigned int CartModel::delItem(string name) {
    short int idel = findItem(name);
    if (idel > -1) { //item found
        for (int i = idel; i < num_items; i++) {
            catalog[i] = catalog[i + 1];
        }
        num_items--;
    } else {
        return 1;
    }
    return 0;
}

void CartModel::clear() {
    num_items = 0;
    return;
}

short unsigned int CartModel::save() {

    fstream file;

    // check file existence
    file.open(catalog_db, ios::in | ios::binary);
    if (file) {
        file.close();
        file.open(catalog_db, ios::out | ios::binary);

        // get size of catalog database
        file.write(reinterpret_cast<char*> (&num_items), sizeof (num_items));

        CartItem temp_item;
        for (int i = 0; i < num_items; i++) {
            //            cout << "Write record " << i << endl;
            strncpy(temp_item.name, catalog[i].name, MAXNAME - 1);
            //            cout << "NAME: " << temp_item.name << endl;
            temp_item.quant = catalog[i].quant;
            //            cout << "QUANT: " << temp_item.quant << endl;
            file.write(reinterpret_cast<char*> (&temp_item), sizeof (CartItem));
        }
    } else {
        return 1;
    }

    file.close();
    return 0;
}

void CartModel::createDB(string catalog_db) {

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

