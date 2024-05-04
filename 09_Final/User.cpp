/** \file */

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
    this->cart = new DBModel<Catalog>(account->getCartDBPath());
    this->hist = new DBModel<Catalog>(account->getHistDBPath());
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
        cout << "[I] View order history\n";
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
            case 'i':
                viewHist();
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

void User::viewCart(float& total) {
    cout << "\n-- Cart\n\n";
    
    float item_total = 0.0;
    int cart_count;
    Catalog* cart_item = nullptr;
    Catalog* ctlg_item = nullptr;
    
    // Sync prices with Catalog
    syncCart();    
    
    cart->open();
    catalog->open();
    
    // Display each item in cart and get total
    cart_count = cart->count();
    if (cart_count > 0) {
        for (int cart_pos = 0; cart_pos < cart_count; cart_pos++) {
            cart_item = cart->get(cart_pos);
            cout << "   -" << cart_pos << "-\n";
            cout << "   Name: " << cart_item->getName() << "\n";
            cout << "   Quantity: " << cart_item->getQuant() << "\n";
            cout << "   Price per unit: $" << setprecision(2) << fixed << cart_item->getPrice() << "\n";
            // Check that catalog is not out of stock for the item
            ctlg_item = catalog->get(catalog->find(cart_item->getName()));
            if (ctlg_item->getQuant() > 0) {
                item_total = cart_item->getPrice() * cart_item->getQuant();
                total += item_total;
                cout << "   Item total: $" << setprecision(2) << fixed << item_total << "\n\n";
            } else {
                cout << "   Item total: $" << setprecision(2) << fixed << 0.0 << " (Item out of stock!)\n\n";
            }
        }
        cout << "   Grand Total: $" << setprecision(2) << fixed << total << "\n";
    } else {
        cout << "   Cart is empty\n";
    }
        
    catalog->close();
    cart->close();
    
    delete cart_item;
    cart_item = nullptr;
    delete ctlg_item;
    ctlg_item = nullptr;
}
void User::viewCart(){
    float total = 0.0;
    viewCart(total);
}

void User::viewHist() {
    cout << "\n-- Order History\n\n";
    
    float item_total = 0.0, total = 0.0;
    int hist_count;
    Catalog* hist_item = nullptr;
    
    hist->open();
    
    // Display each item in cart and get total
    hist_count = hist->count();
    if (hist_count > 0) {
        for (int hist_pos = 0; hist_pos < hist_count; hist_pos++) {
            hist_item = hist->get(hist_pos);
            cout << "   -" << hist_pos << "-\n";
            cout << "   Name: " << hist_item->getName() << "\n";
            cout << "   Quantity: " << hist_item->getQuant() << "\n";
            cout << "   Price per unit: $" << setprecision(2) << fixed << hist_item->getPrice() << "\n";
            item_total = hist_item->getPrice() * hist_item->getQuant();
            cout << "   Item total: $" << setprecision(2) << fixed << item_total << "\n\n";
            total += item_total;
        }
        cout << "   Grand Total: $" << setprecision(2) << fixed << total << "\n";
    } else {
        cout << "   History is empty\n";
    }
        
    hist->close();
    
    delete hist_item;
    hist_item = nullptr;
}

void User::getHistTotal(float& total) {
    float item_total = 0.0, loc_total = 0.0;
    int loc_count;
    Catalog* hist_item = nullptr;
    
    hist->open();
    
    // Display each item in cart and get total
    loc_count = hist->count();
    if (loc_count > 0) {
        for (int hist_pos = 0; hist_pos < loc_count; hist_pos++) {
            hist_item = hist->get(hist_pos);
            item_total = hist_item->getPrice() * hist_item->getQuant();
            loc_total += item_total;
        }
        
    hist->close();
    
    total += loc_total;
    
    delete hist_item;
    hist_item = nullptr;
    }
}

