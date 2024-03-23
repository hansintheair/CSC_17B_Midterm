/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   UsrAccntsModel.h
 * Author: hannes
 *
 * Created on March 17, 2024, 2:54 PM
 */

#ifndef USRACCNTSMODEL_H
#define USRACCNTSMODEL_H

#include "Account.h"

const short unsigned int MAXACCTS = 1000;

class UsrAccntsModel {
private:
    string accts_db;
    Account accounts[MAXACCTS];
    unsigned short int num_accts;
    short int findAcct(string);
public:
    UsrAccntsModel(string);
//    UsrAccntsModel(const UsrAccntsModel& orig);
//    virtual ~UsrAccntsModel();
    void display();
    Account* getAcct(string, string);
    short unsigned int getSize();
    void addAcct(const Account&);
    short unsigned int repAcct(string, const Account&);
    void delAcct(string);

    short unsigned int save();
    static void createDB(string);
};

#endif /* USRACCNTSMODEL_H */

