#pragma once
#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <string>
#include <vector>

#include "product.h"

namespace client{
    class Client{
        public:
            Client(std::string fname="null",std::string lname="null");
            Client(std::vector <product::Product> basket,std::string fname="null",std::string lname="null");

            std::string firstName() const;
            std::string lastName() const;
            std::string id() const;
            std::vector <product::Product> basket() const;
            std::string buyingList() const;
            

            void firstName(std::string fname);
            void lastName(std::string lname);
            void products(std::vector <product::Product> basket);

            void buyProduct(product::Product prod);
            void returnProduct(product::Product prod);
            void changeQty(std::string title,int qty);

            void clearBasket();

        private:
            std::string _first_name;
            std::string _last_name;
            std::string _id;
            std::vector <product::Product> _basket; 
    };
    int generateId();
    bool alrInBasket(std::vector <product::Product> basket,std::string title);
    std::ostream& operator<< (std::ostream &os,const Client& c);
    std::ostream& operator<< (std::ostream &os,std::vector <product::Product> v);
}

#endif