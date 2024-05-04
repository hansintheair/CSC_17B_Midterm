/** \file */

/**
 * \anchor Catalog
 * \class Catalog
 * This class stores catalog item data and provides accessors for reading and manipulating item attributes.
 * 
 * It used to represent data in the store Catalog managed by the Admin class, as well as the cart and shopping history of the User class.
 * 
 * DBModel is used to store records of Catalog items in a binary database file.
 */

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
const string CATALOGDBPATH = "data/store_catalog.bin";

class Catalog {
    
    private:
        char name[MAXFLD];
        float price;
        unsigned int quant;
    
    public:
        Catalog();
        Catalog(string, float, unsigned int);
        
        // Setters

        /// @brief Setter for item name
        /// @param name item name
        void setName(string name);

        /// @brief Setter for item price
        /// @param price item price
        void setPrice(float price);

        /// @brief Setter for item quantity
        /// @param quant item quantity
        void setQuant(unsigned int quant);
        
        // Getters

        /// @brief Getter for item name
        /// @return item name
        string getName();

        /// @brief Getter for item price
        /// @return item price
        float getPrice();

        /// @brief Getter for item quantity
        /// @return item quantity
        unsigned int getQuant();
        
        // Other Methods

        /// @brief Display item details
        void display() const;

};

#endif /* CATALOG_H */

