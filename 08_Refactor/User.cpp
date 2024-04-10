/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   User.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 10:47 AM
 */

#include "User.h"

User::User(Account* account) : ProfileBase(account) {
    this->cart = new DBModel<Cart>(account->getCartDBPath());
}

User::~User(){
    // Clean up managed memory
    delete this->cart;
    this->cart = nullptr;
    delete this->catalog;
    this->catalog = nullptr;
}

Status User::main() {
    bool logout = false;
    char input;
    while (!logout) {
        cout << "\n---User Menu\n";
        cout << " - Signed in: " << account->getName() << "\n";
        cout << "[A] View profile Info\n";
        cout << "[B] Change e-mail\n";
        cout << "[C] Change password\n";
        cout << "[D] View Catalog\n";
        cout << "[E] Shop Catalog\n";
        cout << "[F] View Cart\n";
        cout << "[G] Remove from Cart\n";
        cout << "[H] Place order\n";
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
                viewCatalog();
                break;
            case 'e':
                shopCatalog();
                break;
            case 'f':
                viewCart();
                break;
            case 'g':
                remFrmCart();
                break;
            case 'h':
                break;
            case 'q': //Logout
                cout << "\n";
                logout = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "Logging out\n";
//    cout << "STATUS: " << status << "\n";  //DEBUG
    return status;
}

void User::viewCart() {
    cout << "\n-- Cart\n";
    cart->open();
    if (cart->count() > 0) {
        cart->display();
    }
    else {
        cout << "\n   Cart is empty\n";
    }
    cart->close();
}

void User::shopCatalog() {
    
    string input;
    char conf;
    int pos;
    unsigned int quant;
    float total;
    Catalog* cat_item = nullptr;
    Cart car_item;
    
    cout << "\n-- Shop Catalog\n";
    cout << "   Enter item name or item number\n";
    cout << ">> ";
    getline(cin, input);
    
    catalog->open();
    // If user input is an integer, treat as index position
    if (isInt(input)) {
        pos = stoi(input);
        if (!catalog->hasIndex(pos)) {
            cout << "   Item # " << pos << " not found\n";
            
            delete cat_item;
            cat_item = nullptr;
            return;
        }
//        cout << "POS: " << pos << "\n";  //DEBUG
        cat_item = catalog->get(pos);
    }
    // Otherwise treat as full item name
    else { 
        pos = catalog->find(input);
        if (pos < 0) {
            cout << "   Item \"" << input << "\" not found\n";
            
            delete cat_item;
            cat_item = nullptr;
            return;
        }
//        cout << "POS: " << pos << "\n";  //DEBUG
        cat_item = catalog->get(pos);
    }
    
    catalog->close();
    
    // Display the item details
    
    cout << "\n";
    cat_item->display();
    cout << "             " << cat_item->getQuant() << "\n\n";
    
    // Get number of items to purchase from user
    cout << "   Enter the number of items to purchase (0 to cancel)\n";
    getNumeric<unsigned int>(quant);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (quant == 0) {  // Cancel
        cout << "\n   Cancelled\n";
        
        delete cat_item;
        cat_item = nullptr;
        return;
    } else if (quant > cat_item->getQuant()) {
        cout << "   There are not enough of that item in stock\n";
        
        delete cat_item;
        cat_item = nullptr;
        return;
    }
    
    // Populate cart item from catalog item
    car_item.setName(cat_item->getName());
    car_item.setQuant(quant);
    
    total = static_cast<float>(car_item.getQuant()) * cat_item->getPrice();
    cout << "\n   Unit Price: $" << setprecision(2) << fixed << cat_item->getPrice() << "\n";
    cout << "   Total: $" << setprecision(2) << fixed << total << "\n\n";
    
    // Confirm before adding to cart
    cout << "   Add to cart? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        // Add item to cart
        cart->open();
        
        // Check if item is already in the cart
        int i_ = cart->find(car_item.getName());
//        cout << "FOUND: " << i_ << "\n";  //DEBUG
        if (i_ >= 0) {  // If item already exists, update it with new quantity
            Cart* tmp_car_item = cart->get(i_);
            tmp_car_item->setQuant(tmp_car_item->getQuant() + car_item.getQuant());
            cart->set(i_, tmp_car_item);
            delete tmp_car_item;
            tmp_car_item = nullptr;
        } else {  // Otherwise, add item
            cart->add(&car_item);        
        }
        cart->close();
        // Deduct from catalog
        cat_item->setQuant(cat_item->getQuant() - car_item.getQuant());
        catalog->open();
        catalog->close();
        cout << "   Cart updated\n";
    } else {
        cout << "   Cancelled";
    }    

    delete cat_item;
    cat_item = nullptr;
}

void User::remFrmCart() {
    
    string input;
    char conf;
    int car_pos, cat_pos;
    float total;
    Cart* car_item = nullptr;
    Catalog* cat_item = nullptr;
    
    cout << "\n-- Remove item from cart\n";
    cout << "   Enter item name or item number\n";
    cout << ">> ";
    getline(cin, input);
    
    cart->open();
    // If user input is an integer, treat as index car_position
    if (isInt(input)) {
        car_pos = stoi(input);
        if (!cart->hasIndex(car_pos)) {
            cout << "   Item # " << car_pos << " not found\n";
            
            delete car_item;
            car_item = nullptr;
            delete cat_item;
            cat_item = nullptr;
            return;
        }
//        cout << "POS: " << car_pos << "\n";  //DEBUG
        car_item = cart->get(car_pos);
    }
    // Otherwise treat as full item name
    else { 
        car_pos = cart->find(input);
        if (car_pos < 0) {
            cout << "   Item \"" << input << "\" not found\n";
            
            delete car_item;
            car_item = nullptr;
            delete cat_item;
            cat_item = nullptr;
            return;
        }
//        cout << "POS: " << car_pos << "\n";  //DEBUG
        car_item = cart->get(car_pos);
    }
    
    cart->close();
    
    // Get item from Catalog and check that item is still in stock
    catalog->open();
    cat_pos = catalog->find(car_item->getName());
    if (cat_pos < 0) {
        cout << "   This item is no longer available and\n   will be removed from the cart\n";
        cart->open();
        cart->del(car_pos);
        cart->close();
        
        delete car_item;
        car_item = nullptr;
        delete cat_item;
        cat_item = nullptr;
        return;
    }

    // Check price of item in catalog
    cat_item = catalog->get(cat_pos);
    total = static_cast<float>(car_item->getQuant()) * cat_item->getPrice();
    
    catalog->close();
    
    // Display the item
    cout << "\n";
    car_item->display();
    cout << "   Unit Price: $" << setprecision(2) << fixed << cat_item->getPrice() << "\n";
    cout << "   Total: $" << setprecision(2) << fixed << total << "\n\n";
    
    // Confirm before removing item from cart
    cout << "   Remove from cart? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        // Remove item from cart
        cart->open();
        cart->del(car_pos);
        cart->close();
        cout << "   Item removed from your cart\n";
    } else {
        cout << "   Cancelled";
    }    

    delete car_item;
    car_item = nullptr;
    delete cat_item;
    cat_item = nullptr;
}