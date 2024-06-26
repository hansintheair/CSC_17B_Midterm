/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   HomeController.h
 * Author: hanne
 *
 * Created on March 18, 2024, 6:21 PM
 */

#ifndef HOMECONTROLLER_H
#define HOMECONTROLLER_H

#include "UsrAccntsModel.h"
#include "CatalogModel.h"
#include "HomeView.h"
#include "CatalogModel.h"
#include "UsrAccntController.h"
#include "UsrAccntView.h"

class HomeController {
public:
    HomeController(UsrAccntsModel*, HomeView*, CatalogModel*);
    void main();
    void createUser();
    void loginUser();
    ~HomeController();
private:
    UsrAccntsModel *accntsModel;
    HomeView *homeView;
    CatalogModel *catlgModel;
};

#endif /* HOMECONTROLLER_H */

