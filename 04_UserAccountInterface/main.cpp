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

#include "CatalogModel.h"
#include "UsrAccntsModel.h"
#include "HomeView.h"
#include "HomeController.h"

/*
 * 
 */
int main() {

    string accts_db = "data/users.bin";
    UsrAccntsModel::createDB(accts_db);
    UsrAccntsModel users = UsrAccntsModel(accts_db);
    
    string catalog_db = "data/catalog.bin";
    CatalogModel catalog = CatalogModel(catalog_db);
    
    HomeView homeView = HomeView();
    HomeController homeCont = HomeController(&users, &homeView, &catalog);
    
    homeCont.main();
    
    return 0;
}

