CREATE TABLE Consegne(
    ID_univoco INT PRIMARY KEY SERIAL,
    fornitore_ID INT NOT NULL,
    prodotto_ID INT NOT NULL,
    email_cliente VARCHAR(100) NOT NULL,
    città_fornitore VARCHAR(100) NOT NULL,
    indirizzo_fornitore VARCHAR(255) NOT NULL,
    nome_fornitore VARCHAR(100) NOT NULL,
    CAP_cliente  VARCHAR(10) NOT NULL,
    citta_cliente VARCHAR(100) NOT NULL,
    indirizzo_cliente VARCHAR(255) NOT NULL,
);
