#include "Cryptography.hpp"
#include <iostream>
#include <string>
#include "../lib/redis/redis++/redis++.h"
#include <vector> 
#include "pswd.hpp"

using std::string;
using std::vector;

class Trasportatore {  
private:
    static int contatore_globale;  // Contatore globale per i trasportatori
    sw::redis::Redis redis; // Oggetto Redis per comunicare con il server Redis

public:           
    int trasportatore_ID;       
    int stato; // Disponibile alla consegna (0) | Occupato per la consegna (1)
    string password;

    // Costruttore
    Trasportatore(string password) : redis("tcp://127.0.0.1") { //sempre stessa porta
        this->trasportatore_ID = ++contatore_globale;                                                                                      
        this->stato = 0; // Inizialmente disponibile

	//hash passsword
        Cryptography crypto;
        this->password = crypto.encrypt(password);

        // Salvo i dettagli del trasportatore in Redis
        redis.hset("Trasportatori:Trasportatori" + std::to_string(trasportatore_ID), "stato:", std::to_string(stato));
        redis.hset("Trasportatori:Trasportatori" + std::to_string(trasportatore_ID), "password:", password);
    }


    // Metodo per accettare una consegna
    void take_delivery(string password) {
        string value = "Clienti" + std::to_string(trasportatore_ID);
        int flag = check_pswd(value, password);

        if (flag == 0) { // Controllo della password (COME PER CLIENTE!!!!!!!!!!!!)
            std::cout << "Password non corretta, impossibile accettare la consegna" << std::endl;
            return;
        }else{
        // Controllo se ci sono consegne in coda
        if (redis.exists("Consegne:Coda")) {
            // Prendi la prima consegna disponibile dalla coda
            sw::redis::OptionalString valore  = redis.lpop("Consegne:Coda");
            string codice_consegna = valore.value();


            // Aggiorna lo stato del trasportatore
            redis.hset("Trasportatori:Trasportatori" + std::to_string(trasportatore_ID), "stato:", "1"); // Occupato per la consegna

            // Aggiorna lo stato della consegna nel database
            redis.hset("Consegne:Consegne" + codice_consegna, "stato:", "in consegna");
            

            std::cout << "Consegna " << codice_consegna << " accettata con successo!" << std::endl;
        } else {
            std::cout << "Nessuna consegna disponibile al momento" << std::endl;
        }
     }



         /* 
                VA
                        MESSO
                                POSTGRESQL
    */


    }


    // Metodo per completare la consegna di un prodotto
void execute_delivery(string password) {
    string value = "Trasportatori:Trasportatori" + std::to_string(trasportatore_ID);
    int flag = check_pswd(value, password);

    // Controllo della password
    if (flag == 0) { 
        std::cout << "Password non corretta, impossibile completare la consegna" << std::endl;
        return;
    }else{

    // Controllo se ci sono consegne in corso
    if (redis.exists("Consegne:In corso")) {
        // Prendi la prima consegna in corso
        
        sw::redis::OptionalString valore  = redis.lpop("Consegne:In corso");
        string codice_consegna = valore.value();
        
        // Aggiormo lo stato del trasportatore
        redis.hset("Trasportatori:Trasportatori" + std::to_string(trasportatore_ID), "stato:", "0"); // Disponibile alla consegna
        
        // Aggiorno lo stato dellaconsegna nel database
        redis.hset("Consegne:Consegne" + codice_consegna, "stato:", "consegnato");
        
        

        std::cout << "Consegna " << codice_consegna << " completata con successo!" << std::endl;
    } else {
        std::cout << "Nessuna consegna in corso al momento" << std::endl;
    }
    }
}

    /* 
                VA
                        MESSO
                                POSTGRESQL
    */

};

