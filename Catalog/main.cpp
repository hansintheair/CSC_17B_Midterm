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
        cout << "E - Delete catalog item\n";
        cout << "F - Save catalog\n";
        cout << "Q = Quit\n";
        
        cout << ">> ";
        cin >> input;
        input = tolower(input);

        string temp_input;
        CatalogItem temp_item;
        switch(input){
            case 'a':
                cout << "Number of items in catalog: " << catalog.getSize() << ".\n";
                cout << "\n";
                break;
            case 'b':
                catalog.display();
                cout << "\n";
                break;
            case 'c':
                cout << "CHOICE C\n";
                cout << "\n";
                break;
            case 'd':
                cin.ignore();
                cout << "Item name: ";
                getline(cin, temp_input);
                strncpy(temp_item.name, temp_input.c_str(), MAXNAME -1 );
//                temp_item.name[MAXNAME - 1] = '\0';
                cout << "Item description: ";
//                cin.ignore();
                getline(cin, temp_input);
                strncpy(temp_item.desc, temp_input.c_str(), MAXDESC - 1);
//                temp_item.name[MAXDESC - 1] = '\0';
                cout << "Item price: ";
                cin >> temp_item.price;
                cout << "Item quantity: ";
                cin >> temp_item.quant;
                cout << "\n";
                catalog.addItem(temp_item);
                break;
            case 'e':
                cout << "Name of item to delete: ";
                cin >> temp_input;
                catalog.delItem(temp_input);
                cout << "\n";
                break;
            case 'f':
                cout << "Saving\n";
                catalog.save();
                break;
            case 'q':
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