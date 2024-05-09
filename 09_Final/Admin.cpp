/** \file */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Admin.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 10:14 AM
 */

#include "Admin.h"
#include "Constants.h"

Admin::Admin(Account* account, DBModel<Account>* accounts) : ProfileBase(account) {
    this->accounts = accounts;
}

Status Admin::main() {
    bool logout = false;
    char input;
    while (!logout) {
        cout << "\n---Admin Menu\n";
        cout << " - Account: " << account->getName() << "\n";
        cout << "[A] View profile info\n";
        cout << "[B] Change e-mail\n";
        cout << "[C] Change Password\n";
        cout << "[D] List accounts\n";
        cout << "[E] Access user account\n";
        cout << "[F] Create new account\n";
        cout << "[G] Remove an account\n";
        cout << "[H] View Catalog\n";
        cout << "[I] Add item to Catalog\n";
        cout << "[J] Remove item from Catalog\n";
        cout << "[K] Update item in Catalog\n";
        cout << "[L] View store earnings\n";
        cout << "[M] Delete Account (DANGER ZONE)\n";
        cout << "[Q] Logout\n\n";

        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
                viewProfile();
                break;
            case 'b':
                changeEmail();
                break;
            case 'c':
                changePassw();
                break;
            case 'd':
                viewAccounts();
                break;
            case 'e':
                viewEditUser();
                break;
            case 'f':
                createAccount();
                break;
            case 'g':
                delAccount();
                break;
            case 'h':
                viewCatalog();
                break;
            case 'i':
                addCatalogItem();
                break;
            case 'j':
                delCatalogItem();
                break;
            case 'k':
                updCatalogItem();
                break;
            case 'l':
                viewEarningsHist();
                break;
            case 'm':
                delSelfAccount();
                if (status == DELETE) {
                    logout = true;
                }
                break;
            case 'q':
                cout << "\n";
                logout = true;
                break;
            default:
                cout << "   Unknown input, please try again\n";
        };
    }
    cout << "   Logging out\n";
    return status;
}

void Admin::viewProfile() {
    ProfileBase::viewProfile();
    cout << "   Administrator\n";
}

void Admin::viewCatalog() {
    
    Catalog* item = nullptr;
    
    cout << "\n-- Catalog\n\n";
    
    catalog->open();
    if (catalog->count() > 0) {
        for (int i = 0; i < catalog->count(); i++) {
            item = catalog->get(i);
            cout << "   -" << i << "-\n";
            cout << "   Name: " << item->getName() << "\n";
            cout << "   Price (per unit): $" << setprecision(2) << fixed << item->getPrice() << "\n";
            cout << "   Quantity: " << item->getQuant() << "\n\n";
        }
        cout << "   " << catalog->count() << " items in catalog\n";
    }
    else {
        cout << "\n   Catalog is empty\n";
    }
    
    catalog->close();
}

void Admin::viewAccounts() {
    
    Account* profile = nullptr;
    
    cout << "\n-- Accounts\n\n";
    
    accounts->open();
    for (int i = 0; i < accounts->count(); i++) {
        profile = accounts->get(i);
        cout << "   Name: " << profile->getName() << "\n";
        cout << "   E-mail: " << profile->getEmail() << "\n";
        cout << "   Cart Database: " << profile->getCartDBPath() << "\n";
        cout << "   Is admin: " << (profile->isAdmin()?"Yes":"No") << "\n";
        
        if (!profile->isAdmin()) {
            User user = User(profile);
            float total_spent = 0;
            user.getHistTotal(total_spent);
            cout << "   Total spent: $" << setprecision(2) << fixed << total_spent << "\n";
        }
        
        // Main admin account "admin" has special privileges; can see passwords
        if (account->getName() == "admin") {
            cout << "   Password: " << (profile->getPassw()) << "\n";
        }
        cout << "\n";
    }
    cout << "   " << accounts->count() << " accounts in store\n";
        
    accounts->close();
    delete profile;
    profile = nullptr;    
}