void User::shopCatalog() {
    
    string input;
    char conf;
    int ctlg_pos;
    unsigned int quant;
    float total;
    Catalog* ctlg_item = nullptr;
    Catalog cart_item;
    
    cout << "\n-- Shop Catalog\n";
    syncCart();
    cout << "   Enter item name or item number\n";
    cout << ">> ";
    getline(cin, input);
    
    catalog->open();
    cart->open();
    
    // If user input is an integer, treat as index position
    if (isInt(input)) {
        ctlg_pos = stoi(input);
        if (!catalog->hasIndex(ctlg_pos)) {
            cout << "   Item # " << ctlg_pos << " not found\n";
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }
    // Otherwise treat as full item name
    else { 
        ctlg_pos = catalog->find(input);
        if (ctlg_pos < 0) {
            cout << "   Item \"" << input << "\" not found\n";
            return;
        }
//        cout << "POS: " << cat_pos << "\n";  //DEBUG
    }

    ctlg_item = catalog->get(ctlg_pos);

    // Display the item details
    
    cout << "\n";
    ctlg_item->display();
    cout << "             " << ctlg_item->getQuant() << "\n\n";
    
    // Get number of items to purchase from user
    cout << "   Enter the number of items to purchase (0 to cancel)\n";
    getNumeric<unsigned int>(quant);

    if (quant == 0) {  // Cancel
        cout << "\n   Cancelled\n";
        
        delete ctlg_item;
        ctlg_item = nullptr;
        return;
    } else if (quant > ctlg_item->getQuant()) {
        cout << "   There are not enough of that item in stock\n";
        
        delete ctlg_item;
        ctlg_item = nullptr;
        return;
    }
    
    // Populate cart item from catalog item
    cart_item.setName(ctlg_item->getName());
    cart_item.setQuant(quant);
    
    total = static_cast<float>(cart_item.getQuant()) * ctlg_item->getPrice();
    cout << "\n   Unit Price: $" << setprecision(2) << fixed << ctlg_item->getPrice() << "\n";
    cout << "   Total: $" << setprecision(2) << fixed << total << "\n\n";
    
    // Confirm before adding to cart
    cout << "   Add to cart? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {  // Add item to cart
        // Check if item is already in the cart
        int car_pos = cart->find(cart_item.getName());
//        cout << "FOUND: " << car_pos << "\n";  //DEBUG
        if (car_pos >= 0) {  // If item already exists, update it with new quantity
//            cout << "UPDATE!\n";  //DEBUG
            Catalog* tmp_car_item = cart->get(car_pos);
            tmp_car_item->setQuant(tmp_car_item->getQuant() + cart_item.getQuant());
            cart->set(car_pos, tmp_car_item);
            delete tmp_car_item;
            tmp_car_item = nullptr;
        } else {  // Otherwise, add item
//            cout << "ADD!\n";  //DEBUG
            cart->add(&cart_item);        
        }
//        cart->display();  //DEBUG
//        cout << "ITEMS IN CART: " << cart->count() << "\n";  //DEBUG
               
        cout << "   Cart updated\n";
    } else {
        cout << "   Cancelled";
    }    

    cart->close();
    catalog->close();
    
    delete ctlg_item;
    ctlg_item = nullptr;
}

void User::remFrmCart() {
    
    string input;
    char conf;
    int cart_pos, ctlg_pos;
    float total;
    Catalog* cart_item = nullptr;
    Catalog* ctlg_item = nullptr;
    
    cout << "\n-- Remove item from cart\n";
    syncCart();
    cout << "   Enter item name or item number\n";
    cout << ">> ";
    getline(cin, input);
    
    cart->open();
    catalog->open();
    
    // If user input is an integer, treat as index car_position
    if (isInt(input)) {
        cart_pos = stoi(input);
        if (!cart->hasIndex(cart_pos)) {
            cout << "   Item # " << cart_pos << " not found\n";
            delete cart_item;
            cart_item = nullptr;
            delete ctlg_item;
            ctlg_item = nullptr;
            return;
        }
//        cout << "POS: " << car_pos << "\n";  //DEBUG
        cart_item = cart->get(cart_pos);
    }
    // Otherwise treat as full item name
    else { 
        cart_pos = cart->find(input);
        if (cart_pos < 0) {
            cout << "   Item \"" << input << "\" not found\n";
            delete cart_item;
            cart_item = nullptr;
            delete ctlg_item;
            ctlg_item = nullptr;
            return;
        }
//        cout << "POS: " << car_pos << "\n";  //DEBUG
        cart_item = cart->get(cart_pos);
    }
    
    // Display item
    cout << "\n   Name: " << cart_item->getName() << "\n";
    cout << "   Quantity: " << cart_item->getQuant() << "\n";
    cout << "   Price per unit: $" << setprecision(2) << fixed << cart_item->getPrice() << "\n";
    // Get item from Catalog
    ctlg_pos = catalog->find(cart_item->getName());
    if (ctlg_pos < 0) {   // Check that item is still in stock
        cout << "\n   This item is no longer available (discontinued)\n";
    } else {  // Display price of item
        total = static_cast<float>(cart_item->getQuant()) * cart_item->getPrice();
        // Check if item is in stock. If item is out of stock, total is $0.0
        ctlg_item = catalog->get(ctlg_pos);
        if (ctlg_item->getQuant() > 0) {
            cout << "   Total: $" << setprecision(2) << fixed << total << "\n\n";
        } else {
            cout << "   Total: $" << setprecision(2) << fixed << 0.0 << " (Item out of stock!)\n\n";
        }
    }
    
    // Confirm before removing item from cart
    cout << "   Remove from cart? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        // Remove item from cart
        cart->del(cart_pos);
        cout << "   Item removed from your cart\n";
    } else {
        cout << "   Cancelled\n";
    }

    catalog->close();
    cart->close();
    
    delete cart_item;
    cart_item = nullptr;
    delete ctlg_item;
    ctlg_item = nullptr;
}

