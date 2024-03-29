CREATE TABLE Azioni_Tempo(
    ID_univoco INT PRIMARY KEY SERIAL,
    azione VARCHAR(255) NOT NULL,
    ID_ruolo INT NOT NULL,
    ruolo VARCHAR(100) NOT NULL,
    prodotto_ID INT NOT NULL,
    nome_prodotto VARCHAR(100) NOT NULL,
    tempo FLOAT NOT NULL,
);