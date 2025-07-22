#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>  
#include <iomanip> 
#include <algorithm> 
#include <cmath>   
#include <map>  

#include "Imovel.h"
#include "Corretor.h"
#include "Cliente.h"
#include "Agendamento.h"

constexpr double EARTH_R = 6371.0;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double haversine(double lat1, double lon1, double lat2, double lon2);
TipoImovel stringToTipoImovel(const std::string& tipoStr);
DataHora adicionarMinutos(DataHora dh, int minutosParaAdicionar);

int main() {
    std::vector<Corretor> corretores;
    std::vector<Cliente> clientes;
    std::vector<Imovel> imoveis;
    std::vector<Agendamento> agendamentos;

    //Entrada
    // 1. Leitura de Corretores
    int numCorretores;
    std::cin >> numCorretores;
    for (int i = 0; i < numCorretores; ++i) {
        std::string telefone;
        int avaliadorInt;
        double lat, lng;
        std::string nome;

        std::cin >> telefone >> avaliadorInt >> lat >> lng;
        std::getline(std::cin >> std::ws, nome);

        bool avaliador = (avaliadorInt == 1);
        corretores.push_back(Corretor(nome, telefone, avaliador, lat, lng));
    }

    // 2. Leitura de Clientes
    int numClientes;
    std::cin >> numClientes;
    for (int i = 0; i < numClientes; ++i) {
        std::string telefone;
        std::string nome;

        std::cin >> telefone;
        std::getline(std::cin >> std::ws, nome);

        clientes.push_back(Cliente(nome, telefone));
    }

    // 3. Leitura de Imóveis
    int numImoveis;
    std::cin >> numImoveis;
    for (int i = 0; i < numImoveis; ++i) {
        std::string tipoStr;
        std::string proprietarioId;
        double lat, lng, preco;
        std::string endereco;

        std::cin >> tipoStr >> proprietarioId >> lat >> lng >> preco;
        std::getline(std::cin >> std::ws, endereco);

        TipoImovel tipo = stringToTipoImovel(tipoStr);
        imoveis.push_back(Imovel(tipo, proprietarioId, lat, lng, endereco, preco));
    }

    //Agendamento (Round-Robin)

    //Ordena imóveis por ID.
    std::sort(imoveis.begin(), imoveis.end(), [](const Imovel& a, const Imovel& b) {
        return a.getId() < b.getId();
    });

    //Filtro corretores/avaliadores
    std::vector<const Corretor*> avaliadores;
    for (const auto& corretor : corretores) {
        if (corretor.isAvaliador()) {
            avaliadores.push_back(&corretor);
        }
    }

    // Mapeamento
    std::map<std::string, std::vector<const Imovel*>> imoveisPorAvaliador;
    for (const auto* avaliador : avaliadores) {
        imoveisPorAvaliador[avaliador->getId()] = std::vector<const Imovel*>();
    }

    // Atribuição de imóveis
    int avaliadorIdx = 0;
    for (const auto& imovel : imoveis) {
        imoveisPorAvaliador[avaliadores[avaliadorIdx]->getId()].push_back(&imovel);
        avaliadorIdx = (avaliadorIdx + 1) % avaliadores.size();
    }

    //Ordena a Rota (Vizinho Mais Próximo)
    for (const auto* avaliador : avaliadores) {
        std::vector<const Imovel*> imoveisAtribuidos = imoveisPorAvaliador[avaliador->getId()];
        if (imoveisAtribuidos.empty()) {
            continue; 
        }

        std::vector<const Imovel*> imoveisNaoVisitados = imoveisAtribuidos;
        
        DataHora relogioAtual = {2025, 7, 25, 9, 0}; 
        double currentLat = avaliador->getLat();
        double currentLng = avaliador->getLng();

        const Cliente* clienteParaAgendamento = &clientes[0];

        while (!imoveisNaoVisitados.empty()) {
            const Imovel* proximoImovel = nullptr;
            double menorDistancia = -1.0;

            for (const auto* imovelNaoVisitado : imoveisNaoVisitados) {
                double distancia = haversine(currentLat, currentLng,
                                             imovelNaoVisitado->getLat(), imovelNaoVisitado->getLng());

                if (proximoImovel == nullptr || distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximoImovel = imovelNaoVisitado;
                }
            }

            //Deslocamento
            int tempoDeslocamentoMin = static_cast<int>(menorDistancia * 2); 
            relogioAtual = adicionarMinutos(relogioAtual, tempoDeslocamentoMin);

            agendamentos.push_back(Agendamento(proximoImovel, clienteParaAgendamento, avaliador, relogioAtual, "Confirmado"));
            relogioAtual = adicionarMinutos(relogioAtual, 60); 

            currentLat = proximoImovel->getLat();
            currentLng = proximoImovel->getLng();

            imoveisNaoVisitados.erase(std::remove(imoveisNaoVisitados.begin(), imoveisNaoVisitados.end(), proximoImovel), imoveisNaoVisitados.end());
        }
    }

    //Saída

    //Ordena agendamentos
    std::sort(agendamentos.begin(), agendamentos.end(), [](const Agendamento& a, const Agendamento& b) {
        if (a.getCorretor()->getId() != b.getCorretor()->getId()) {
            return a.getCorretor()->getId() < b.getCorretor()->getId();
        }
        if (a.getDataHora().hora != b.getDataHora().hora) {
            return a.getDataHora().hora < b.getDataHora().hora;
        }
        return a.getDataHora().minuto < b.getDataHora().minuto;
    });

    std::string currentCorretorId = "";
    bool firstCorretorBlock = true;

    for (const auto& agendamento : agendamentos) {
        if (agendamento.getCorretor()->getId() != currentCorretorId) {
            if (!firstCorretorBlock) {
                std::cout << std::endl;
            }
            // Imprime "Corretor [ID]"
            std::cout << "Corretor " << std::stoi(agendamento.getCorretor()->getId().substr(3)) << std::endl;
            currentCorretorId = agendamento.getCorretor()->getId();
            firstCorretorBlock = false;
        }

        // Imprime "[HH:MM] Imóvel [ID]"
        std::cout << std::setfill('0') << std::setw(2) << agendamento.getDataHora().hora << ":"
                  << std::setw(2) << agendamento.getDataHora().minuto << " Imóvel "
                  << std::stoi(agendamento.getImovel()->getId().substr(3)) << std::endl;
    }

    return 0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);
    double a = std::pow(std::sin(dlat/2), 2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::pow(std::sin(dlon/2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_R * c;
}

TipoImovel stringToTipoImovel(const std::string& tipoStr) {
    if (tipoStr == "Casa") {
        return TipoImovel::CASA;
    } else if (tipoStr == "Apartamento") {
        return TipoImovel::APARTAMENTO;
    } else if (tipoStr == "Terreno") {
        return TipoImovel::TERRENO;
    }
    return TipoImovel::CASA; 
}

DataHora adicionarMinutos(DataHora dh, int minutosParaAdicionar) {
    dh.minuto += minutosParaAdicionar;
    dh.hora += dh.minuto / 60;
    dh.minuto %= 60;
    return dh;
}