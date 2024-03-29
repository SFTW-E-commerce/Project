#include <iostream>
#include "../lib/postgresql/libpq-fe.h" // Includi il file delle intestazioni di libpq

int connection_postgre() {
    // Connessione al database
    PGconn *conn = PQconnectdb("dbname=ecommerce user=postgres password=05/02/2002");

    // Verifica se la connessione è avvenuta con successo
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connessione al database fallita: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn); // Chiudi la connessione
        return 1;
    }

    // Connessione riuscita
    std::cout << "Connessione al database postgre avvenuta con successo!" << std::endl;
    // Esegui query o altre operazioni qui

    // Chiudi la connessione prima di uscire dal programma
    PQfinish(conn);

    return 0;
}
