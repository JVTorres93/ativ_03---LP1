#include "Imovel.h"
int Imovel::proximoIdImovel = 1;

// construtor
Imovel::Imovel(TipoImovel tipo, std::string proprietarioId,
               double lat, double lng, std::string endereco, double preco)
    : tipo(tipo),
      proprietarioId(proprietarioId),
      lat(lat),
      lng(lng),
      endereco(endereco),
      preco(preco) {
    std::stringstream ss;
    ss << "IMO" << std::setw(3) << std::setfill('0') << proximoIdImovel++;
    this->id = ss.str();
}

// Getters
std::string Imovel::getId() const {
    return id;
}

TipoImovel Imovel::getTipo() const {
    return tipo;
}

std::string Imovel::getProprietarioId() const {
    return proprietarioId;
}

double Imovel::getLat() const {
    return lat;
}

double Imovel::getLng() const {
    return lng;
}

std::string Imovel::getEndereco() const {
    return endereco;
}

double Imovel::getPreco() const {
    return preco;
}
