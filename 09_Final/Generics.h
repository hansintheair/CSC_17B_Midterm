/** \file */

/**
 * \anchor Generics
 * \class Generics
 * A collection of generic functions that are broadly useful throughout the project and don't belong to any 
 * specific class.
 * 
 * It is used in Admin to generate a random password.
 */

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

/// @brief Get a numeric value of specified numeric type from the user
/// @tparam T Specified numeric type
/// @param num variable to store user input
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

/// @brief Get a single char from the user
/// @return The user input
inline char getSingleChar() {
    char choice;
    cout << ">> ";
    cin.get(choice);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

/// @brief Get a line of text (string) from the user
/// @param dest The variable to store the user input in
/// @param max_len The maximum length of text to get from the user
inline void safeGetLine(string& dest, unsigned int max_len) {
    while (true) {
        cout << ">> ";
        getline(cin, dest);
        if (dest.length() < max_len) break;
        else cout << "Input must be less than " << max_len-1 << " characters long.\n";
    }
}

/// @brief Safely copy a string to a cstring
/// @param dest The cstring to copy the string into
/// @param src The string to be copied to the cstring
/// @param max_len The maximum length that can be stored in the cstring
inline void safeCStrNCpy(char* dest, string src, int max_len) {
    strncpy(dest, src.c_str(), max_len-1);
    dest[max_len-1] = '\0';
}

/// @brief Check whether the input string is an integer
/// @param value The string to check
/// @return True if value is an integer
inline bool isInt(const string& value) {
    for (char c : value) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Random Data Generators

/// @brief Generate a random floating point number
/// @param min Smallest number in range
/// @param max Largest number in range
/// @return A random floating point number within the specified range
inline float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

/// @brief Generate a random integer number
/// @param min Smallest number in range
/// @param max Largest number in range
/// @return A random integer number within the specified range
inline unsigned int randomUnsInt(unsigned int min, unsigned int max) {
    return min + static_cast<unsigned int>(rand()) % (max - min + 1);
}

/// @brief Append a random string of letters and numbers of the given length to the given input string
/// @param str The string to be appended to
/// @param len The number of random letters and numbers to append
inline void randomString(string& str, unsigned short int len) {
    char clist[] = "abcdefghijklmnopqrstuvwxyz1234567890";
    short unsigned int size = strlen(clist);
    
    for (int i = 0; i < len; i++) {
        str += clist[rand() % size];
    }
}

#endif /* GENERICS_H */

