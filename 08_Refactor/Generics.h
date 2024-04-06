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

// Constants

// Data Abstracts

// Generic helper methods

using namespace std;

template <typename T, typename enable_if<is_arithmetic<T>::value>::type* = nullptr>
void getNumeric(T& num) {
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore();
        cin >> num;
    }
}

inline void safeCStrNCpy(char* dest, string src, int max_len) {
    strncpy(dest, src.c_str(), max_len-1);
    dest[max_len-1] = '\0';
}


#endif /* GENERICS_H */

