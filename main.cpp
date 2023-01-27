#include <iostream>
#include "product.h"
#include "client.h"
#include "command.h"
#include "shop.h"
#include "program.h"

int main(){

    program::Program prog;

    prog.getClients();
    prog.getProducts();
    prog.getCommands();
    
    prog.launch();
    

    prog.uploadClients();
    prog.uploadProducts();
    prog.uploadCommands();


    return 0;
}