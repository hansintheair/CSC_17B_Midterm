/** \file */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ProfileBase.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 11:41 AM
 */

#include "ProfileBase.h"

ProfileBase::ProfileBase(Account* account) {
    this->account = account;
    this->catalog = new DBModel<Catalog>(CATALOGDBPATH);
    this->status = CLEAN;
}

void ProfileBase::viewProfile() {
    cout << "\n-- Profile Info\n";
    account->display();
//    cout << "CARTDBPATH: " << account->getCartDBPath() << "\n";  //DEBUG
}

void ProfileBase::changePassw() {
    
    string oldpw, newpw;
    
    // Get old password
    cout << "\n-- Change password\n";
    cout << "   Enter old password for " << account->getName() << "\n";
    safeGetLine(oldpw, MAXFLD);
    
    // Authenticate password
    if (!(account->getPassw() == oldpw)) {
        cout << "\n   Invalid password.\n";
        return;
    }
    
    // Get new password
    cout << "   Enter new password for " << account->getName() << "\n";
    safeGetLine(newpw, MAXFLD);
    
    // Update account with new password
    account->setPassw(newpw);
    status = DIRTY;
    
//    cout << "STATUS: " << status << "\n";  //DEBUG
    
    cout << "\n   Password has been updated.\n";
}

void ProfileBase::changeEmail() {
    
    string newemail;
    
    // Get new e-mail
    cout << "\n-- Change e-mail\n";
    cout << "   Old e-mail is " << account->getEmail() << "\n";
    cout << "   Enter new e-mail for " << account->getName() << "\n";
    safeGetLine(newemail, MAXFLD);
    
    // Update account with new password
    account->setEmail(newemail);
    status = DIRTY;
    
    cout << "\n   E-mail has been updated.\n";
}

void ProfileBase::delSelfAccount() {
    
    char conf;
    
    cout << "\n-- Delete account\n";
    cout << "   Are you sure you want to delete your account (Y/)?\n";
    cout << "   WARNING!!! This will permanently delete your account.\n";
    
    cout << "   Add to cart? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {  // Delete user
        // Check if item is already in the cart
        status = DELETE;
    } else {
        cout << "   Cancelled\n";
    }
}

void ProfileBase::viewCatalog() {
    cout << "\n-- Catalog\n";
    catalog->open();
    if (catalog->count() > 0) {
        catalog->display();
    }
    else {
        cout << "\n   Catalog is empty\n";
    }
    
    catalog->close();
}



