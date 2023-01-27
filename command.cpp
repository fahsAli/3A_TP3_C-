#include "command.h"

int cmd::generatecmdId(){
    static int a=1000;
    a++;
    return a;
}


cmd::Command::Command(client::Client client)
:_client(client){
    _cbasket = _client.basket();
    _status = cmd::Status::not_delivred;
    _id = std::to_string(cmd::generatecmdId());
}

client::Client cmd::Command::client() const{
    return _client;
}

std::vector <product::Product> cmd::Command::basket() const{
    return _cbasket;
}

cmd::Status cmd::Command::status() const{
    return _status;
}

float cmd::Command::totalPrice() const{
    float price=0.0;
    for(auto it=_cbasket.begin();it!=_cbasket.end();++it){
        price += it->price()*it->stock();
    }
    return price;
}

std::string cmd::Command::id() const{
    return _id;
}

void cmd::Command::status(cmd::Status status){
    _status = status;
}

std::string cmd::Command::basketList() const{
    std::string str="> command list : \n";
    for(auto it=_cbasket.begin();it!=_cbasket.end();++it){
        str = str + "title : " + it->title() + "\n";
        str = str + "amount : " + std::to_string(it->stock()) + "\n";
        str = str + "price : " + std::to_string(it->price()) + "\n";
        str = str + "\n";
    }
    return str;
}


std::ostream& cmd::operator<<(std::ostream& os,const cmd::Command cmd){
    os << "--------------------------\nclient : " + cmd.client().firstName() + " " + cmd.client().lastName() + "\n";
    os << "command id : " + cmd.id() + "\n";
    os << cmd.basketList() + "\n";
    os << "total : " + std::to_string(cmd.totalPrice()) + "\n" + "status : " + ((cmd::Status::delivred==cmd.status())?"delivred":"not delivred") + "\n--------------------------\n";
    return os;
}








