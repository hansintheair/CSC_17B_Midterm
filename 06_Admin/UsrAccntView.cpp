/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   UsrAccntView.cpp
 * Author: hanne
 * 
 * Created on March 21, 2024, 5:56 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;

#include "UsrAccntView.h"
#include "CatalogModel.h"

char UsrAccntView::mainMenu(const string& username) {
    cout << "\n--Big4Shopping--\n";
    cout << "--Signed in as " << username << "\n\n";
    cout << "A - User Profile\n";
    cout << "B - View Catalog\n";
    cout << "C - Shop Catalog\n";
    cout << "D - View Cart\n";
    cout << "E - Remove from Cart\n";
    cout << "F - Place order\n";
    cout << "Q - Logout\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

char UsrAccntView::profileMenu(const Account* usrAcct) {
    cout << "\n--Profile\n";
    cout << "Username: " << usrAcct->name << "\n";
    cout << "E-mail: " << usrAcct->email << "\n\n";

    cout << "A - Change e-mail\n";
    cout << "B - Change password\n";
    cout << "Q - Exit profile menu\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

void UsrAccntView::newEmail(string& email) {
    cout << "\n--Change e-mail\n";
    cout << "New e-mail: ";
    getline(cin, email);
}

void UsrAccntView::getPassw(const string& username, string& passw, string adj) {
    cout << "\n--Change password\n";
    cout << "Enter " << (adj.length() > 0 ? (adj + " ") : "") << "password for " << username << ": ";
    getline(cin, passw);
}

void UsrAccntView::shopCtlgTitle() {
    cout << "\n--Shop catalog\n";
}

void UsrAccntView::remCartItmTitle() {
    cout << "\n--Remove item from cart\n";
}

void UsrAccntView::placeOrderTitle() {
    cout << "\n--Place order\n";
}

void UsrAccntView::viewCartTitle() {
    cout << "\n--Shopping Cart\n\n";
}

void UsrAccntView::getSearchName(string& searchName) {
    cout << "Enter the name of an item: ";
    getline(cin, searchName);
}

unsigned short int UsrAccntView::getQuantity(unsigned int& quant) {

    cout << "Enter the number of items to purchase: ";

    unsigned int tquant;
    string squant;
    getline(cin, squant);

    //    cout << "QUANT GOT: " << squant << "\n";  //DEBUG
    try {
        tquant = stoul(squant);
        //        cout << "QUANT CONV: " << tquant << "\n";  //DEBUG
    } catch (invalid_argument) { //invalid value error
        return 1;
    } catch (out_of_range) { //value out of allowable range error
        return 2;
    }
    if (tquant > 0U - 1) { //value out of allowable range error
        return 2;
    }
    quant = tquant;
    return 0;
}

char UsrAccntView::addToCartPrmpt(const string& name, const unsigned int quant, const float unitPrice) {
    cout << "Add item " << quant << " of item " << name << " to cart for total of $";
    cout << setprecision(2) << fixed << unitPrice * quant << "? (Y/N)\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

char UsrAccntView::placeOrdrPrmpt() {
    cout << "Place order? (Y/N)\n\n";

    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore();
    return choice;
}

void UsrAccntView::orderPlaced() {
    cout << "Order has been placed successfully.\n";
}

void UsrAccntView::viewCatalog(const CatalogItem* catalogItems, int size) {
    cout << "\n--Catalog\n\n";
    for (int i = 0; i < size; i++) {
        cout << "Name: " << catalogItems[i].name << "\n";
        cout << "Description: " << catalogItems[i].desc << "\n";
        cout << "Price $" << fixed << setprecision(2) << catalogItems[i].price << "\n";
        cout << (catalogItems[i].quant > 0 ? "In stock" : "Out of stock") << "\n";
        if (i < size - 1) {
            cout << "\n";
        }
    }
}

void UsrAccntView::viewCartItem(const string& name, const string& desc, const unsigned int quant, const float price) {
    cout << "Name: " << name << "\n";
    cout << "Description: " << desc << "\n";
    cout << "Quantity: " << quant << "\n";
    cout << "Total $" << fixed << setprecision(2) << price << "\n";
}

void UsrAccntView::dispGrndTtl(float amount) {
    cout << "Order Total: $" << fixed << setprecision(2) << amount << "\n";
}

void UsrAccntView::chgPasswSuccess() {
    cout << "Password change succeeded.\n";
}

void UsrAccntView::acctDataCrrptErr() {
    cout << "Error: Account data corruption.\n";
}

void UsrAccntView::acctSaveErr() {
    cout << "Error: Failed to save profile data.\n";
}

void UsrAccntView::acctValidtErr() {
    cout << "Error: Invalid password.\n";
}

void UsrAccntView::itemExistErr() {
    cout << "Error: That item does not exist.\n";
}

void UsrAccntView::itemSaveErr() {
    cout << "Error: Failed to save item to cart.\n";
}

void UsrAccntView::quantityErr(unsigned int quant, const string& itemName) {
    cout << "Error: There are only " << quant << " of " << itemName << " in stock.\n";
}

void UsrAccntView::cartFullErr() {
    cout << "Error: Cannot add item to cart. Cart is full.\n";
}

void UsrAccntView::failToUpdtErr(const string& name) {
    cout << "Error: Failed to update the item " << name << ".\n";
}

void UsrAccntView::failOrderErr() {
    cout << "Error: Failed to place order\n";
}

void UsrAccntView::outOfRangeErr() {
    cout << "Error: Quantity out of allowable range.\n";
}

void UsrAccntView::invValErr() {
    cout << "Error: Invalid quantity input.\n";
}

void UsrAccntView::blank() {
    cout << "\n";
}