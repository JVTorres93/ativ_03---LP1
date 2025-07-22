#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>

class Corretor {
private:
    std::string id;
    std::string nome;
    std::string telefone;
    bool avaliador;
    double lat;
    double lng;

    static int proximoIdCorretor;

public:
    // Construtor
    Corretor(std::string nome, std::string telefone, bool avaliador, double lat, double lng);

    //Getters
    std::string getId() const;
    std::string getNome() const;
    std::string getTelefone() const;
    bool isAvaliador() const; 
    double getLat() const;
    double getLng() const;
};

#endif 
