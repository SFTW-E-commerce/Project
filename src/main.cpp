#include <iostream>
#include "Header.hpp"
#include "fornitore.hpp"

int main() {
    connection_red();
    connection_postgre();

    Fornitore Fornitore("Alessio", "Roma", "Via ", "333", "1234");

    return 0;
}
