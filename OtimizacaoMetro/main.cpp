#include <bits/stdc++.h>
#define mapa unordered_map
using namespace std;

class Grafo {
private:
    const int n_vertices;
    int n_arestas;
    vector<bool> marcado;
    vector<mapa<int, int>> lista_adj;
    mapa<string, int> estacao_para_numero = {
        {"Recife", 0},
        {"Joana Bezerra", 1},
        {"Afogados", 2},
        {"Ipiranga", 3},
        {"Mangueira", 4},
        {"Santa Luzia", 5},
        {"Werneck", 6},
        {"Barro", 7},
        {"Tejipio", 8},
        {"Coqueiral", 9},
        {"Alto do Ceu", 10},
        {"Curado", 11},
        {"Rodoviaria", 12},
        {"Cosme e Damiao", 13},
        {"Camaragibe", 14},
        {"Cavaleiro", 15},
        {"Floriano", 16},
        {"Engenho Velho", 17},
        {"Jaboatao", 18},
        {"Largo da Paz", 19},
        {"Imbiribeira", 20},
        {"Antonio Falcao", 21},
        {"Shopping", 22},
        {"Tancredo Neves", 23},
        {"Aeroporto", 24},
        {"Porta Larga", 25},
        {"Monte dos Guararapes", 26},
        {"Prazeres", 27},
        {"Cajueiro Seco", 28}
    };

    vector<string> numero_para_estacao = {
        "Recife",
        "Joana Bezerra",
        "Afogados",
        "Ipiranga",
        "Mangueira",
        "Santa Luzia",
        "Werneck",
        "Barro",
        "Tejipio",
        "Coqueiral",
        "Alto do Ceu",
        "Curado",
        "Rodoviaria",
        "Cosme e Damiao",
        "Camaragibe",
        "Cavaleiro",
        "Floriano",
        "Engenho Velho",
        "Jaboatao",
        "Largo da Paz",
        "Imbiribeira",
        "Antonio Falcao",
        "Shopping",
        "Tancredo Neves",
        "Aeroporto",
        "Porta Larga",
        "Monte dos Guararapes",
        "Prazeres",
        "Cajueiro Seco"
    };
    void dfs_recursivo(int atual, int fim, stack<string>& caminho) {
        marcado[atual] = true;
        caminho.push(numero_para_estacao[atual]);
        for (auto [vertice, tempo]: lista_adj[atual]) {
            if(marcado[fim] == true) {
                return;
            }
            if(marcado[vertice] == false) {
                dfs_recursivo(vertice, fim, caminho);
            }
        }
        if(marcado[fim] == false) {
            caminho.pop();
        }
    }

    stack<string> dfs(string inicio, string fim) {
        marcado.assign(n_vertices, false);
        stack<string> caminho;
        dfs_recursivo(estacao_para_numero[inicio],estacao_para_numero[fim], caminho);
        return caminho;
    }

    struct aresta {
        int inicio;
        int fim;
        int tempo;

        bool operator < (const aresta& outra) const {
            return tempo > outra.tempo;
        }
    };

public:
    Grafo(int x) : n_vertices(x) {
        n_arestas = 0;
        marcado.assign(x, false);
        for (int i = 0; i < x; ++i) {
            mapa<int, int> mapa_vazia;
            lista_adj.push_back(mapa_vazia);
        }
    }

    void add_aresta(string v1,string v2, int peso) {
        lista_adj[estacao_para_numero[v1]][estacao_para_numero[v2]] = peso;
    }

    void remover_aresta(string v1,string v2) {
        lista_adj[estacao_para_numero[v1]].erase(estacao_para_numero[v2]);
    }

    void printar() {
        for (int i = 0; i < n_vertices; ++i) {
            cout << numero_para_estacao[i] <<": [" ;
            for (auto [vertice, tempo]: lista_adj[i]) {
                cout << " (" << numero_para_estacao[vertice] << ", " << tempo << " min)";
            }
            cout <<" ]" << endl;
        }
    }

    void printar_dfs (string inicio, string fim) {
        stack<string> caminho = dfs(inicio, fim);
        vector<string> vetor_caminho(caminho.size());
        int tamanho = caminho.size();
        int total = 0;

        for (int i = (tamanho - 1); i >= 0; --i) {
            vetor_caminho[i] = caminho.top();
            caminho.pop();
        }

        for (int i = 0; i < (tamanho - 1); ++i) {
            int v1 = estacao_para_numero[vetor_caminho[i]];
            int v2 = estacao_para_numero[vetor_caminho[i+1]];
            cout << vetor_caminho[i] << " -> " << vetor_caminho[i+1] << " = " << lista_adj[v1][v2] << " min" << endl;
            total += lista_adj[v1][v2];
        }

        if(tamanho == 0) {
            cout << "Caminho nao encontrado!!!" << endl;
        }
        else {
            cout << "Total = " << total << " min" << endl;
        }
    }

