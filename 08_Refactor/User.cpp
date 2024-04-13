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
                placeOrder();
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
    cout << "\n-- Cart\n\n";
    
    float total = 0.0;
    float item_total = 0.0;
    int car_count, pos;
    Cart* car_items = nullptr;
    Catalog* cat_item = nullptr;
    
    // Get items from cart and store in memory
    cart->open();
    car_items = cart->getAll();
    car_count = cart->count();
    cart->close();
    
    if (car_count > 0) {
        // Check price of each item in cart (ignore if discontinued)
        catalog->open();
        for (int i = 0; i < car_count; i++) {
            pos = catalog->find(car_items[i].getName());
            if (pos >= 0) {
                cat_item = catalog->get(pos);
                item_total = cat_item->getPrice() * car_items[i].getQuant();
                total += item_total;

                cout << "   Name: " << car_items[i].getName() << "\n";
                cout << "   Quantity: " << car_items[i].getQuant() << "\n";
                cout << "   Price per unit: $" << setprecision(2) << fixed << cat_item->getPrice() << "\n";
                cout << "   Item total: $" << setprecision(2) << fixed << item_total << "\n\n";
            }
        }
        catalog->close();

        cout << "   Grand Total: $" << setprecision(2) << fixed << total << "\n";
    } else {
        cout << "   Cart is empty\n";
    }
        
    delete [] car_items;
    car_items = nullptr;
    delete cat_item;
    cat_item = nullptr;
}

void User::shopCatalog() {
    
    string input;
    char conf;
    int cat_pos, car_pos;
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
        cat_pos = stoi(input);
        if (!catalog->hasIndex(cat_pos)) {
            cout << "   Item # " << cat_pos << " not found\n";
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }
    // Otherwise treat as full item name
    else { 
        cat_pos = catalog->find(input);
        if (cat_pos < 0) {
            cout << "   Item \"" << input << "\" not found\n";
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }

    cat_item = catalog->get(cat_pos);

    
    catalog->close();
    
    // Display the item details
    
    cout << "\n";
    cat_item->display();
    cout << "             " << cat_item->getQuant() << "\n\n";
    
    // Get number of items to purchase from user
    cout << "   Enter the number of items to purchase (0 to cancel)\n";
    getNumeric<unsigned int>(quant);

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
        int car_pos = cart->find(car_item.getName());
//        cout << "FOUND: " << car_pos << "\n";  //DEBUG
        if (car_pos >= 0) {  // If item already exists, update it with new quantity
//            cout << "UPDATE!\n";  //DEBUG
            Cart* tmp_car_item = cart->get(car_pos);
            tmp_car_item->setQuant(tmp_car_item->getQuant() + car_item.getQuant());
            cart->set(car_pos, tmp_car_item);
            delete tmp_car_item;
            tmp_car_item = nullptr;
        } else {  // Otherwise, add item
//            cout << "ADD!\n";  //DEBUG
            cart->add(&car_item);        
        }
//        cart->display();  //DEBUG
//        cout << "ITEMS IN CART: " << cart->count() << "\n";  //DEBUG
        cart->close();
               
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
    
    // Display item
    cout << "\n";
    car_item->display();
    
    // Get item from Catalog
    catalog->open();
    cat_pos = catalog->find(car_item->getName());
    if (cat_pos < 0) {   // Check that item is still in stock
        cout << "\n   This item is no longer available (discontinued)\n";
    } else {  // Check price of item in catalog and display it
        cat_item = catalog->get(cat_pos);
        total = static_cast<float>(car_item->getQuant()) * cat_item->getPrice();
        cout << "   Unit Price: $" << setprecision(2) << fixed << cat_item->getPrice() << "\n";
        cout << "   Total: $" << setprecision(2) << fixed << total << "\n\n";
    }
    catalog->close();
    
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
        cout << "   Cancelled\n";
    }
    
    delete car_item;
    car_item = nullptr;
    delete cat_item;
    cat_item = nullptr;
}

void User::placeOrder() {
    
    cout << "-- Place order\n\n";
    
    char conf;
    float total = 0.0;
    int car_count, cat_pos, car_pos;
    Cart* car_items = nullptr;
    Catalog* cat_item = nullptr;
    
    viewCart();
    
    // Confirm before placing order
    cout << "\n   Proceed? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        
        // Get items from cart and store in memory
        cart->open();
        car_items = cart->getAll();
        car_count = cart->count();
        
        // Deduct quantity from catalog
        catalog->open();
        for (int i = 0; i < car_count; i++) {
            cat_pos = catalog->find(car_items[i].getName());
            // Item is in catalog
            if (cat_pos >= 0) {
                cat_item = catalog->get(cat_pos);
                // Item is in stock
                if (cat_item->getQuant() > 0) {
                    cat_item->setQuant(cat_item->getQuant() - car_items[i].getQuant());
                    catalog->set(cat_pos, cat_item);
                // Item is out of stock
                } else {
                    cout << "   Item << " << cat_item->getName() << " is out of stock and has been left in your cart.";
                    break;
                }
                total += cat_item->getPrice();
            // Item is not in catalog (discontinued)
            } else {
                cout << "   Item " << cat_item->getName() << " is discontinued and has been removed from your cart.";
            }
            // Remove item from cart
            car_pos = cart->find(cat_item->getName());
            cart->del(car_pos);
        }
        cart->close();
        catalog->close();
        
        cout << "   Order placed\n";
    } else {
        cout << "   Cancelled\n";
    }
    
    delete [] car_items;
    car_items = nullptr;
    delete cat_item;
    cat_item = nullptr;
}