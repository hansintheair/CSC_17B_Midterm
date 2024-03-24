/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   CartItem.h
 * Author: hanne
 *
 * Created on March 24, 2024, 4:02 PM
 */

#ifndef CARTITEM_H
#define CARTITEM_H

#include <cstring>
using namespace std;

#include "Constants.h"

struct CartItem{
    char name[MAXNAME];  // Name doubles as ID, must be unique.
    unsigned int quant;
    
    CartItem operator-(const CartItem& other) const {
        CartItem temp_item;
        strncpy(temp_item.name, name, MAXNAME - 1);
        temp_item.quant = quant;
        return temp_item;
    }
    
    CartItem operator+(const CartItem& other) const {
        CartItem temp_item;
        strncpy(temp_item.name, name, MAXNAME - 1);
        temp_item.quant = quant;
        return temp_item;
    }
};

#endif /* CARTITEM_H */