     void printar_bfs(string Sinicio, string Sfim) {
        marcado.assign(n_vertices, false);
        int inicio = estacao_para_numero[Sinicio];
        int fim = estacao_para_numero[Sfim];
        queue<int> fila;
        vector<int> pai(n_vertices, -1);
        fila.push(inicio);
        marcado[inicio] = true;

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            for (auto [vertice, tempo]: lista_adj[atual]) {
                if(marcado[vertice] == false) {
                    marcado[vertice] = true;
                    fila.push(vertice);
                    pai[vertice] = atual;
                }
            }
        }
        int vertice_atual = fim;
        vector<int> caminho;
        while (vertice_atual != -1) {
            caminho.push_back(vertice_atual);
            vertice_atual =pai[vertice_atual];
        }
        int tamanho = caminho.size();
        int total = 0;
        for (int i = (tamanho - 1); i > 0; --i) {
            string v1 = numero_para_estacao[caminho[i]];
            string v2 = numero_para_estacao[caminho[i-1]];
            cout << v1 << " -> " << v2 << " = " << lista_adj[caminho[i]][caminho[i-1]] <<  " min" << endl;
            total += lista_adj[caminho[i]][caminho[i-1]];
        }

        if(tamanho == 0) {
            cout << "Caminho nao encontrado!!!" << endl;
        }
        else {
            cout << "Total = " << total << " min" << endl;
        }
    }

    void printar_dijkstra(string Sinicio, string Sfim) {
        marcado.assign(n_vertices, false);
        int inicio = estacao_para_numero[Sinicio];
        int fim = estacao_para_numero[Sfim];
        vector<int> pai(n_vertices, -1);
        vector<int> distancia(n_vertices, INT_MAX);

        priority_queue<aresta> fila_arestas;
        fila_arestas.push({inicio, inicio, 0});
        distancia[inicio] = 0;
        int atual_vertice;
        int proximo_vertice;
        int tempo;
        for (int i = 0; i < n_vertices; ++i) {
            do {
                if (fila_arestas.empty()) {
                    goto sair_for;
                }
                aresta menor_aresta = fila_arestas.top();
                fila_arestas.pop();
                atual_vertice = menor_aresta.inicio;
                proximo_vertice = menor_aresta.fim;
                tempo = menor_aresta.tempo;

            } while (marcado[proximo_vertice] == true);
            marcado[proximo_vertice] = true;
            pai[proximo_vertice] = atual_vertice;

            for (auto [vertice, peso]: lista_adj[proximo_vertice]) {
                if(marcado[vertice] == false && peso + distancia[proximo_vertice] < distancia[vertice]) {
                    distancia[vertice] = peso + distancia[proximo_vertice];
                    fila_arestas.push({proximo_vertice, vertice, distancia[vertice]});
                }
            }
        }
        sair_for:

        int vertice_atual = fim;

        vector<int> caminho;

        while (vertice_atual != inicio) {
            caminho.push_back(vertice_atual);
            vertice_atual =pai[vertice_atual];
        }

        caminho.push_back(inicio);

        int tamanho = caminho.size();

        for (int i = (tamanho - 1); i > 0; --i) {
            string v1 = numero_para_estacao[caminho[i]];
            string v2 = numero_para_estacao[caminho[i-1]];
            cout << v1 << " -> " << v2 << " = " << lista_adj[caminho[i]][caminho[i-1]] <<  " min" << endl;
        }

        if(tamanho == 0) {
            cout << "Caminho nao encontrado!!!" << endl;
        }
        else {
            cout << "Total = " << distancia[fim] << " min" << endl;
        }
    }

    void possiveis_dijkstra(string Sinicio) {
        marcado.assign(n_vertices, false);
        int inicio = estacao_para_numero[Sinicio];
        vector<int> pai(n_vertices, -1);
        vector<int> distancia(n_vertices, INT_MAX);

        priority_queue<aresta> fila_arestas;
        fila_arestas.push({inicio, inicio, 0});
        distancia[inicio] = 0;
        int atual_vertice;
        int proximo_vertice;
        int tempo;
        for (int i = 0; i < n_vertices; ++i) {
            do {
                if (fila_arestas.empty()) {
                    goto sair_for;
                }
                aresta menor_aresta = fila_arestas.top();
                fila_arestas.pop();
                atual_vertice = menor_aresta.inicio;
                proximo_vertice = menor_aresta.fim;
                tempo = menor_aresta.tempo;

            } while (marcado[proximo_vertice] == true);
            marcado[proximo_vertice] = true;
            pai[proximo_vertice] = atual_vertice;

            for (auto [vertice, peso]: lista_adj[proximo_vertice]) {
                if(marcado[vertice] == false && peso + distancia[proximo_vertice] < distancia[vertice]) {
                    distancia[vertice] = peso + distancia[proximo_vertice];
                    fila_arestas.push({proximo_vertice, vertice, distancia[vertice]});
                }
            }
        }
        sair_for:

        cout << "distancia de " << Sinicio << " ate: \n";
        for (int i = 0; i < n_vertices; ++i) {
            cout << numero_para_estacao[i] << " = " << distancia[i] << endl;
        }
    }
};

