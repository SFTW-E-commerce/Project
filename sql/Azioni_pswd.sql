CREATE TABLE Azioni_pswd(
    ID_univoco INT PRIMARY KEY SERIAL,
    azione VARCHAR(255) NOT NULL,
    ID_ruolo INT NOT NULL,
    ruolo VARCHAR(100) NOT NULL,
    pswd_inserita VARCHAR(100) NOT NULL,
    pswd_corretta VARCHAR(100) NOT NULL,
);