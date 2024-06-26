/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Generics.h
 * Author: hannes
 *
 * Created on April 5, 2024, 5:23 PM
 * 
 * Generic data and functions.
 * 
 */

#ifndef GENERICS_H
#define GENERICS_H

#include <type_traits>
#include <cstring>
#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "DBModel.h"

// Generic helper methods

template <typename T, typename enable_if<is_arithmetic<T>::value>::type* = nullptr>
void getNumeric(T& num) {
    cout << ">> ";
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ">> ";
        cin >> num;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

inline char getSingleChar() {
    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

inline void safeGetLine(string& dest, unsigned int max_len) {
    while (true) {
        cout << ">> ";
        getline(cin, dest);
        if (dest.length() < max_len) break;
        else cout << "Input must be less than " << max_len-1 << " characters long.\n";
    }
}

inline void safeCStrNCpy(char* dest, string src, int max_len) {
    strncpy(dest, src.c_str(), max_len-1);
    dest[max_len-1] = '\0';
}

inline bool isInt(const string& value) {
    for (char c : value) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Random Data Generators

inline float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

inline unsigned int randomUnsInt(unsigned int min, unsigned int max) {
    return min + static_cast<unsigned int>(rand()) % (max - min + 1);
}





#endif /* GENERICS_H */

