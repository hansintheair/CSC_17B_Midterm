/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: hanne
 *
 * Created on March 16, 2024, 3:39 PM
 */

#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

#include "CatalogModel.h"

/*
 * 
 */
int main(int argc, char** argv) {

    string catalog_db = "data/catalog.bin";
    CatalogModel::createDB(catalog_db);
    CatalogModel catalog = CatalogModel(catalog_db);

    bool quit = false;
    char input;
    while (!quit) {
        cout << "Please choose an option:\n";
        cout << "A - Display count\n";
        cout << "B - Display catalog\n";
        cout << "C - Display specific catalog item\n";
        cout << "D - Add catalog item\n";
        cout << "E - Replace catalog item\n";
        cout << "F - Delete catalog item\n";
        cout << "G - Save catalog\n";
        cout << "Q = Quit\n";
        
        cout << ">> ";
        cin >> input;
        input = tolower(input);

        string temp_input;
        CatalogItem temp_item;
        switch(input){
            case 'a':  //Display count
                cout << "\n";
                cout << "Number of items in catalog: " << catalog.getSize() << ".\n";
                cout << "\n";
                break;
            case 'b':  //Display all
                cout << "\n";
                catalog.display();
                break;
            case 'c':  //Display specific
                cout << "\n";
                cout << "Enter name of item to display: ";
                cin.ignore();
                getline(cin, temp_input);
                cout << "\n";
                catalog.display(temp_input);
                cout << "\n";
                break;
            case 'd':  //Add item
                cout << "\n";
                cin.ignore();
                cout << "Item name: ";
                getline(cin, temp_input);
                strncpy(temp_item.name, temp_input.c_str(), MAXNAME -1 );
                cout << "Item description: ";
                getline(cin, temp_input);
                strncpy(temp_item.desc, temp_input.c_str(), MAXDESC - 1);
                cout << "Item price: ";
                cin >> temp_item.price;
                cout << "Item quantity: ";
                cin >> temp_item.quant;
                catalog.addItem(temp_item);
                cout << "\n\n";
                break;
            case 'e': //Edit item
                cout << "\n";
                cout << "Enter new values for item:\n";
                cin.ignore();
                cout << "Item name: ";
                getline(cin, temp_input);
                strncpy(temp_item.name, temp_input.c_str(), MAXNAME -1 );
                cout << "Item description: ";
                getline(cin, temp_input);
                strncpy(temp_item.desc, temp_input.c_str(), MAXDESC - 1);
                cout << "Item price: ";
                cin >> temp_item.price;
                cout << "Item quantity: ";
                cin >> temp_item.quant;
                cout << "Enter name of item to replace with new item: ";
                cin.ignore();
                getline(cin, temp_input);
                catalog.repItem(temp_input, temp_item);
                cout << "\n";
                break;
            case 'f':  //Delete item
                cout << "\n";
                cout << "Name of item to delete: ";
                cin >> temp_input;
                catalog.delItem(temp_input);
                cout << "\n";
                break;
            case 'g':  //Save
                cout << "\n";
                cout << "Saving\n";
                catalog.save();
                cout << "\n";
                break;
            case 'q':  //Quit
                cout << "\n";
                quit=true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "QUITTING\n";

    return 0;
}