#ifndef CRYPTOGRAPHY_HPP
#define CRYPTOGRAPHY_HPP

#include <iostream>
#include <string>

class Cryptography {
private:
    std::string salt = "aB3!pQz9";
    
public:
    Cryptography() {};

    std::string encrypt(std::string plaintext) {
        std::string ciphertext = "";
        int saltIndex = 0;

        for (char& c : plaintext) {
            if (isalpha(c)) {
                int shift = salt[saltIndex % salt.length()] - 'a'; // calcola lo spostamento basato sul carattere del salt
                char base = isupper(c) ? 'A' : 'a'; // determina se il carattere è maiuscolo o minuscolo
                ciphertext += static_cast<char>((c - base + shift) % 26 + base); // applica lo spostamento
                saltIndex++;
            } else {
                ciphertext += c; // mantiene i caratteri speciali invariati
            }
        }

        return ciphertext;
    }

    std::string decrypt(std::string ciphertext) {
        std::string plaintext = "";
        int saltIndex = 0;

        for (char& c : ciphertext) {
            if (isalpha(c)) {
                int shift = salt[saltIndex % salt.length()] - 'a'; // calcola lo spostamento basato sul carattere del salt
                char base = isupper(c) ? 'A' : 'a'; // determina se il carattere è maiuscolo o minuscolo
                int decrypted_char = (c - base - shift + 26) % 26; // calcola il carattere decifrato
                plaintext += static_cast<char>(decrypted_char + base); // aggiunge il carattere decifrato
                saltIndex++;
            } else {
                plaintext += c; // mantiene i caratteri speciali invariati
            }
        }

        return plaintext;
    }
};

#endif // CRYPTOGRAPHY_HPP
