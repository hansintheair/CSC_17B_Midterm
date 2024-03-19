/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   Account.h
 * Author: hanne
 *
 * Created on March 17, 2024, 2:54 PM
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

const short unsigned int MAXFLD = 81;

struct Account {
    char name[MAXFLD];
    char email[MAXFLD];
    char passw[MAXFLD];
    char cartdb[MAXFLD];
    bool admin;
    
    void display() {
        cout << "Name: " << name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Password " << passw << "\n";
        cout << "Cart Database: " << cartdb << "\n";
        cout << "Admin: " << string(admin?"Yes":"No") << "\n";
    }
};

#endif /* ACCOUNT_H */

