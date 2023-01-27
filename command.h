#pragma once
#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include <vector>
#include <string>

#include "client.h"
#include "product.h"

namespace cmd{

    enum class Status{
        delivred,
        not_delivred
    };

    class Command{
        public:
            Command(client::Client client=client::Client());

            client::Client client() const;
            std::vector <product::Product> basket() const;
            Status status() const;
            float totalPrice() const;
            std::string id() const;
            std::string basketList() const;

            void status(Status status);

       private:
            std::string _id;
            client::Client _client;
            std::vector <product::Product> _cbasket;
            Status _status;

    };
    int generatecmdId();
    std::ostream& operator<<(std::ostream& os,const Command cmd);
}


#endif