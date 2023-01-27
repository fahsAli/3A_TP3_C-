#include "shop.h"

shop::Shop::Shop(std::string sname)
:_shop_name(sname){

}

void shop::Shop::shopName(std::string sname){
    _shop_name = sname;
}

std::vector <client::Client> shop::Shop::clients() const{
    return _clients;
}

std::vector <product::Product> shop::Shop::products() const{
    return _products;
}

void shop::Shop::addProduct(){
    std::string title="",descp="";
    float price=0;
    int stock=0;
    std::cout << "enter product title : ";
    std::cin >> title;
    std::cout << "enter product description : ";
    std::cin.ignore();
    std::getline(std::cin,descp);
    std::cout << "enter product price : ";
    std::cin >> price;

    while(price <= 0){
        std::cout << "enter a valid price : ";
        std::cin >> price;
    }

    std::cout << "enter product stock : ";
    std::cin >> stock;

    while(stock <= 0){
        std::cout << "enter a valid stock : ";
        std::cin >> stock;
    }

    _products.push_back(product::Product(title,descp,stock,price));
    std::cout << std::endl;

}

void shop::Shop::addProduct(product::Product p){
    _products.push_back(p);
}

std::vector <cmd::Command> shop::Shop::commands() const{
    return _commands;
}

std::string shop::Shop::idByName(std::string fname,std::string lname){
    for(auto& it : _clients){
        if((it.firstName()==fname)||(it.lastName()==lname)){
            return it.id();
        }
    }
    return "null";
}

void shop::Shop::makeCommand(std::string id,std::vector <product::Product> products,cmd::Status status){
    for(auto it : _clients){
        if(it.id()==id){
            it.products(products);
            _commands.push_back(cmd::Command(it));
            _commands.at(_commands.size()-1).status(status);
        }
    }
}

void shop::Shop::productsList(){
    for(auto it=_products.begin();it!=_products.end();++it){
        std::cout << *it << std::endl;
    }
}


void shop::Shop::showProductWithTitle(){
    std::string title="";
    std::cout << "enter product title : ";
    std::cin >> title;

    for(auto it=_products.begin();it!=_products.end();++it){
        if(it->title()==title){
            std::cout << *it << std::endl;
            break;
        }
    }
}


void shop::Shop::updateStock(){
    std::string title="";
    int stock=0;
    bool change=false;
    std::cout << "enter product title : ";
    std::cin >> title;

    for(auto it=_products.begin();it!=_products.end();++it){
        if(it->title()==title){
            std::cout << "enter the new stock : ";
            std::cin >> stock;

            while(stock <= 0){
                std::cout << "enter a valid stock : ";
                std::cin >> stock;
            }
            change = true;
            it->stock(stock);
            break;
        }
    }

    if(!change){
        std::cout << "product not found try again later " << std::endl;
    }

}

void shop::Shop::updateStock(std::string title,int stock){
    for(auto it=_products.begin();it!=_products.end();++it){
        if(it->title()==title){
            it->stock(it->stock()+stock);
            break;
        }
    }
}


void shop::Shop::addClient(){
    std::string fname="",lname="";
    std::cout << "enter first name : ";
    std::cin >> fname;
    std::cout << "enter last name : ";
    std::cin >> lname;

    _clients.push_back(client::Client(fname,lname));
    std::cout << "welcome here and your id is : " << _clients.at(_clients.size()-1).id() << std::endl;
}

void shop::Shop::showAllClients(){
    std::cout << std::endl;
    for(auto it=_clients.begin();it!=_clients.end();++it){
        std::cout << *it << std::endl;
    }
}

void shop::Shop::showClientWithName(){
    std::string name="";
    std::cout << "enter your lname or id : ";
    std::cin >> name;

    for(auto it=_clients.begin();it!=_clients.end();++it){
        if((it->lastName()==name)||(it->id()==name)){
            std::cout << *it << std::endl;
            break;
        }
    }
}

