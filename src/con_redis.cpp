#include <iostream>
#include "../lib/redis/redis++/redis++.h"

using namespace sw::redis;

int connection_red() {
    
    try {
        // Connessione all'istanza di Redis
        auto redis = Redis("tcp://127.0.0.1:6379");
        std::cout << "Connessione a redis riuscita!" << std::endl;
     
    } catch(const std::exception& e) {
        std::cerr << "Errore durante la connessione a Redis: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
