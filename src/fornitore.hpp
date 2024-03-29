#include "Cryptography.hpp"
#include <iostream>
#include <string>
#include "../lib/redis/redis++/redis++.h"
#include "item.hpp"
#include <vector> 
#include "pswd.hpp"

using std::string;


class Fornitore{  

private:
    static int contatore_globale;  // Contatore globale per i fornitori
    sw::redis::Redis redis; // Oggetto Redis per comunicare con il server Redis

public:           
    int fornitore_ID;       
    string nome;
    string citta;
    string indirizzo;
    string numero_telefono;
    string pswd;

    Fornitore(string nome, string citta, string indirizzo, string numero_telefono, string pswd) : redis("tcp://127.0.0.1:6379") {
        this->fornitore_ID = ++contatore_globale;
        this->nome = nome;
        this->citta = citta;
        this->indirizzo = indirizzo;
        this->numero_telefono = numero_telefono;

        Cryptography crypto;
        this->pswd = crypto.encrypt(pswd);



        string query = "Fornitori:*citta:" + citta + ":indirizzo:" + indirizzo + "*";


        // Verifica se l'indice esiste già
        bool exist = redis.exists(query);
        if (exist) {
            std::cout << "Esiste già un fornitore con lo stesso indirizzo e città, Impossibile crearne nuovi" << std::endl;
        }else {
                    redis.hset("Fornitori:Fornitori" + std::to_string(fornitore_ID), "nome:", nome);
                    redis.hset("Fornitori:Fornitori" + std::to_string(fornitore_ID), "citta:", citta);
                    redis.hset("Fornitori:Fornitori" + std::to_string(fornitore_ID), "indirizzo:", indirizzo);
                    redis.hset("Fornitori:Fornitori" + std::to_string(fornitore_ID), "numero_telefono:", numero_telefono);
                    redis.hset("Fornitori:Fornitori" + std::to_string(fornitore_ID), "pswd:", pswd);
    }
};
/*      LA STRUTTURA È QUESTA IN TEORIA 
    "Fornitori:Fornitori1" => {
    "nome:" => "valore_del_nome",
    "citta:" => "valore_della_città",
    "indirizzo:" => "valore_dell_indirizzo",
    "numero_telefono:" => "valore_del_numero_di_telefono",
    "pswd:" => "valore_della_password"
}
*/

    void setItem(Item oggetto, string password){
        string value = "Fornitori:Fornitori" + std::to_string(fornitore_ID);
        int flag = check_pswd(value, password);

        if (flag == 0) {    //se la password è diversa da quella memorizzata, annullo
        std::cout << "Password non corretta, Messa in vendita annullata" << std::endl;
        return;
    }else{

            /* 
                VA
                        MESSO
                                POSTGRESQL
    */

        


     };
    }


};

int Fornitore::contatore_globale = 0;