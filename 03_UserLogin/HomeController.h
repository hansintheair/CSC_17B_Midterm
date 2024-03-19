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


class HomeController {
public:
    HomeController(UsrAccntsModel*);
    void createUser(string, string, string);
    void loginUser(string, string);
    
private:
    UsrAccntsModel *accntsModel;
};

#endif /* HOMECONTROLLER_H */

