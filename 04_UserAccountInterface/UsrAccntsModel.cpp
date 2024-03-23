/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UsrAccntsModel.cpp
 * Author: hanne
 * 
 * Created on March 17, 2024, 2:54 PM
 */

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "UsrAccntsModel.h"

UsrAccntsModel::UsrAccntsModel(string accts_db) {
    
    // open file
    fstream file;
    file.open(accts_db, ios::in | ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    // get size of accounts database
    file.read(reinterpret_cast<char*> (&num_accts), sizeof (num_accts));

    Account temp_accnt;
    for (int i = 0; i < num_accts; i++) {
        file.read(reinterpret_cast<char*> (&temp_accnt), sizeof (Account));
        strncpy(accounts[i].name, temp_accnt.name, MAXFLD - 1);
        strncpy(accounts[i].email, temp_accnt.email, MAXFLD - 1);
        strncpy(accounts[i].passw, temp_accnt.passw, MAXFLD - 1);
        strncpy(accounts[i].cartdb, temp_accnt.cartdb, MAXFLD - 1);
        accounts[i].admin = temp_accnt.admin;
    }
//    cout << "DB: " << accts_db << "\n";  //DEBUG
    this->accts_db = accts_db;
//    cout << "DB: " << this->accts_db << "\n";  //DEBUG
}


//UsrAccntsModel::UsrAccntsModel(const UsrAccntsModel& orig) {
//}

//UsrAccntsModel::~UsrAccntsModel() {
//}

short int UsrAccntsModel::findAcct(string name) {
    short unsigned int i = 0;
    short int pos = -1;
//    cout << "Searching for " << name << "\n";  //DEBUG

    while (i < num_accts) {
//        cout << "Searching catalog item #" << i << "\n";  //DEBUG
        if (accounts[i].name == name) {
            pos = i;
            break; //item found
        }
        i++;
    }
    return pos;
}

short unsigned int UsrAccntsModel::getSize() {
    return num_accts;
}

void UsrAccntsModel::display() {
    for (int i = 0; i < num_accts; i++) {
        accounts[i].display();
        cout << "\n";
    }
}

Account* UsrAccntsModel::getAcct(string name, string passw) {
    short int idis = findAcct(name);
//    cout << "index pos: " << idis << "\n"; //DEBUG
    if (idis > -1) {//item found
        if (accounts[idis].passw == passw){
            cout << "Login succeeded\n";
            return &accounts[idis];
        }
        else {
            cout << "Password invalid\n";
            return nullptr;
        }
    }
    else {
        cout << "Account " << name << " does not exist.\n";
        return nullptr;
    }
}

void UsrAccntsModel::addAcct(const Account& account) {
    accounts[num_accts] = account;
    num_accts++;
}

short unsigned int UsrAccntsModel::repAcct(string name, const Account& new_acct){
    short int irep = findAcct(name);
//    cout << "index: " << irep << "\n";  //DEBUG
    if (irep > -1) { //item found
        accounts[irep] = new_acct;
        return 0;  // Success
    } else {
        return 1;  // Account not found
    }
}

void UsrAccntsModel::delAcct(string name){
    short int idel = findAcct(name);
    if (idel > -1) { //item found
        for (int i = idel; i < num_accts; i++) {
            accounts[i] = accounts[i + 1];
        }
        num_accts--;
    } else {
        cout << "Account " << name << " does not exist.\n";
    }
}

short unsigned int UsrAccntsModel::save(){
    fstream file;
    
    cout << "DB: " << accts_db << "\n";

    // check file existence
    file.open(accts_db, ios::in | ios::binary);
    if (file) {
        file.close();
        file.open(accts_db, ios::out | ios::binary);

        // get size of catalog database
        file.write(reinterpret_cast<char*> (&num_accts), sizeof (num_accts));

        Account temp_acct;
        for (int i = 0; i < num_accts; i++) {
            cout << "Write record " << i << "\n";  //DEBUG
            strncpy(temp_acct.name, accounts[i].name, MAXFLD - 1);
            cout << "NAME: " << temp_acct.name << "\n";  //DEBUG
            strncpy(temp_acct.email, accounts[i].email, MAXFLD - 1);
            cout << "EMAIL: " << temp_acct.email << "\n";  //DEBUG
            strncpy(temp_acct.passw, accounts[i].passw, MAXFLD - 1);
            cout << "PASSWORD: " << temp_acct.passw << "\n";  //DEBUG
            strncpy(temp_acct.cartdb, accounts[i].cartdb, MAXFLD -1);
            cout << "CART DATABASE: " << temp_acct.cartdb << "\n";  //DEBUG
            temp_acct.admin = accounts[i].admin;
            cout << "ADMIN: " << string(temp_acct.admin?"Yes":"No") << "\n";  //DEBUG
            file.write(reinterpret_cast<char*> (&temp_acct), sizeof (Account));
        }
    } else {
        return 1;
    }

    file.close();
    return 0;
}

void UsrAccntsModel::createDB(string accts_db) {

    fstream file;

    // check file existence
    file.open(accts_db, ios::in | ios::binary);
    if (!file) {
        file.close();
        file.open(accts_db, ios::out | ios::binary);
        short unsigned int num_accts = 0;
        file.write(reinterpret_cast<char*> (&num_accts), sizeof (num_accts));
    } else {
        cout << "File " << accts_db << " already exists.\n";
    }

    file.close();
}

