#include "program.h"


void program::Program::productManagement(){
    
    int option=0;
    bool end = false;

    std::cout << "   >> product management <<   " << std::endl;
    
    while(!end){
        std::cout << "1)  add a product" << std::endl; 
        std::cout << "2)  product list" << std::endl;   
        std::cout << "3)  find product by title" << std::endl;
        std::cout << "4)  update stock" << std::endl;
        std::cout << "5)  back" << std::endl;
                
        
        std::cout << "enter your choice : ";
        std::cin >> option; std::cout << std::endl;

        while((option < 1)||(option>5)){
            std::cout << "please choose again : "<< std::endl;
            std::cin >> option;
        }

        switch (option)
        {
            case 1:
                _easystore.addProduct();
                break;
            case 2:
                _easystore.productsList();
                break;
            case 3:
                _easystore.showProductWithTitle();
                break;
            case 4:
                _easystore.updateStock();
                break;
            case 5:
                end=true;
                break;
        }

    }

}


void program::Program::clientManagement(){
    int option=0;
    bool end = false;

    std::cout << "   >> client management <<   " << std::endl;
    
    while(!end){
        std::cout << "1)  add a client" << std::endl; 
        std::cout << "2)  client list" << std::endl;   
        std::cout << "3)  find a client by name" << std::endl;
        std::cout << "4)  buy a product" << std::endl;
        std::cout << "5)  return a product" << std::endl;
        std::cout << "6)  change qty of a product" << std::endl;
        std::cout << "7)  show all items in basket" << std::endl;
        std::cout << "8)  back" << std::endl;       
        
        std::cout << "enter your choice : ";
        std::cin >> option; std::cout << std::endl;

        while((option < 1)||(option>8)){
            std::cout << "please choose again : "<< std::endl;
            std::cin >> option;
        }

        switch (option)
        {
            case 1:
                _easystore.addClient();
                break;
            case 2:
                _easystore.showAllClients();
                break;
            case 3:
                _easystore.showClientWithName();
                break;
            case 4:
                _easystore.buyProduct();
                break;
            case 5:
                _easystore.returnProduct();
                break;
            case 6:
                _easystore.changeBuyingQty();
                break;
            case 7:
                _easystore.showBasketItems();
                break;
            case 8:
                end=true;
                break;
        }

    }
}


void program::Program::commandManagement(){
    int option=0;
    bool end = false;

    std::cout << "   >> command management <<   " << std::endl;
    
    while(!end){
        std::cout << "1)  validate a command" << std::endl; 
        std::cout << "2)  update command status" << std::endl;   
        std::cout << "3)  show all commands" << std::endl;
        std::cout << "4)  find a command by client name or id" << std::endl;
        std::cout << "5)  find a command by command id" << std::endl;
        std::cout << "6)  back" << std::endl;
                
        
        std::cout << "enter your choice : ";
        std::cin >> option; std::cout << std::endl;

        while((option < 1)||(option>6)){
            std::cout << "please choose again : "<< std::endl;
            std::cin >> option;
        }

        switch (option)
        {
            case 1:
                _easystore.makeCommand();
                break;
            case 2:
                _easystore.changeStatus();
                break;
            case 3:
                _easystore.showAllCommands();
                break;
            case 4:
                _easystore.showClientWithName();
                break;
            case 5:
                _easystore.showCommandByCId();
                break;
            case 6:
                end=true;
                break;
        }

    }
}


std::string program::getElement(std::string str,int index){
    int flag=0;
    std::string elem="";
    for(int i=0;i<str.length();i++){
        if((str[i]==']')&&(flag==index)){
            break;
        }
        if(flag==index){
            elem = elem + str[i];
        }
        if(str[i]=='['){
            flag++;
        }
    }
    return elem;
}

int program::countLines(std::string fname){
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(fname);

    while (std::getline(myfile, line)){
        ++number_of_lines;
    }

    return number_of_lines;
}

void program::Program::uploadClients(){
   std::fstream newfile;
   newfile.open("clients.txt",std::ios::out);
   if(newfile.is_open()) {
        for(auto& it : _easystore.clients()){
            newfile << "["+ it.firstName() + "] " + "[" + it.lastName() + "] " + "[" + std::to_string(it.basket().size()) + "]\n";
            for(auto& it2: it.basket()){
                newfile << "["+ it2.title() + "] " + "[" + it2.description() + "] " + "[" + std::to_string(it2.stock()) + "] " + "[" + std::to_string(it2.price()) + "]\n";        
            }
        }
    }
    newfile.close();
}

