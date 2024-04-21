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
#include "Catalog.h"
#include "Cart.h"

/*
 * 
 */

void createRndmCtlg(string, unsigned int);


int main() {
    
    srand(static_cast<unsigned>(time(0)));  //Seed random number
        
    createRndmCtlg(CATALOGDBPATH, 10);
    DBModel<Catalog> catalog = DBModel<Catalog>(CATALOGDBPATH);
//    catalog.open();  //DEBUG
//    catalog.display();  //DEBUG
//    catalog.close();  //DEBUG
    

    DBModel<Account>::create(ACCOUNTSDBPATH);
    DBModel<Account> accounts = DBModel<Account>(ACCOUNTSDBPATH);
    accounts.open();
    accounts.delAll();

    Account admin = Account("admin", "admin@company.com", "admin", "", "", 1);
    Account user1 = Account("hannes", "hannesz1@gmail.com", "hannes", "data/hannes.bin", "data/hannes_hist.bin", 0);
    DBModel<Catalog>::create(user1.getCartDBPath());
    DBModel<Catalog>::create(user1.getHistDBPath());
    Account user2 = Account("merari", "merari@gmail.com", "merari", "data/merari.bin", "data/merari_hist.bin", 0);
    DBModel<Catalog>::create(user2.getCartDBPath());
    DBModel<Catalog>::create(user2.getHistDBPath());
    
    accounts.add(&admin);
    accounts.add(&user1);
    accounts.add(&user2);
    accounts.display();
    accounts.close();

    Home home = Home(&accounts);
    home.main();
    
    return 0;
}


void createRndmCtlg(string path, unsigned int count) {
    
    // Create the database
    DBModel<Catalog>::create(path);
    DBModel<Catalog> catalog = DBModel<Catalog>(path);
    
    Catalog* records = new Catalog[count];

    for (unsigned int i = 0; i < count; i++) {
        records[i].setName("Item #"+to_string(i));
        records[i].setPrice(randomFloat(0.49, 200));
        records[i].setQuant(randomUnsInt(1, 100000));
    }

    catalog.open();
    catalog.setAll(records, count);
//    cout << "COUNT: " << catalog.count() << "\n";  //DEBUG
    catalog.close();
        
    delete [] records;
    records = nullptr;
}