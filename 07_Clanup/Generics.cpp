/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Generics.cpp
 * Author: hanne
 * 
 * Created on March 31, 2024, 2:10 PM
 */

#include "Generics.h"


void getNumeric(int& num) {
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore();
        cin >> num;
    }
}
void getNumeric(unsigned int& num) {
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore();
        cin >> num;
    }
}
void getNumeric(float& num) {
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore();
        cin >> num;
    }
}