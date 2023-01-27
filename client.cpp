#include "client.h"


int client::generateId(){
    static int a=1000;
    a++;
    return a;
}

bool client::alrInBasket(std::vector <product::Product> basket,std::string title){
    for(auto it=basket.begin();it!=basket.end();++it){
        if(it->title()==title){
            return true;
        }
    }
    return false;
}

client::Client::Client(std::string fname,std::string lname)
:_first_name(fname),_last_name(lname){
    _id = std::to_string(client::generateId());
}

client::Client::Client(std::vector <product::Product> basket,std::string fname,std::string lname)
:_first_name(fname),_last_name(lname){
    _id = std::to_string(client::generateId());
    _basket = basket;
}

std::string client::Client::firstName() const{
    return _first_name;
}

std::string client::Client::lastName() const{
    return _last_name;
}

std::string client::Client::id() const{
    return _id;
}

std::vector <product::Product> client::Client::basket() const{
    return _basket;
}

std::string client::Client::buyingList() const{
    std::string str="--------------------------\n>> buying list : \n";
    float money=0;
    for(auto it=_basket.begin();it!=_basket.end();++it){
        str = str + "title : " + it->title() + "\n";
        str = str + "amount : " + std::to_string(it->stock()) + "\n";
        str = str + "price : " + std::to_string(it->price()) + "\n";
        str = str + "\n";
        money += it->price()*it->stock();
    }
    str = str + "total : " + std::to_string(money) + "\n";
    return str + "--------------------------\n";
}

void client::Client::firstName(std::string fname){
    _first_name = fname;
}

void client::Client::lastName(std::string lname){
    _last_name = lname;
}

void client::Client::products(std::vector <product::Product> basket){
    _basket = basket;
}

void client::Client::buyProduct(product::Product prod){
    if(!client::alrInBasket(_basket,prod.title())){
        _basket.push_back(prod);
    }else{
        for(auto it=_basket.begin();it!=_basket.end();++it){
            if(it->title()==prod.title()){
                it->stock(it->stock()+prod.stock());
            }
        }
    }
}

void client::Client::returnProduct(product::Product prod){
    for(int i=0;i<_basket.size();i++){
        if(prod.title()==_basket.at(i).title()){
            _basket.erase(_basket.begin()+i);
            break;
        }
    }
}

void client::Client::changeQty(std::string title,int qty){
    for(auto it=_basket.begin();it!=_basket.end();++it){
        if(it->title()==title){
            it->stock(qty);
        }
    }
}

void client::Client::clearBasket(){
    _basket.clear();
}

std::ostream& client::operator<< (std::ostream &os,const client::Client& c){
    os << "first name : " + c.firstName() + "\n";
    os << "last name : " + c.lastName() + "\n";
    os << "client ID : " + c.id() + "\n";
    return os;
}

std::ostream& client::operator<< (std::ostream &os,std::vector <product::Product> v){
    std::string str="--------------------------\n>> buying list : \n";
    float money=0;
    for(auto it=v.begin();it!=v.end();++it){
        str = str + "title : " + it->title() + "\n";
        str = str + "amount : " + std::to_string(it->stock()) + "\n";
        str = str + "price : " + std::to_string(it->price()) + "\n";
        str = str + "\n";
        money += it->price()*it->stock();
    }
    str = str + "total : " + std::to_string(money) + "\n";
    os << str + "--------------------------\n";
    return os;
}
