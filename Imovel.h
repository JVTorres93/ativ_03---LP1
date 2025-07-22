#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>
#include <sstream>
#include <iomanip>

enum class TipoImovel {
    CASA,
    APARTAMENTO,
    TERRENO
};

class Imovel {
private:
    std::string id;
    TipoImovel tipo;
    std::string proprietarioId;
    double lat;
    double lng;
    std::string endereco;
    double preco;

    static int proximoIdImovel;

public:
    // Construtor
    Imovel(TipoImovel tipo, std::string proprietarioId,
           double lat, double lng, std::string endereco, double preco);

    //Getters
    std::string getId() const;
    TipoImovel getTipo() const;
    std::string getProprietarioId() const;
    double getLat() const;
    double getLng() const;
    std::string getEndereco() const;
    double getPreco() const;
};

#endif