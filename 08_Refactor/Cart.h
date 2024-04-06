/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Cart.h
 * Author: hanne
 *
 * Created on April 6, 2024, 8:25 AM
 */

#ifndef CART_H
#define CART_H

#include <string>
#include <iostream>

using namespace std;

class Cart {
    
    private:
        char* name;
        unsigned int quant;

    
    public:
        Cart();
        Cart(string, float, unsigned int);
        
        // Setters
        void setName(string);
        void setQuant(unsigned int);
        
        // Getters
        string getName();
        unsigned int getQuant();
        
        // Other
        void display();

};

#endif /* CART_H */

