/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Catalog.h
 * Author: hanne
 *
 * Created on April 6, 2024, 7:59 AM
 */

#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Generics.h"
#include "Constants.h"

// Constants
const string CATALOGDBPATH = "data/catalog.bin";

class Catalog {
    
    private:
        char* name;
        float price;
        unsigned int quant;

    
    public:
        Catalog();
        Catalog(string, float, unsigned int);
        
        // Setters
        void setName(string);
        void setPrice(float);
        void setQuant(unsigned int);
        
        // Getters
        string getName();
        float getPrice();
        unsigned int getQuant();
        
        // Other Methods
        void display();

};

#endif /* CATALOG_H */

