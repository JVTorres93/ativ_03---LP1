#include "Cliente.h"
int Cliente::proximoIdCliente = 1;

//construtor
Cliente::Cliente(std::string nome, std::string telefone)
    : nome(nome), telefone(telefone) {
    std::stringstream ss;
    ss << "CLI" << std::setw(3) << std::setfill('0') << proximoIdCliente++;
    this->id = ss.str();
}

//Getters
std::string Cliente::getId() const {
    return id;
}

std::string Cliente::getNome() const {
    return nome;
}

std::string Cliente::getTelefone() const {
    return telefone;
}
