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
#include "HomeView.h"

class HomeController {
public:
    HomeController(UsrAccntsModel*, HomeView*);
    void main();
    void createUser(string, string, string);
    void loginUser();
    
private:
    UsrAccntsModel *accntsModel;
    HomeView *homeView;
};

#endif /* HOMECONTROLLER_H */

