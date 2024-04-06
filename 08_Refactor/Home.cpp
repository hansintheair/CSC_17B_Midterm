/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Home.cpp
 * Author: hanne
 * 
 * Created on April 6, 2024, 8:28 AM
 */

#include "Home.h"

Home::Home() {
}

void Home::main() {
    bool quit = false;
    char input;
    while (!quit) {
        
        cout << "\n--Big4Shopping--\n\n";
        cout << "A - Login\n";
        cout << "B - Create user\n";
        cout << "Q - Exit\n\n";

        input = getSingleChar();
        input = tolower(input);
        switch (input) {
            case 'a':
//                loginUser();
                break;
            case 'b':
//                createUser();
                break;
            case 'q': //Quit
                cout << "\n";
                quit = true;
                break;
            default:
                cout << "Unknown input, please try again\n";
        };
    }
    cout << "Exiting program\n";
}

