#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <sstream>
#include <iomanip>

class Cliente {
private:
    std::string id;
    std::string nome;
    std::string telefone;

    static int proximoIdCliente;

public:
    // Construtor
    Cliente(std::string nome, std::string telefone);

    //Getters
    std::string getId() const;
    std::string getNome() const;
    std::string getTelefone() const;
};

#endif
