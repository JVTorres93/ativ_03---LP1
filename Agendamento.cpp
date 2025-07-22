#include "Agendamento.h"

int Agendamento::proximoIdAgendamento = 1;

//construtor
Agendamento::Agendamento(const Imovel* imovel, const Cliente* cliente, const Corretor* corretor,
                         DataHora dataHora, std::string status)
    : imovel(imovel),
      cliente(cliente),
      corretor(corretor),
      dataHora(dataHora),
      status(status) {
    std::stringstream ss;
    ss << "AGE" << std::setw(3) << std::setfill('0') << proximoIdAgendamento++;
    this->id = ss.str();
}

// Getters
std::string Agendamento::getId() const {
    return id;
}

const Imovel* Agendamento::getImovel() const {
    return imovel;
}

const Cliente* Agendamento::getCliente() const {
    return cliente;
}

const Corretor* Agendamento::getCorretor() const {
    return corretor;
}

DataHora Agendamento::getDataHora() const {
    return dataHora;
}

std::string Agendamento::getStatus() const {
    return status;
}

//Setter
void Agendamento::setStatus(std::string novoStatus) {
    this->status = novoStatus;
}