void User::placeOrder() {
    
    cout << "-- Place order\n\n";
    
    char conf;
    float total = 0.0;
    int cart_count, ctlg_pos, cart_pos;
    Catalog* cart_item = nullptr;
    Catalog* ctlg_item = nullptr;
    
    viewCart(total);  // Implicitly syncs prices with catalog
    
    catalog->open();
    cart->open();
    hist->open();

    // Confirm before placing order
    cout << "\n   Proceed? (Y/)\n";
    conf = getSingleChar();
    tolower(conf);
    if (conf == 'y') {
        cart_count = cart->count();
        // Deduct quantity from catalog
        for (int cart_pos = 0; cart_pos < cart_count; cart_pos++) {
            cart_item = cart->get(cart_pos);
            ctlg_pos = catalog->find(cart_item->getName());
            // Item is in catalog
            if (ctlg_pos >= 0) {
                ctlg_item = catalog->get(ctlg_pos);
                // Item is in stock
                if (ctlg_item->getQuant() > 0) {
                    // Deduct purchased quantity from catalog
                    ctlg_item->setQuant(ctlg_item->getQuant() - cart_item->getQuant());
                    catalog->set(ctlg_pos, ctlg_item);
                    // Add purchase to history
                    cout << "SIZE OF CTLGITEM: " << sizeof(*ctlg_item) << "\n";  //DEBUG
                    cout << "SIZE BFORE PASS: " << sizeof(*cart_item) << "\n";  //DEBUG
                    hist->add(cart_item);
                // Item is out of stock
                } else {
                    cout << "   Item << " << ctlg_item->getName() << " is out of stock and has been left in your cart.\n";
                    break;
                }
            // Item is not in catalog (discontinued)
            } else {
                cout << "   Item " << ctlg_item->getName() << " is discontinued and has been removed from your cart.\n";
            }
            // Remove item from cart
            cart->del(cart_pos);
        }
        
        cout << "   Order placed\n";
    } else {
        cout << "   Cancelled\n";
    }
    
    catalog->close();
    cart->close();
    hist->close();
    
    delete cart_item;
    cart_item = nullptr;
    delete ctlg_item;
    ctlg_item = nullptr;
}

void User::syncCart() {

    int cart_count, ctlg_pos;
    bool any_discont = false;
    Catalog* cart_item = nullptr;
    Catalog* ctlg_item = nullptr;
    
    cart->open();
    catalog->open();
    
    cart_count = cart->count();
    for (int cart_pos = 0; cart_pos < cart_count; cart_pos++) {
        cart_item = cart->get(cart_pos);
        ctlg_pos = catalog->find(cart_item->getName());
        // Item is in catalog, so sync price
        if (ctlg_pos >= 0) {
            ctlg_item = catalog->get(ctlg_pos);
            cart_item->setPrice(ctlg_item->getPrice());
            cart->set(cart_pos, cart_item);
        // Item is not in catalog (discontinued), so remove it
        } else {
            cart->del(cart_pos);
            cout << "   Item " << cart_item->getName() << " is discontinued and has been removed from your cart.\n";
            any_discont = true;
        }
    }
    if (any_discont) { cout << "\n"; }
    
    cart->close();
    catalog->close();
    
    delete cart_item;
    cart_item = nullptr;
    delete ctlg_item;
    ctlg_item = nullptr;
}