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

#include "CatalogItem.h"

const short unsigned int MAXITEMS = 1000;

class CatalogModel {
private:
    string catalog_db;
    CatalogItem catalog[MAXITEMS];
    unsigned short int num_items;
    short int findItem(string);
public:
    CatalogModel(string);
//    CatalogModel(const CatalogModel& orig);
    void display();
    void display(string);
    short unsigned int getSize();
    void addItem(const CatalogItem&);
    void repItem(string, const CatalogItem&);
    void delItem(string);

    void save();
    static void createDB(string);
//    virtual ~CatalogModel();
};

#endif /* CATALOGMODEL_H */

