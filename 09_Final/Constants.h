/** \file */

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Constants.h
 * Author: hanne
 *
 * Created on April 6, 2024, 8:12 AM
 */


#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Constants.h"

// Constants

const short unsigned int MAXFLD = 81;

// Enums

/// @brief Return value specifying action to take on AccountDB record
enum Status {
    CLEAN,
    DIRTY,
    DELETE
};

#endif /* CONSTANTS_H */

