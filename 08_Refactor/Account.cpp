/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Account.cpp
 * Author: hanne
 * 
 * Created on April 5, 2024, 6:13 PM
 */

#include "Account.h"

using namespace std;

Account::Account() {
    strncpy(this->name, "", MAXFLD-1);
    strncpy(this->email, "", MAXFLD-1);
    strncpy(this->passw, "", MAXFLD-1);
    strncpy(this->cartdb, "", MAXFLD-1);
    this->is_admin = 0;
}
Account::Account(string name, string email, string passw, string cartdb, bool is_admin) {
    strncpy(this->name, name.c_str(), MAXFLD-1);
    strncpy(this->email, email.c_str(), MAXFLD-1);
    strncpy(this->passw, passw.c_str(), MAXFLD-1);
    strncpy(this->cartdb, cartdb.c_str(), MAXFLD-1);
    this->is_admin = is_admin;
}

void Account::setName(string name){
    strncpy(this->name, name.c_str(), MAXFLD-1);
}
void Account::setEmail(string email){
    strncpy(this->email, email.c_str(), MAXFLD-1);
}
void Account::setPassw(string passw){
    strncpy(this->passw, passw.c_str(), MAXFLD-1);
}

string Account::getName(){
    return this->name;
}
string Account::getEmail(){
    return this->email;
}
string Account::getPassw(){
    return this->passw;
}
bool Account::isAdmin(){
    return this->is_admin;
}

void Account::display() {
    cout << "Name: " << this->name << "\n";
    cout << "E-mail: " << this->email << "\n";
}



