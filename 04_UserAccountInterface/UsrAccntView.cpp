/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UsrAccntView.cpp
 * Author: hanne
 * 
 * Created on March 21, 2024, 5:56 PM
 */

#include <iostream>
using namespace std;

#include "UsrAccntView.h"

char UsrAccntView::menu(const string& username) {
    cout << "\n--Big4Shopping--\n";
    cout << "--Signed in as " << username << "\n\n";
    cout << "A - User Profile\n";
    cout << "B - Shopping cart\n";
    cout << "C - Shop the catalog\n";
    cout << "Q - Logout\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}



