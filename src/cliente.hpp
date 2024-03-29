#include "Cryptography.hpp"
#include <iostream>
#include <string>
#include "../lib/redis/redis++/redis++.h"
#include <vector> 
#include "pswd.hpp"
#include <random>

using std::string;
using std::vector;




class Cliente {  

private:
    static int contatore_globale;  // Contatore globale per i clienti
    sw::redis::Redis redis; // Oggetto Redis per comunicare con il server Redis

public:           
    int cliente_ID;       
    string email;
    string telefono;
    string nome;
    string cognome;
    string CAP;
    string citta;
    string indirizzo;
    string password;

//Creo il costuttore
    Cliente(string email, string telefono, string nome, string cognome, string CAP, string citta, string indirizzo, string password) : redis("tcp://127.0.0.1:6379") {
        this->cliente_ID = ++contatore_globale;                                                                                          
        this->email = email;
        this->telefono = telefono;
        this->nome = nome;
        this->cognome = cognome;
        this->CAP = CAP;
        this->citta = citta;
        this->indirizzo = indirizzo;

	    //crittografia per hashare la password
	    Cryptography crypto;
        this->password = crypto.encrypt(password);

        string query = "Clienti:*email:" + email;

        // Verifica se l'email esiste già
        bool exist = redis.exists(query);
        if (exist) {
            std::cout << "Esiste già un cliente con la stessa email, devi usarne un'altra!" << std::endl;
        } else {
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "email:", email);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "telefono:", telefono);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "nome:", nome);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "cognome:", cognome);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "CAP:", CAP);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "citta:", citta);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "indirizzo:", indirizzo);
            redis.hset("Clienti:Clienti" + std::to_string(cliente_ID), "password:", password);
        }
    }


//metodo get_item()

	int get_item(string categoria) {
    
    sw::redis::Redis redis("tcp://127.0.0.1:6379"); 
    
    if (categoria.empty()) { 		// Se la categoria è vuota (cioè non seleziono nessun elemento)
        				// Ottengp tutti i prodotti disponibili nel sistema
        vector<string> keys;
        redis.keys("Prodotti:*", std::back_inserter(keys));
        
        // Stampa i codici univoci dei prodotti disponibili
        std::cout << "Prodotti disponibili nel sistema:" << std::endl;
        for (const auto& key : keys) {
            std::cout << key << std::endl;
        }
    } else {
        // Controlla se la categoria esiste nel database
        if (!redis.exists("Prodotti:*categoria:" + categoria + "*")) {
            // Se la categoria non esiste nel database, restituisci un numero negativo
            std::cout << "La categoria specificata non esiste nel sistema" << std::endl;
        } else {
            // Sela categoria esiste nel database, trova i prodotti corrispondenti
            vector<string> keys;
            redis.keys("Prodotti:*categoria:" + categoria + "*", std::back_inserter(keys));
            
            // Stampa i codici univoci dei prodotti scelti
            std::cout << "Prodotti corrispondenti alla categoria " << categoria << ":" << std::endl;
            for (const auto& key : keys) {
                std::cout << key << std::endl;
            }
            return keys.size(); // Restituisci il numero di prodotti corrispondenti
        }
    }
}



//metodo buy_item()

void buy_item(int number, vector<string> Array_codici, string password) {
    
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a distribution (e.g., uniform distribution between 1 and 100)
    std::uniform_int_distribution<int> distribution(-1, number);

    // Generate a random number
    int numb = distribution(gen);



    if (numb == -1) {   //se il numero generato è -1, vuol dire che non compro nulla
        		//quindi, annulla l'acquisto
        std::cout << "Acquisto annullato" << std::endl;
        return;
    }
    
    
    string value = "Clienti:Clienti" + std::to_string(cliente_ID);
    int flag = check_pswd(value, password);
    // Controllo della password

    if (flag == 0) {    //se la password è divesra da quella memorizzata, annullo
        std::cout << "Password non corretta, acquisto annullato" << std::endl;
        return;
    }else{
    string codice_prodotto = Array_codici[numb]; //acquisto oggetto
    std::cout << "Prodotto acquistato con successo!" << std::endl;   //oggetto acquistato



    // VA DIMINUITA LA QUANTITÀ IN REDIS E SE QUANTITÀ-1 == 0 ALLORA ELIMINA TUTTA LA VOCE
    }


    /* 
                VA
                        MESSO
                                POSTGRESQL
    */

}


};