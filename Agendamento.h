#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <string> 
#include <sstream> 
#include <iomanip> 
#include "Imovel.h" 
#include "Cliente.h"
#include "Corretor.h"

struct DataHora {
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
};

class Agendamento {
private:
    std::string id;
    const Imovel* imovel;
    const Cliente* cliente;
    const Corretor* corretor;
    DataHora dataHora;
    std::string status;

    static int proximoIdAgendamento;

public:
    // Construtor
    Agendamento(const Imovel* imovel, const Cliente* cliente, const Corretor* corretor,
                DataHora dataHora, std::string status);

    //Getters
    std::string getId() const;
    const Imovel* getImovel() const;
    const Cliente* getCliente() const;
    const Corretor* getCorretor() const;
    DataHora getDataHora() const;
    std::string getStatus() const;

    //Setters
    void setStatus(std::string novoStatus);
};

#endif 
