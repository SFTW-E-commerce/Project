CREATE TABLE Prodotti (
    prodotto_ID INT PRIMARY KEY SERIAL,
    nome VARCHAR(100) NOT NULL,
    quantita INT NOT NULL,
    prezzo FLOAT NOT NULL,
    categoria VARCHAR(10) NOT NULL,
    fornitore_ID INT NOT NULL,
    nome_fornitore VARCHAR(100) NOT NULL,
    citta VARCHAR(100) NOT NULL,
    indirizzo VARCHAR(255) NOT NULL,
);
