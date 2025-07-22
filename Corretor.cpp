#include "Corretor.h"
#include <iomanip>
#include <sstream>

int Corretor::proximoIdCorretor = 1;

//construtor
Corretor::Corretor(std::string nome, std::string telefone, bool avaliador, double lat, double lng)
    : nome(nome), telefone(telefone), avaliador(avaliador), lat(lat), lng(lng) {
    std::stringstream ss;
    ss << "COR" << std::setw(3) << std::setfill('0') << proximoIdCorretor++;
    this->id = ss.str();
}

//Getters
std::string Corretor::getId() const {
    return id;
}

std::string Corretor::getNome() const {
    return nome;
}

std::string Corretor::getTelefone() const {
    return telefone;
}

bool Corretor::isAvaliador() const {
    return avaliador;
}

double Corretor::getLat() const {
    return lat;
}

double Corretor::getLng() const {
    return lng;
}