void program::Program::getClients(){
    std::string fname="";
    std::string lname="";
    std::string title="",descp="";
    float price=0.0;
    int i=0,line=1,skipline=0,amount=0;
    std::vector <product::Product> basket;
    std::fstream newfile;
    newfile.open("clients.txt",std::ios::in);
    if (newfile.is_open()){ 
        std::string tp;
        while(line <= countLines("clients.txt")){
            std::getline(newfile, tp);
            skipline = line + std::stoi(getElement(tp,3));
            fname = getElement(tp,1);
            lname = getElement(tp,2);
            line++;
            
            while(line<=skipline){
                std::getline(newfile, tp);
                title = getElement(tp,1);
                descp = getElement(tp,2);
                amount = std::stoi(getElement(tp,3));
                price = std::stof(getElement(tp,4));
                basket.push_back(product::Product(title,descp,amount,price));
                line++;
            }
            _easystore.addClient(client::Client(basket,fname,lname));
            basket.clear();
        }
        
        newfile.close();
    }else{
        std::cout<<"\nerror while opening clients.txt\n";
    }
}

void program::Program::uploadProducts(){
   std::fstream newfile;
   newfile.open("products.txt",std::ios::out);
   if(newfile.is_open()) {
        for(auto& it : _easystore.products()){
            newfile << "["+ it.title() + "] " + "[" + it.description() + "] " + "[" + std::to_string(it.stock()) + "] " + "[" + std::to_string(it.price()) + "]\n";
        }
    }
    newfile.close();
}

void program::Program::getProducts(){
    std::string title="",descp="";
    float price=0.0;
    int i=0,line=1,amount=0;
    std::vector <product::Product> basket;

    std::fstream newfile;
    newfile.open("products.txt",std::ios::in);
    if (newfile.is_open()){ 
        std::string tp;
        while(line <= countLines("products.txt")){

            std::getline(newfile, tp);
            title = getElement(tp,1);
            descp = getElement(tp,2);
            amount = std::stoi(getElement(tp,3));
            price = std::stof(getElement(tp,4));
            _easystore.addProduct(product::Product(title,descp,amount,price));
            line++;
        }
        
        newfile.close();
    }else{
        std::cout<<"\nerror while opening products.txt\n";
    }


}

void program::Program::uploadCommands(){
   std::fstream newfile;
   newfile.open("commands.txt",std::ios::out);
   if(newfile.is_open()) {
        for(auto& it : _easystore.commands()){
            newfile << "["+ it.client().firstName() + "] " + "[" + it.client().lastName() + "] " + "[" + std::to_string(it.basket().size()) + "] " + "[" + ((it.status()==cmd::Status::delivred)?"1":"0") + "]\n";
            for(auto& it2: it.basket()){
                newfile << "["+ it2.title() + "] " + "[" + it2.description() + "] " + "[" + std::to_string(it2.stock()) + "] " + "[" + std::to_string(it2.price()) + "]\n";        
            }
        }
    }
    newfile.close();
}

void program::Program::getCommands(){
    std::string fname="";
    std::string lname="";
    std::string title="",descp="",status="";
    float price=0.0;
    int i=0,line=1,skipline=0,amount=0;
    std::vector <product::Product> basket;
    std::fstream newfile;
    newfile.open("commands.txt",std::ios::in);
    if (newfile.is_open()){ 
        std::string tp;
        while(line <= countLines("commands.txt")){
            std::getline(newfile, tp);
            skipline = line + std::stoi(getElement(tp,3));
            fname = getElement(tp,1);
            lname = getElement(tp,2);
            status= getElement(tp,4);
            line++;
            
            while(line<=skipline){
                std::getline(newfile, tp);
                title = getElement(tp,1);
                descp = getElement(tp,2);
                amount = std::stoi(getElement(tp,3));
                price = std::stof(getElement(tp,4));
                basket.push_back(product::Product(title,descp,amount,price));
                line++;
            }
            _easystore.makeCommand(_easystore.idByName(fname,lname),basket,((status=="1")?cmd::Status::delivred:cmd::Status::not_delivred));
            basket.clear();
        }
        
        newfile.close();
    }else{
        std::cout<<"\nerror while opening commands.txt\n";
    }
}






void program::Program::launch(){

    _easystore.shopName("EasyStore");

    int option = 0;
    bool end = false;
    
    std::cout << "=============================================" << std::endl;
    std::cout << "           welcome to EasyStore              " << std::endl;
    std::cout << "=============================================" << std::endl;

    while(!end){
        std::cout << "how can i help you ?" << std::endl;
        std::cout << "1)  product management" << std::endl; 
        std::cout << "2)  client management" << std::endl;   
        std::cout << "3)  command management" << std::endl;
        std::cout << "4)  quit" << std::endl;        
        
        std::cout << "enter your choice : ";
        std::cin >> option; std::cout << std::endl;

        while((option < 1)||(option>4)){
            std::cout << "please choose again : "<< std::endl;
            std::cin >> option;
        }

        switch (option)
        {
            case 1:
                this->productManagement();
                break;
            case 2:
                this->clientManagement();
                break;
            case 3:
                this->commandManagement();
                break;
            case 4:
                end=true;
                break;
        }

    }
}