/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   HomeView.cpp
 * Author: hanne
 * 
 * Created on March 18, 2024, 6:21 PM
 */

#include <iostream>
using namespace std;

#include "HomeView.h"

char HomeView::renderHome() {

    cout << "\n--BIG4SHOPPING--\n\n";
    cout << "A - Login\n";
    cout << "B - Create user\n";
    cout << "Q - Exit\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    return choice;
}

void HomeView::userLogin(string &username, string &passw) {
    cout << "--Login\n";
    cout << "Username: ";
    cin.ignore();
    getline(cin, username);
    cout << "password: ";
    getline(cin, passw);
}


