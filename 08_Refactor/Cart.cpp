/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Cart.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 8:25 AM
 */

#include "Cart.h"
#include "Generics.h"
#include "Constants.h"

Cart::Cart() {
    safeCStrNCpy(this->name, "", MAXFLD);
    this->quant = 0;
}
Cart::Cart(string name, float price, unsigned int quant){
    safeCStrNCpy(this->name, name, MAXFLD);
    this->quant = quant;
}
        
void Cart::setName(string name){
    safeCStrNCpy(this->name, name, MAXFLD);
}
void Cart::setQuant(unsigned int quant){
    this->quant = quant;
}
        
string Cart::getName(){
    return this->name;
}
unsigned int Cart::getQuant(){
    return this->quant;
}

void Cart::display(){
    cout << "Name: " << this->name << "\n";
    cout << "Quantity: " << (this->quant > 0 ? "In stock" : "Out of stock") << "\n";
}


