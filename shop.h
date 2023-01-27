#pragma once
#ifndef SHOP_HEADER
#define SHOP_HEADER

#include <iostream>
#include <string>

#include "product.h"
#include "client.h"
#include "command.h"

namespace shop{
    class Shop{
        public:
            Shop(std::string sname="null");

            std::vector <client::Client> clients() const;
            std::vector <product::Product> products() const;
            std::vector <cmd::Command> commands() const;
            std::string idByName(std::string fname,std::string lname);

            void shopName(std::string sname);

            void addProduct();
            void addProduct(product::Product p);
            void productsList();
            void showProductWithTitle();
            void updateStock();
            void updateStock(std::string title,int stock);

            void addClient();
            void addClient(client::Client client);
            void showAllClients();
            void showClientWithName();
            void buyProduct();
            void returnProduct();
            void changeBuyingQty();
            void showBasketItems();

            void makeCommand();
            void makeCommand(std::string id,std::vector <product::Product> products,cmd::Status status);
            void changeStatus();
            void showAllCommands();
            void showCommandByName();
            void showCommandByCId();


        private:
            std::string _shop_name;
            std::vector <client::Client> _clients;
            std::vector <product::Product> _products;
            std::vector <cmd::Command> _commands;

    };
    void addProductToBasket(client::Client &client,product::Product p);

}

#endif