void shop::addProductToBasket(client::Client &client,product::Product p){
    client.buyProduct(p);
}


void shop::Shop::buyProduct(){
    std::string title="",name="";
    int qty=0,index=0;
    bool foundClient=false;
    std::cout << "first enter your id or your last name : ";
    std::cin >> name;

    for(auto it=_clients.begin();it!=_clients.end();++it){
        if((it->lastName()==name)||(it->id()==name)){
            foundClient = true;
            break;
        }
        index++;
    }

    if(foundClient){
        this->productsList();
        std::cout << "enter the product name : ";
        std::cin >> title;
        std::cout << "enter the qty : ";
        std::cin >> qty;

        while(qty<=0){
            std::cout << "enter a valid qty : ";
            std::cin >> qty;
        }

        for(auto it=_products.begin();it!=_products.end();++it){
            if(it->title()==title){
                if(it->stock()>=qty){
                    it->stock(it->stock()-qty);
                        shop::addProductToBasket(_clients.at(index),product::Product(it->title(),it->description(),qty,it->price()));
                }else{
                    std::cout << "we dont have " << qty << " "<< it->title() << std::endl;
                    std::cout << "please wait restock or try lower qty than " << it->stock() << std::endl;
                    while((qty > it->stock())&&(qty!=0)){
                        std::cout << "enter qty or 0 to cancel : ";
                        std::cin >> qty;
                    }
                    if(qty!=0){
                        it->stock(it->stock()-qty);
                        shop::addProductToBasket(_clients.at(index),product::Product(it->title(),it->description(),qty,it->price()));
                        }
                }   
                break;
            }else{
                std::cout << "product not found please try again" << std::endl;
            }
        }
    }else{
        std::cout << "id or name not found please try again" << std::endl;
    }

}

void shop::Shop::returnProduct(){
    std::string id="",ptitle="";
    bool cfound=false,pfound=false;
    std::cout << "enter your last name or your id : ";
    std::cin >> id;

    while(!cfound){
        for(auto it=_clients.begin();it!=_clients.end();++it){
            if((it->lastName()==id)||(it->id()==id)){
                
                cfound = true;
                it->buyingList();
                std::cout << "enter the name of the product : ";
                std::cin >> ptitle;

                for(auto& it2 : it->basket()){
                    if(it2.title()==ptitle){
                        pfound = true;
                        it->returnProduct(it2);
                        this->updateStock(it2.title(),it2.stock());
                    }
                }

                while(!pfound){
                    std::cout << "product not found in your basket" << std::endl;
                    std::cout << "enter title again or enter c to cancel : ";
                    std::cin >> ptitle;

                    if(ptitle=="c"){
                        pfound = true;
                    }else{
                        for(auto& it2 : it->basket()){
                            if(it2.title()==ptitle){
                                pfound = true;
                                it->returnProduct(it2);
                                this->updateStock(it2.title(),it2.stock());
                            }
                        }
                    }
                }
                break;
            }
        }

        if(!cfound){
            std::cout << "client not found " << std::endl;
            std::cout << "enter your last name or your id again : ";
            std::cin >> id;
        }
    }
    std::cout << std::endl;
}


