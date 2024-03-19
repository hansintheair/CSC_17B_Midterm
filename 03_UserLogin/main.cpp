/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: hanne
 *
 * Created on March 17, 2024, 2:50 PM
 */

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

#include "UsrAccntsModel.h"

/*
 * 
 */
int main() {

    string accts_db = "data/users.bin";
    UsrAccntsModel::createDB(accts_db);
    UsrAccntsModel users = UsrAccntsModel(accts_db);
    
    bool quit = false;
    char input;
    while (!quit) {
        cout << "Please choose an option:\n";
        cout << "A - Display count\n";
        cout << "B - Display user accounts\n";
//        cout << "C - Display specific user account\n";
        cout << "D - Add account\n";
        cout << "E - Replace account\n";
        cout << "F - Delete account\n";
        cout << "G - Save\n";
        cout << "Q = Quit\n";
        
        cout << ">> ";
        cin >> input;
        input = tolower(input);

        string temp_input_a, temp_input_b;
        Account temp_acct;
        switch(input){
            case 'a':  //Display count
                cout << "\n";
                cout << "Number of users in database: " << users.getSize() << ".\n";
                cout << "\n";
                break;
            case 'b':  //Display all
                cout << "\n";
                users.display();
                break;
//            case 'c':  //Display specific
//                cout << "\n";
//                cout << "Enter name of account display: ";
//                cin.ignore();
//                getline(cin, temp_input_a);
//                cout << "\n";
//                cout << "Enter password for the account: ";
//                getline(cin, temp_input_b);
//                cout << "\n";
//                users.getAcct(temp_input_a, temp_input_b)->display();
//                cout << "\n";
//                break;
            case 'd':  //Add account
                cout << "\n";
                cin.ignore();
                cout << "User name: ";
                getline(cin, temp_input_a);
                strncpy(temp_acct.name, temp_input_a.c_str(), MAXFLD -1 );
                cout << "User email: ";
                getline(cin, temp_input_a);
                strncpy(temp_acct.email, temp_input_a.c_str(), MAXFLD - 1);
                cout << "User password: ";
                getline(cin, temp_input_a);
                strncpy(temp_acct.passw, temp_input_a.c_str(), MAXFLD -1 );
                cout << "Admin (0=No, 1=Yes): ";
                cin >> temp_acct.admin;
                strncpy(temp_acct.cartdb, ("data/" + string(temp_acct.name) + ".db").c_str(), MAXFLD - 1);
                users.addAcct(temp_acct);
                cout << "\n\n";
                break;
//            case 'e': //Edit account
//                cout << "\n";
//                cout << "Enter new values for item:\n";
//                cin.ignore();
//                strncpy(temp_acct.name, temp_input_a.c_str(), MAXFLD -1 );
//                cout << "Item description: ";
//                getline(cin, temp_input_a);
//                strncpy(temp_acct.desc, temp_input_a.c_str(), MAXFLD - 1);
//                cout << "Item price: ";
//                cin >> temp_acct.price;
//                cout << "Item quantity: ";
//                cin >> temp_acct.quant;
//                cout << "Enter name of item to replace with new item: ";
//                cin.ignore();
//                getline(cin, temp_input_a);
//                users.repItem(temp_input_a, temp_acct);
//                cout << "\n";
//                break;
            case 'f':  //Delete account
                cout << "\n";
                cout << "Name of item to delete: ";
                cin >> temp_input_a;
                users.delAcct(temp_input_a);
                cout << "\n";
                break;
            case 'g':  //Save
                cout << "\n";
                cout << "Saving\n";
                users.save();
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

