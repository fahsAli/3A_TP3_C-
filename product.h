#pragma once
#ifndef PRODUCT_HEADER
#define PRODUCT_HEADER

#include <string>

namespace product{
    class Product{
        public:
            Product(std::string title="null",std::string descp="null",int stock=0,float price=0.0);

            std::string title() const;
            std::string description() const;
            int stock() const;
            float price() const;

            void title(std::string title);
            void description(std::string descp);
            void stock(int stock);
            void price(float price);

        private:
            std::string _title;
            std::string _description;
            int _stock;
            float _price;

    };
    std::ostream& operator<< (std::ostream &os,const Product& p);
}

#endif