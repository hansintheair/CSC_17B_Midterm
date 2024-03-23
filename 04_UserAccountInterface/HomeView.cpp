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

char HomeView::menu() {

    cout << "\n--Big4Shopping--\n\n";
    cout << "A - Login\n";
    cout << "B - Create user\n";
    cout << "Q - Exit\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    return choice;
}

void HomeView::userCreate(string &username, string &email, string &passw) {
    cout << "\n--Create user\n";
    cout << "Username: ";
    cin.ignore();
    getline(cin, username);
    cout << "e-mail address: ";
    getline(cin, email);
    cout << "password: ";
    getline(cin, passw);
}

void HomeView::userLogin(string &username, string &passw) {
    cout << "\n--Login\n";
    cout << "Username: ";
    cin.ignore();
    getline(cin, username);
    cout << "password: ";
    getline(cin, passw);
}


