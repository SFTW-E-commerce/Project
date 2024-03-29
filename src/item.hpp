#include <string>
#include <map>


using std::string;
using std::map;

// Definizione del tipo per il dizionario categorie
map<string, string> dizionarioCategorie = {
    {"Smartphone", "A1"},
    {"Elettrodomestico", "B4"},
    {"Abbigliamento", "C7"},
    {"Libri", "D3"},
    {"Accessori Auto", "E2"},
    {"Sport e Tempo Libero", "F5"},
    {"Giochi e Videogiochi", "G8"},
    {"Alimentari", "H9"},
    {"Fai da Te", "I6"},
    {"Bellezza e Cura Personale", "J0"},
    {"Elettronica", "K2"},
    {"Arredamento", "L4"},
    {"Musica e Film", "M7"},
    {"Giardino e Giardinaggio", "N1"},
    {"Articoli per Animali", "O3"},
    {"Strumenti Musicali", "P6"},
    {"Articoli per Ufficio", "Q8"},
    {"Viaggi e Vacanze", "R5"},
    {"Hobby Creativi", "S9"},
    {"Articoli per Bambini", "T0"},
    {"Articoli per la Casa", "U2"},
    {"Abbigliamento Sportivo", "V4"},
    {"Borse e Valigie", "W7"},
    {"Articoli per la Scuola", "X9"},
    {"Orologi", "Y1"},
    {"Attrezzature Sportive", "Z3"},
    {"Prodotti per la Salute", "AA6"},
    {"Prodotti per la Cucina", "BB8"},
    {"Prodotti per la Sicurezza", "CC2"},
    {"Articoli per Feste ed Eventi", "DD4"},
    {"Prodotti per l'Infanzia", "EE7"},
};


class Item{  
private: 
    static int contatore_globale;

public:                 
    string nome;
	static int codice_univoco;
	string categoria;
	string codice_categoria;
	float prezzo;

    Item(string nome, string categoria, float prezzo){
        this->nome = nome;
        this->codice_univoco = ++contatore_globale;
        this->categoria = categoria;
        this->prezzo = prezzo;
        this->codice_categoria= dizionarioCategorie[categoria];
    }


};

int Item::contatore_globale = 0;