void Admin::createAccount() {
    
    char conf;
    string name, email, passw, cart, hist;
    bool is_admin;

    accounts->open();

    // Get new user data
    cout << "\n-- Create user\n";
    cout << "   Enter username\n";
    safeGetLine(name, MAXFLD);
    if (accounts->find(name) >= 0) {
        cout << "   That account already exists\n";
        accounts->close();
        return;
    } 
    cout << "   Enter e-mail address\n";
    safeGetLine(email, MAXFLD);
    cout << "   Enter password\n";
    safeGetLine(passw, MAXFLD);
    
    cout << "   Is this an admin account (Y/N)?\n";
    while (true) {
        conf = getSingleChar();
        tolower(conf);
        if (conf == 'y') {
            is_admin = true;
            cart = "";
            break;
        } else if (conf == 'n') {
            is_admin = false;
            // Create cart database for new user
            cart = "data/" + name + ".bin";
            DBModel<Catalog>::create(cart);
            hist = "data/" + name + "_hist.bin";
            DBModel<Catalog>::create(hist);
            break;

        } else {
            cout << "   Invalid response, must be 'Y' or 'N'\n";
        }
    }
    
    // Add new user record to accounts database
    Account record = Account(name, email, passw, cart, hist, is_admin);
    accounts->add(&record);
    accounts->close();
}

void Admin::delAccount() {
    
    string name;
    int prof_pos;
    Account* profile;
    
    cout << "\n-- Delete an account\n";
    cout << "   Enter username of account to delete\n";
    safeGetLine(name, MAXFLD);
    
    // Cannot delete own account using this method
    if (name == account->getName()) {
        cout << "   Cannot delete your own account using this method\n";
        return;
    } else if (name == "admin") { // admin is special; primary admin
        cout << "   Cannot remove the primary admin, \"admin\"\n";
        return;
    }
    
    accounts->open();
    
    // Check if the account exists
    prof_pos = accounts->find(name);
    if (prof_pos < 0) {
        cout << "   That account does not exist\n";
        accounts->close();
        return;
    }

    // Delete the account
    profile = accounts->get(prof_pos);
    DBModel<Account>::deleteDB(profile->getCartDBPath());
    accounts->del(prof_pos);
    accounts->close();
    
    cout << "   Successfully deleted account\n";
    
    delete profile;
    profile = nullptr;
}

void Admin::delSelfAccount() {
    
    if (account->getName() == "admin") {
        cout << "   Cannot remove the primary admin, \"admin\"\n";
        return;
    }
    
    ProfileBase::delSelfAccount();
}

void Admin::addCatalogItem() {
    
    string name;
    int quant;
    float price;
    
    Catalog item;
    
    cout << "-- Add item to catalog\n";
    
    catalog->open();
    
    // Get new user data
    cout << "   Enter name of item\n";
    safeGetLine(name, MAXFLD);
    if (catalog->find(name) >= 0) {
        cout << "   That item already exists\n";
        catalog->close();
        return;
    } 
    cout << "   Enter quantity of item\n";
    getNumeric<int>(quant);
    cout << "   Enter price of each unit\n";
    getNumeric<float>(price);

    item.setName(name);
    item.setQuant(quant);
    item.setPrice(price);
    
    catalog->add(&item);
    catalog->close();    
    cout << "   Item added to catalog\n";
}

