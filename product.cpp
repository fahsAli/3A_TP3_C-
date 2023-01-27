#include "product.h"


product::Product::Product(std::string title,std::string descp,int stock,float price)
:_title(title),_description(descp),_stock(stock),_price(price){

}

std::string product::Product::title() const{
    return _title;
}

std::string product::Product::description() const{
    return _description;
}

int product::Product::stock() const{
    return _stock;
}

float product::Product::price() const{
    return _price;
}

void product::Product::title(std::string title){
    _title = title;
}

void product::Product::description(std::string descp){
    _description = descp;
}

void product::Product::stock(int stock){
    _stock = stock;
}

void product::Product::price(float price){
    _price = price;
}

std::ostream& product::operator<< (std::ostream &os,const product::Product& p){
    os << "title : " + p.title() + "\n";
    os << "description : " + p.description() + "\n";
    os << "stock : " + ((p.stock()==0)?"out of stock":std::to_string(p.stock())) + "\n";
    os << "price : " + std::to_string(p.price()) + "\n";
    return os;
}
