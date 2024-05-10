/** \file */

/**
 * @mainpage Documentation Homepage
 *
 * This is the main page of the documentation for my C++ Shopping Store Application.
 *
 * \ref Home is the main entry point into the application.   
 * \ref main performs some setup (creating nescessary objects) and then calls Home::main() to execute the program.
 * 
 * \ref Generics provides a handful of generic helper functions useful throughout the project.
  */

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

/*
 * 
 */

void createRndmCtlg(string, unsigned int);
void createRndmUser(int num, bool isadmin = false);

/// @brief Performs nescessary setup to run the Shopping Store Application. 
/// Calls Home.main to launch the application.
int main() {
    
    srand(static_cast<unsigned>(time(0)));  //Seed random number

    // UNCOMMENT IF YOU WANT TO GENERATE SOME RANDOM DATA OR ACCOUNTS
//    createRndmCtlg(CATALOGDBPATH, 1000);  //Overwrites all catalog entries with N new entries
//    createRndmUser(1, true);  // Adds (appends) some new admin accounts to the accounts database
//    createRndmUser(20, false);  // Adds (appends) some new user accounts to the accounts database
    
    DBModel<Catalog> catalog = DBModel<Catalog>(CATALOGDBPATH);
    DBModel<Account>::create(ACCOUNTSDBPATH);
    DBModel<Account> accounts = DBModel<Account>(ACCOUNTSDBPATH);
    

    Home home = Home(&accounts);
    home.main();
    
    return 0;
}


/// @brief Helper to create random catalog items.
/// @param path The path to the catalog database.
/// @param count The number of random items to generate. WARNING: existing catalog will be overwritten.
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

/// @brief Helpert to create random user or admin accounts. Generates random shopping data if user accounts.
/// @param num Number of accounts to generate.
/// @param isadmin Creates admin accounts if true, else creates user accounts.
void createRndmUser(int num, bool isadmin) {
    
    DBModel<Account> accounts = DBModel<Account>(ACCOUNTSDBPATH);
    DBModel<Catalog> catalog = DBModel<Catalog>(CATALOGDBPATH);
    string prefix, name, email, cartpath = "", histpath = "";
    int idx = 0, cnt = 0, pos = 0, cat_cnt = 0;
    unsigned int items = 0;
    
    // set the correct prefix based on admin or user
    if (isadmin) {
        prefix = "admin";
    } else {
        prefix = "user";
    }
        
    accounts.open();
    catalog.open();
    
    cat_cnt = catalog.count();
    
    while (cnt < num) {
        
        // Generate new name and make sure it is unique, else skip it
        name = prefix + "_" + to_string(idx);
        pos = accounts.find(name);
        if (pos > -1) {
            idx += 1;  // We can't use this number, try next one
            continue;
        }
        
        cnt += 1;  // This one is unique, count up
        
        // Create a new user account
        email = name + "@email.com";
        if (!isadmin) {
            cartpath = "data/" + name + ".bin";
            DBModel<Catalog>::create(cartpath);
            histpath = "data/" + name + "_hist.bin";
            DBModel<Catalog>::create(histpath);
        }        
        
        Account account = Account(name, email, name, cartpath, histpath, isadmin);
        accounts.add(&account);
        
//        account.display();  // DEBUG
        if (!isadmin) {
            // Fill cart with items randomly chosen from store catalog
            DBModel<Catalog> cart = DBModel<Catalog>(cartpath);
            cart.open();
            items = randomUnsInt(0, 6);
            for (unsigned int i = 0; i < items; i++) {
                Catalog* item = catalog.get(randomUnsInt(0, cat_cnt));
                item->setQuant(randomUnsInt(1, 3));
//                item->display();  //DEBUG
//                cout << "   QUANT: " << item->getQuant() << "\n";  //DEBUG
                cart.add(item);
            }
            cart.close();

            // Fill history with items randomly chosen from store catalog
            DBModel<Catalog> hist = DBModel<Catalog>(histpath);
            hist.open();
            items = randomUnsInt(0, 6);
            for (unsigned int i = 0; i < items; i++) {
                Catalog* item = catalog.get(randomUnsInt(0, cat_cnt));
                item->setQuant(randomUnsInt(1, 3));
//                item->display();  //DEBUG
//                cout << "   QUANT: " << item->getQuant() << "\n";  //DEBUG
                hist.add(item);
            }
            hist.close();
        }
        
    }
    accounts.close();
    catalog.close();
}