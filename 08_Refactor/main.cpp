/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: hanne
 *
 * Created on April 5, 2024, 5:21 PM
 */

#include <cstdlib>
#include <string>

using namespace std;

#include "Generics.h"
#include "DBModel.h"
#include "Account.h"

/*
 * 
 */
int main() {
    
    string dbpath = "testdb.bin";
    DBModel<Account>::create(dbpath);
    DBModel<Account> db = DBModel<Account>(dbpath);
    db.open();
    db.delAll();

    Account user1 = Account("Hannes", "hannesz1@gmail.com", "hannes", "", 0);
    Account user2 = Account("Merari", "merari@gmail.com", "merari", "", 0);
    
    db.add(&user1);
    db.add(&user2);
    db.display();
    db.close();
    
    return 0;
}