void shop::Shop::changeBuyingQty(){
    std::string id="",ptitle="";
    bool cfound=false,pfound=false;
    int qty=0,oldqty=0;
    std::cout << "enter your last name or your id : ";
    std::cin >> id;

    while(!cfound){
        for(auto it=_clients.begin();it!=_clients.end();++it){
            if((it->lastName()==id)||(it->id()==id)){
                
                cfound = true;
                it->buyingList();
                std::cout << "enter the name of the product : ";
                std::cin >> ptitle;

                for(auto& it2 : it->basket()){
                    if(it2.title()==ptitle){
                        pfound = true;

                        std::cout << "enter new qty : ";
                        std::cin >> qty;

                        while(qty<=0){
                            std::cout << "invalid qty enter again : ";
                            std::cin >> qty;
                        }
                        
                        oldqty = it2.stock();    
                        this->updateStock(it2.title(),(oldqty-qty));
                        it->changeQty(it2.title(),qty);
                    }
                }

                while(!pfound){
                    std::cout << "product not found in your basket" << std::endl;
                    std::cout << "enter title again or enter c to cancel : ";
                    std::cin >> ptitle;

                    if(ptitle=="c"){
                        pfound = true;
                    }else{
                        for(auto& it2 : it->basket()){
                            if(it2.title()==ptitle){
                                pfound = true;

                                std::cout << "enter new qty : ";
                                std::cin >> qty;

                                while(qty<=0){
                                    std::cout << "invalid qty enter again : ";
                                    std::cin >> qty;
                                }

                                oldqty = it2.stock();    
                                this->updateStock(it2.title(),(oldqty-qty));
                                it->changeQty(it2.title(),qty);
                            }
                        }
                    }
                }

                break;

            }
        }

        if(!cfound){
            std::cout << "client not found " << std::endl;
            std::cout << "enter your last name or your id again : ";
            std::cin >> id;
        }
    }
    std::cout << std::endl;
}

void shop::Shop::showBasketItems(){
    std::string name="";
    bool foundClient=false;
    std::cout << "first enter your id or your last name : ";
    std::cin >> name;

    while(!foundClient){
        for(auto it=_clients.begin();it!=_clients.end();++it){
            if((it->lastName()==name)||(it->id()==name)){
                foundClient = true;
                std::cout << it->buyingList();
                break;
            }
        }
        if(!foundClient){
            std::cout << "client not found " << std::endl;
            std::cout << "enter your last name or your id again : ";
            std::cin >> name;
        }
    }
}


void shop::Shop::showAllCommands(){
    for(auto &it: _commands){
        std::cout << it << std::endl;
    }
}

void shop::Shop::addClient(client::Client client){
    _clients.push_back(client);
}

void shop::Shop::showCommandByName(){
    std::string name="";
    bool found=false;
    std::cout << "enter last name or your id : ";
    std::cin >> name;

    for(auto &it: _commands){
        if((it.client().id()==name)||(it.client().lastName()==name)){
            found = true;
            std::cout << it << std::endl;            
        }
    }

    if(!found){
        std::cout << "command not found try again " << std::endl;
    }
}

void shop::Shop::showCommandByCId(){
    std::string id="";
    bool found=false;
    std::cout << "enter command id : ";
    std::cin >> id;

    for(auto &it: _commands){
        if(it.id()==id){
            found = true;
            std::cout << it << std::endl;            
        }
    }

    if(!found){
        std::cout << "command not found try again " << std::endl;
    }
}



void shop::Shop::changeStatus(){
    std::string id="";
    std::cout << "enter command id : ";
    std::cin >> id;
    bool found=false;
    int status=-1;
    std::cout << "enter new status (1: delivred , 0 not delivred) : "; 
    std::cin >> status;

    while((status>1)||(status<0)){
        std::cout << "invalid status enter again (1: delivred , 0 not delivred) : "; 
        std::cin >> status;
    }


    for(auto it=_commands.begin();it!=_commands.end();++it){
        if(id==it->id()){
            found = true;
            it->status(((status==1)?cmd::Status::delivred:cmd::Status::not_delivred));
            break;
        }
    }

    if(!found){
        std::cout << "command not found try again " << std::endl;
    }

}

void shop::Shop::makeCommand(){
    std::string id="";
    std::cout << "enter your last name or your id : ";
    std::cin >> id;

    for(auto it=_clients.begin();it!=_clients.end();++it){
        if((id==it->id())||(id==it->lastName())){
            _commands.push_back(*it);
            std::cout << _commands.at(_commands.size()-1) << std::endl;
            it->clearBasket();
        }
    }

}