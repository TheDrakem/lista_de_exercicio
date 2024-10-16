#include <bits/stdc++.h>

using namespace std;

struct Evento {
    string nome;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;

};

void printar(vector<Evento> &eventos) {
    for (const auto& evento : eventos) {
        cout << evento.nome << ": "
             << evento.dia << "/" << evento.mes << "/" << evento.ano
             << ", " << evento.hora << ":" << (evento.minuto < 10 ? "0" : "") << evento.minuto << " h" << endl;
    }
}
 int main() {
    vector<Evento> eventos = {
        {"Olha! Recife a Pe - Recife Walking Tour", 4, 10, 2024, 9, 30},
        {"Olha! Recife a Pe - Recife Walking Tour", 27, 9, 2024, 9, 30},
        {"Olha! Recife no Rio - Ilha de Deus", 28, 9, 2024, 9, 0},
        {"Olha! Recife de Onibus - Jardim Botanico", 28, 9, 2024, 9, 0},
        {"Olha! Recife de Onibus - Fundacao Gilberto Freyre", 29, 9, 2024, 13, 0},
        {"Olha! Recife a Pe - Patio do Terco e Arredores", 2, 10, 2024, 14, 0},
        {"Olha! Recife de Onibus - Instituto Ricardo Brennand", 28, 9, 2024, 14, 0},
        {"Olha! Recife Pedalando - Antigos Cinemas do Recife", 29, 9, 2024, 9, 0},
        {"Olha! Recife a Pe - Recife Walking Tour", 27, 9, 2024, 9, 30}
    };


    printar(eventos);
    return 0;
}