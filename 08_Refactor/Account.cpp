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
#include "Generics.h"

using namespace std;

Account::Account() {
    safeCStrNCpy(this->name, "", MAXFLD);
    safeCStrNCpy(this->email, "", MAXFLD);
    safeCStrNCpy(this->passw, "", MAXFLD);
    safeCStrNCpy(this->cartdb, "", MAXFLD);
    this->is_admin = 0;
}
Account::Account(string name, string email, string passw, string cartdb, bool is_admin) {
    safeCStrNCpy(this->name, name, MAXFLD);
    safeCStrNCpy(this->email, email, MAXFLD);
    safeCStrNCpy(this->passw, passw, MAXFLD);
    safeCStrNCpy(this->cartdb, cartdb, MAXFLD);
    this->is_admin = is_admin;
}

void Account::setName(string name){
    safeCStrNCpy(this->name, name, MAXFLD);
}
void Account::setEmail(string email){
    safeCStrNCpy(this->email, email, MAXFLD);
}
void Account::setPassw(string passw){
    safeCStrNCpy(this->passw, passw, MAXFLD);
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



