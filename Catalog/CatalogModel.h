/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   CatalogModel.h
 * Author: hannes
 *
 * Created on March 16, 2024, 3:40 PM
 */

#ifndef CATALOGMODEL_H
#define CATALOGMODEL_H

#include <string>
using namespace std;

#include "CatalogItem.h"

const short unsigned int MAXDB = 1000;

class CatalogModel {
private:
    string catalogDB;
    CatalogItem catalog[MAXDB];
public:
    CatalogModel();
    CatalogModel(const CatalogModel& orig);
    virtual ~CatalogModel();
};

#endif /* CATALOGMODEL_H */

