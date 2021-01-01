#pragma once
#include"Item.h"
#include"coffShop.h"



void main_menu();                                      // main menu

void customer_menu();                                  // costumer options

void admin_access();

int checkAccess(std::string, std::string);            // check if the access is valid

void creatAcount();                                   // create staff account

void login();                

void admin_menu();                                   // admin option
