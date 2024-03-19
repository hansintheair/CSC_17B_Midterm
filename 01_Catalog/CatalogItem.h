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

#include <iostream>
#include <iomanip>

using namespace std;

const short unsigned int MAXNAME = 81;
const short unsigned int MAXDESC = 256;

struct CatalogItem{
    char name[MAXNAME];  // Name doubles as ID, must be unique.
    char desc[MAXDESC];
    float price;
    unsigned int quant;
    
    void display() {
        cout << "Name: " << name << "\n";
        cout << "Description: " << desc << "\n";
        cout << "Price $" << fixed << setprecision(2) << price << "\n";
        cout << "Quantity: " << quant << "\n";
    }
};

#endif /* CATALOGITEM_H */

