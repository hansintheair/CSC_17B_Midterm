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

#include "Home.h"

/*
 * 
 */
int main() {
    
    string dbpath = "testdb.bin";
    DBModel<Account>::create(dbpath);
    DBModel<Account> accounts = DBModel<Account>(dbpath);
   accounts.open();
   accounts.delAll();

   Account admin = Account("admin", "admin@company.com", "admin", "", 1);
   Account user1 = Account("hannes", "hannesz1@gmail.com", "hannes", "", 0);
   Account user2 = Account("merari", "merari@gmail.com", "merari", "", 0);
   
   accounts.add(&admin);
   accounts.add(&user1);
   accounts.add(&user2);
   accounts.display();
   accounts.close();
    
    Home home = Home(&accounts);
    home.main();
    
    return 0;
}