int main() {
    Grafo metro_recife (29);

    //Ligações entre as estacões do metro de Recife baseado no site  https://www.metrorecife.com.br/
        metro_recife.add_aresta("Recife", "Joana Bezerra", 5);
        metro_recife.add_aresta("Joana Bezerra", "Recife", 5);
        metro_recife.add_aresta("Joana Bezerra", "Afogados", 6);
        metro_recife.add_aresta("Joana Bezerra", "Largo da Paz", 5);
        metro_recife.add_aresta("Afogados", "Joana Bezerra", 6);
        metro_recife.add_aresta("Afogados", "Ipiranga", 3);
        metro_recife.add_aresta("Ipiranga", "Afogados", 4);
        metro_recife.add_aresta("Ipiranga", "Mangueira", 3);
        metro_recife.add_aresta("Mangueira", "Ipiranga", 3);
        metro_recife.add_aresta("Mangueira", "Santa Luzia", 4);
        metro_recife.add_aresta("Santa Luzia", "Mangueira", 4);
        metro_recife.add_aresta("Santa Luzia", "Werneck", 4);
        metro_recife.add_aresta("Werneck", "Santa Luzia", 4);
        metro_recife.add_aresta("Werneck", "Barro", 4);
        metro_recife.add_aresta("Barro", "Werneck", 5);
        metro_recife.add_aresta("Barro", "Tejipio", 5);
        metro_recife.add_aresta("Tejipio", "Barro", 5);
        metro_recife.add_aresta("Tejipio", "Coqueiral", 4);
        metro_recife.add_aresta("Coqueiral", "Tejipio", 4);
        metro_recife.add_aresta("Coqueiral", "Alto do Ceu", 6);
        metro_recife.add_aresta("Coqueiral", "Cavaleiro", 4);
        metro_recife.add_aresta("Alto do Ceu", "Coqueiral", 6);
        metro_recife.add_aresta("Alto do Ceu", "Curado", 4);
        metro_recife.add_aresta("Curado", "Alto do Ceu", 4);
        metro_recife.add_aresta("Curado", "Rodoviaria", 5);
        metro_recife.add_aresta("Rodoviaria", "Curado", 5);
        metro_recife.add_aresta("Rodoviaria", "Cosme e Damiao", 5);
        metro_recife.add_aresta("Cosme e Damiao", "Rodoviaria", 5);
        metro_recife.add_aresta("Cosme e Damiao", "Camaragibe", 6);
        metro_recife.add_aresta("Camaragibe", "Cosme e Damiao", 6);
        metro_recife.add_aresta("Cavaleiro", "Coqueiral", 4);
        metro_recife.add_aresta("Cavaleiro", "Floriano", 12);
        metro_recife.add_aresta("Floriano", "Cavaleiro", 12);
        metro_recife.add_aresta("Floriano", "Engenho Velho", 5);
        metro_recife.add_aresta("Engenho Velho", "Floriano", 5);
        metro_recife.add_aresta("Engenho Velho", "Jaboatao", 5);
        metro_recife.add_aresta("Jaboatao", "Engenho Velho", 5);
        metro_recife.add_aresta("Largo da Paz", "Joana Bezerra", 6);
        metro_recife.add_aresta("Largo da Paz", "Imbiribeira", 4);
        metro_recife.add_aresta("Imbiribeira", "Largo da Paz", 4);
        metro_recife.add_aresta("Imbiribeira", "Antonio Falcao", 10);
        metro_recife.add_aresta("Antonio Falcao", "Imbiribeira", 10);
        metro_recife.add_aresta("Antonio Falcao", "Shopping", 3);
        metro_recife.add_aresta("Shopping", "Antonio Falcao", 3);
        metro_recife.add_aresta("Shopping", "Tancredo Neves", 3);
        metro_recife.add_aresta("Tancredo Neves", "Shopping", 3);
        metro_recife.add_aresta("Tancredo Neves", "Aeroporto", 6);
        metro_recife.add_aresta("Aeroporto", "Tancredo Neves", 6);
        metro_recife.add_aresta("Aeroporto", "Porta Larga", 6);
        metro_recife.add_aresta("Porta Larga", "Aeroporto", 6);
        metro_recife.add_aresta("Porta Larga", "Monte dos Guararapes", 4);
        metro_recife.add_aresta("Monte dos Guararapes", "Porta Larga", 4);
        metro_recife.add_aresta("Monte dos Guararapes", "Prazeres", 4);
        metro_recife.add_aresta("Prazeres", "Monte dos Guararapes", 4);
        metro_recife.add_aresta("Prazeres", "Cajueiro Seco", 5);
        metro_recife.add_aresta("Cajueiro Seco", "Prazeres", 5);

    metro_recife.printar();

    cout << "\n----------DFS----------\n\n";
    metro_recife.printar_dfs("Recife", "Prazeres");
    cout << "\n----------BFS----------\n\n";
    metro_recife.printar_bfs("Recife", "Prazeres");
    cout << "\n----------Dijkstra----------\n\n";
    metro_recife.printar_dijkstra("Recife", "Prazeres");
    cout << "\n***************************\n\n";
    metro_recife.possiveis_dijkstra("Recife");

    return 0;
}
