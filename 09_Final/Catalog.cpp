/** \file */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Catalog.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 7:59 AM
 */

#include "Catalog.h"

Catalog::Catalog() {
    safeCStrNCpy(this->name, "", MAXFLD);
    this->price = 0.0;
    this->quant = 0;
}
Catalog::Catalog(string name, float price, unsigned int quant){
    safeCStrNCpy(this->name, name, MAXFLD);
    this->price = price;
    this->quant = quant;
}
        
void Catalog::setName(string name){
    safeCStrNCpy(this->name, name, MAXFLD);
}
void Catalog::setPrice(float price){
    this->price = price;
}
void Catalog::setQuant(unsigned int quant){
    this->quant = quant;
}
        
string Catalog::getName(){
    return this->name;
}
float Catalog::getPrice(){
    return this->price;
}
unsigned int Catalog::getQuant(){
    return this->quant;
}

void Catalog::display() const {
    cout << "   Name: " << this->name << "\n";
    cout << "   Price (per unit): $" << setprecision(2) << fixed << this->price << "\n";
    cout << "   Quantity: " << (this->quant > 0 ? "In stock" : "Out of stock") << "\n";
}

