#include "Cryptography.hpp"
#include <iostream>
#include <string>
#include "../lib/redis/redis++/redis++.h"
#include <vector>


sw::redis::Redis redis("tcp://127.0.0.1:6379");

using std::string;

int check_pswd(string ruolo, string pswd){

    string chiave = "Fornitori:" + ruolo;
    // Nome dell'attributo
    std::string attributo = "pswd";


    sw::redis::OptionalString valore = redis.hget(chiave, attributo);
    string value = valore.value();

    Cryptography crypto;

    string pswd_cryptata = crypto.encrypt(pswd);

    if (pswd_cryptata == value){
        return 1;
    }else{
        return 0;
    }

}