void Admin::updCatalogItem() {
    
    string name;
    int quant, pos;
    float price;
    
    Catalog* item = nullptr;
    
    cout << "-- Update item in catalog\n";
    
    // Retrieve item
    cout << "   Enter name of item to update\n";
    safeGetLine(name, MAXFLD);
    
    catalog->open();
    
    // If user input is an integer, treat as index position
    if (isInt(name)) {
        pos = stoi(name);
        if (!catalog->hasIndex(pos)) {
            cout << "   Item # " << pos << " not found\n";
            catalog->close();
            return;
        }
//        cout << "POS: " << pos << "\n";  //DEBUG
    }
    // Otherwise treat as full item name
    else { 
        pos = catalog->find(name);
        if (pos < 0) {
            cout << "   Item \"" << name << "\" not found\n";
            catalog->close();
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }
    
    item = catalog->get(pos);
    cout << "   Name: " << item->getName() << "\n";
    cout << "   Price (per unit): $" << setprecision(2) << fixed << item->getPrice() << "\n";
    cout << "   Quantity: " << item->getQuant() << "\n\n";
    
    // Get update item data
    cout << "   Enter new name of item\n";
    safeGetLine(name, MAXFLD);
    cout << "   Enter new quantity of item\n";
    getNumeric<int>(quant);
    cout << "   Enter new price of each unit\n";
    getNumeric<float>(price);

    item->setName(name);
    item->setQuant(quant);
    item->setPrice(price);
    
    catalog->set(pos, item);
    catalog->close();
    
    cout << "   Item updated in catalog\n";
    
    delete item;
    item = nullptr;
}

void Admin::delCatalogItem() {
    
    string name;
    int quant, pos;
    float price;
    char conf;
    
    Catalog* item = nullptr;
    
    cout << "-- Remove item from catalog\n";
    
    // Retrieve item
    cout << "   Enter name of item to update\n";
    safeGetLine(name, MAXFLD);
    
    catalog->open();
    
    // If user input is an integer, treat as index position
    if (isInt(name)) {
        pos = stoi(name);
        if (!catalog->hasIndex(pos)) {
            cout << "   Item # " << pos << " not found\n";
            catalog->close();
            return;
        }
//        cout << "POS: " << pos << "\n";  //DEBUG
    }
    // Otherwise treat as full item name
    else { 
        pos = catalog->find(name);
        if (pos < 0) {
            cout << "   Item \"" << name << "\" not found\n";
            catalog->close();
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }
    
    // Display the item
    item = catalog->get(pos);
    cout << "   Name: " << item->getName() << "\n";
    cout << "   Price (per unit): $" << setprecision(2) << fixed << item->getPrice() << "\n";
    cout << "   Quantity: " << item->getQuant() << "\n\n";
    
    // Delete item
    cout << "   Delete item (Y/)?\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        catalog->del(pos);
    } else {
        cout << "   Cancelled\n";
    }
    
    catalog->close();
    
    delete item;
    item = nullptr;
}

void Admin::viewEarningsHist() {
    
    float total = 0.0;
    int num_accnts;
    Account* profiles = nullptr;
    
    cout << "\n-- Store Earnings\n\n";

    accounts->open();
    profiles = accounts->getAll();
    num_accnts = accounts->count();
    accounts->close();
    
    for (int i = 0; i < num_accnts; i++) {
        if (!profiles[i].isAdmin()) {
            User user = User(&profiles[i]);
            user.getHistTotal(total);
        }
    }

    cout << "   Total store earnings: $" << setprecision(2) << fixed << total << "\n";
    
    delete[] profiles;
    profiles = nullptr;    
}

void Admin::viewEditUser(){
    bool logout = false;
    string name;
    char input;
    int prof_pos = -1;
    Account* profile;
    
    // Get user
    cout << "\n-- Access user account (as admin)\n";
    cout << "   Enter name of user account\n";
    safeGetLine(name, MAXFLD);
    
    
    // Check if the account exists
    accounts->open();
    prof_pos = accounts->find(name);
    if (prof_pos < 0) {
        cout << "   That account does not exist\n";
        accounts->close();
        return;
    }
    profile = accounts->get(prof_pos);    
    accounts->close();
    
    // Cannot access other admin accounts
    if (profile->isAdmin()) {
        cout << "   Impossible, the selected account is an admin\n";
        return;
    }
    
    // Display account access options
    User user = User(profile);
    while (!logout) {
        user.viewProfile();
        cout << "[A] View cart\n";
        cout << "[B] Remove from cart\n";
        cout << "[C] View order history\n";
        cout << "[D] Change e-mail\n";
        cout << "[E] Reset password\n";
        cout << "[Q] Back\n\n";

        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
                user.viewCart();
                break;
            case 'b':
                user.remFrmCart();
                break;
            case 'c':
                user.viewHist();
                break;
            case 'd':
                user.changeEmail();
                break;
            case 'e':
            {
                cout << "-- Reset password\n";
                cout << "   This will reset the user's password. Are you sure (Y/)?\n";
                char conf = getSingleChar();
                tolower(conf);
                if (conf != 'y') {
                    cout << "   Cancelled\n";
                    break;
                }
                
                string new_pwd;
                randomString(new_pwd, 12);
                profile->setPassw(new_pwd);
                cout << "   Password has been reset to " << new_pwd << "\n";
                cout << "   ATTENTION! Be sure to provide this password to the user\n";
                break;
            }
            case 'q':
                cout << "\n";
                logout = true;
                break;
            default:
                cout << "   Unknown input, please try again\n";
        };
    }
    
    // Update account record if changes were made to profile
    if (user.getStatus() == DIRTY) {
        accounts->open();
        prof_pos = accounts->find(profile->getName());
        accounts->set(prof_pos, profile);
        accounts->close();
    }
    
    // Cleanup
    delete profile;
    profile = nullptr;
    
    cout << "   Exiting user\n";
}

