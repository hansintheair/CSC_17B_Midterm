/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   AdminView.cpp
 * Author: hanne
 * 
 * Created on March 29, 2024, 5:35 PM
 */

#include <iostream>
using namespace std;

#include "AdminView.h"

AdminView::AdminView() {
}

char AdminView::mainMenu(const string& username) {
    cout << "\n--Big4Shopping--\n";
    cout << "--Signed in as" << username << "\n";
    cout << "--ADMIN\n\n";
    cout << "A - Set Password\n";
    cout << "B - List users\n";
    cout << "C - Add user\n";
    cout << "D - Remove user\n";
    cout << "E - View Catalog\n";
    cout << "F - Add item to Catalog\n";
    cout << "G - Remove item from Catalog\n";
    cout << "H - Update item in Catalog\n";
    cout << "Q - Logout\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}