#pragma once
#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER

#include <iostream>
#include <fstream>

#include "product.h"
#include "client.h"
#include "command.h"
#include "shop.h"


namespace program
{
    class Program{
        public:


        void productManagement();
        void clientManagement();
        void commandManagement();
        void launch();

        void uploadClients();
        void getClients();

        void uploadProducts();
        void getProducts();

        void uploadCommands();
        void getCommands();

        private:
        shop::Shop _easystore;

    };

    std::string getElement(std::string str,int index);
    int countLines(std::string fname);
}

#endif