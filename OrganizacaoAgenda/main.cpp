#include <bits/stdc++.h>
#include <chrono>
using namespace std;

struct Evento {
    string nome;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;

};
void maxheapify(vector<Evento>&eventos,int atual,int tamanho)
{
     int esquerda,direita;
     esquerda=2*atual+1;
     direita=2*atual+2;
     int maior=atual;
     if (esquerda < tamanho &&
   (eventos[esquerda].ano > eventos[maior].ano ||
   (eventos[esquerda].ano == eventos[maior].ano && eventos[esquerda].mes > eventos[maior].mes) ||
   (eventos[esquerda].ano == eventos[maior].ano && eventos[esquerda].mes == eventos[maior].mes && eventos[esquerda].dia > eventos[maior].dia) ||
   (eventos[esquerda].ano == eventos[maior].ano && eventos[esquerda].mes == eventos[maior].mes && eventos[esquerda].dia == eventos[maior].dia && eventos[esquerda].hora > eventos[maior].hora) ||
   (eventos[esquerda].ano == eventos[maior].ano && eventos[esquerda].mes == eventos[maior].mes && eventos[esquerda].dia == eventos[maior].dia && eventos[esquerda].hora == eventos[maior].hora && eventos[esquerda].minuto > eventos[maior].minuto)))
{
    maior = esquerda;
}
    if (direita < tamanho &&
   (eventos[direita].ano > eventos[maior].ano ||
   (eventos[direita].ano == eventos[maior].ano && eventos[direita].mes > eventos[maior].mes) ||
   (eventos[direita].ano == eventos[maior].ano && eventos[direita].mes == eventos[maior].mes && eventos[direita].dia > eventos[maior].dia) ||
   (eventos[direita].ano == eventos[maior].ano && eventos[direita].mes == eventos[maior].mes && eventos[direita].dia == eventos[maior].dia && eventos[direita].hora > eventos[maior].hora) ||
   (eventos[direita].ano == eventos[maior].ano && eventos[direita].mes == eventos[maior].mes && eventos[direita].dia == eventos[maior].dia && eventos[direita].hora == eventos[maior].hora && eventos[direita].minuto > eventos[maior].minuto)))
{
        maior=direita;
}

    if(maior!=atual){
    swap(eventos[atual],eventos[maior]);
    maxheapify(eventos,maior,tamanho);}


}

void contrucaoheapmaxima(vector<Evento>&eventos,int tamanho)
{
    int posicaoInicial=tamanho/2 - 1;//maior no pai
    for(int i=posicaoInicial;i>=0;--i)
    {
        maxheapify(eventos,i,tamanho);
    }
}
void HeapSort(vector<Evento>&eventos)
{
    int tamanho=eventos.size();
    contrucaoheapmaxima(eventos,tamanho);

    for(int i=tamanho-1;i>0;i--)
    {
        swap(eventos[i],eventos[0]);
        maxheapify(eventos,0,i);

    }

}

void printar(vector<Evento> &eventos) {

    for (const auto& evento : eventos) {
        cout << evento.nome << ": "
             << evento.dia << "/" << evento.mes << "/" << evento.ano
             << ", " << evento.hora << ":" << (evento.minuto < 10 ? "0" : "") << evento.minuto << " h" << endl;
    }
    cout <<endl<<"tempo de execução: ";
}

void Merge(vector<Evento> &vetor ,vector<Evento> &MetadeEsq, vector<Evento> &MetadeDir,int tamanhoEsq,int tamanhoDir){
    int i=0;
    int j=0;
    int k=0;
    while(i<tamanhoEsq || j<tamanhoDir)
    {
        if ( (i<tamanhoEsq && j<tamanhoDir) &&
        (MetadeEsq[i].ano > MetadeDir[j].ano ||
        (MetadeEsq[i].ano == MetadeDir[j].ano && MetadeEsq[i].mes > MetadeDir[j].mes) ||
        (MetadeEsq[i].ano == MetadeDir[j].ano && MetadeEsq[i].mes == MetadeDir[j].mes && MetadeEsq[i].dia > MetadeDir[j].dia) ||
        (MetadeEsq[i].ano == MetadeDir[j].ano && MetadeEsq[i].mes == MetadeDir[j].mes && MetadeEsq[i].dia == MetadeDir[j].dia && MetadeEsq[i].hora > MetadeDir[j].hora) ||
        (MetadeEsq[i].ano == MetadeDir[j].ano && MetadeEsq[i].mes == MetadeDir[j].mes && MetadeEsq[i].dia == MetadeDir[j].dia && MetadeEsq[i].hora == MetadeDir[j].hora && MetadeEsq[i].minuto > MetadeDir[j].minuto)))
    {
            vetor[k]=MetadeDir[j];
            j++;
            k++;
    }
        else if ( (i<tamanhoEsq && j<tamanhoDir) &&
        (MetadeDir[j].ano > MetadeEsq[i].ano ||
        (MetadeDir[j].ano == MetadeEsq[i].ano && MetadeDir[j].mes > MetadeEsq[i].mes) ||
        (MetadeDir[j].ano == MetadeEsq[i].ano && MetadeDir[j].mes == MetadeEsq[i].mes && MetadeDir[j].dia > MetadeEsq[i].dia) ||
        (MetadeDir[j].ano == MetadeEsq[i].ano && MetadeDir[j].mes == MetadeEsq[i].mes && MetadeDir[j].dia == MetadeEsq[i].dia && MetadeDir[j].hora > MetadeEsq[i].hora) ||
        (MetadeDir[j].ano == MetadeEsq[i].ano && MetadeDir[j].mes == MetadeEsq[i].mes && MetadeDir[j].dia == MetadeEsq[i].dia && MetadeDir[j].hora == MetadeEsq[i].hora && MetadeDir[j].minuto > MetadeEsq[i].minuto)))
    {
            vetor[k]=MetadeEsq[i];
            i++;
            k++;
    }
        else if(j<tamanhoDir && i>=tamanhoEsq) //
    {
            vetor[k]=MetadeDir[j];
            j++;
            k++;
    }
        else
    {
            vetor[k]=MetadeEsq[i];
            i++;
            k++;
    }


    }
}

void MergeSort(vector<Evento> &vetor )
{
    int tamanho=vetor.size();
    if(tamanho<=1)
    {
        return;
    }
    int meio=tamanho/2;
    vector<Evento> MetadeEsq;
    vector<Evento> MetadeDir;
    for(int i=0;i<meio;i++)//copiando os vetores;
    {
        MetadeEsq.push_back(vetor[i]);
    }
    for(int i=meio;i<tamanho;i++)
    {
        MetadeDir.push_back(vetor[i]);
    }
    MergeSort(MetadeEsq);
    MergeSort(MetadeDir);//ate aq ele ta quebrando o vetor principal e separando em 2!
    int tamanhoEsq,tamanhoDir;
    tamanhoEsq=MetadeEsq.size();
    tamanhoDir=MetadeDir.size();
    Merge(vetor,MetadeEsq,MetadeDir,tamanhoEsq,tamanhoDir);

}

int part(vector<Evento> &vetor,int esq,int dir){

    Evento pivo=vetor[esq];
    int pEsq=esq;
    int pDir=dir + 1;
    do
    {
       do {pEsq++; }
     while(pEsq<dir  &&
    (vetor[pEsq].ano < pivo.ano ||
    (vetor[pEsq].ano == pivo.ano && vetor[pEsq].mes < pivo.mes) ||
    (vetor[pEsq].ano == pivo.ano && vetor[pEsq].mes == pivo.mes && vetor[pEsq].dia < pivo.dia) ||
    (vetor[pEsq].ano == pivo.ano && vetor[pEsq].mes == pivo.mes && vetor[pEsq].dia == pivo.dia && vetor[pEsq].hora < pivo.hora) ||
    (vetor[pEsq].ano == pivo.ano && vetor[pEsq].mes == pivo.mes && vetor[pEsq].dia == pivo.dia && vetor[pEsq].hora == pivo.hora && vetor[pEsq].minuto < pivo.minuto)));

       do{pDir --;}while(pDir>esq &&
    (vetor[pDir].ano > pivo.ano ||
    (vetor[pDir].ano == pivo.ano && vetor[pDir].mes > pivo.mes) ||
    (vetor[pDir].ano == pivo.ano && vetor[pDir].mes == pivo.mes && vetor[pDir].dia > pivo.dia) ||
    (vetor[pDir].ano == pivo.ano && vetor[pDir].mes == pivo.mes && vetor[pDir].dia == pivo.dia && vetor[pDir].hora > pivo.hora) ||
    (vetor[pDir].ano == pivo.ano && vetor[pDir].mes == pivo.mes && vetor[pDir].dia == pivo.dia && vetor[pDir].hora == pivo.hora && vetor[pDir].minuto > pivo.minuto)));

        swap(vetor[pDir],vetor[pEsq]);


    }while(pDir>pEsq);
    swap(vetor[pDir],vetor[pEsq]);
    swap(vetor[pDir],vetor[esq]);
    return pDir;
}

void quicksort(vector<Evento>&vetor, int esq, int dir){
    if(esq<dir){
        int s = part(vetor, esq, dir);
        quicksort(vetor, esq, s - 1);
        quicksort(vetor, s + 1, dir);
    }
    return;
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
    //HeapSort(eventos);
    eventos.insert(eventos.begin(),{"Olha! Recife Noturno - Tour Historico", 1, 10, 2024, 21, 0});
    eventos.insert(eventos.begin(),{"Olha! Recife Pedalando - Antigos Cinemas do Recife", 29, 9, 2024, 9, 0});
    eventos.insert(eventos.begin(),{"Olha! Recife de Barco - Passeio no Capibaribe", 26, 9, 2024, 12, 0});
    //auto inicio = chrono::high_resolution_clock::now();
   // HeapSort(eventos);
    //auto fim = chrono::high_resolution_clock::now();
    //auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
    //auto inicio = chrono::high_resolution_clock::now();
    //MergeSort(eventos);
     //auto fim = chrono::high_resolution_clock::now();
     //auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
    //auto inicio = chrono::high_resolution_clock::now();
    //quicksort(eventos,0,eventos.size()-1);
   // auto fim = chrono::high_resolution_clock::now();
    //auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
    printar(eventos);
    cout<<duracao<<"ns"<<endl;
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//c)por se tratar de um vetor dinamico pequeno mesmo apos os incrementos todos os 3 algoritmos obtiveram o tempo de 0ns
//d)para vetores dinamicos,em questao de complexidade, o mais estavel seria o heapsort com complexidade de O(n log(n)) em todos os casos e sem precisar da utilizacao de outros vetores como o mergesort(menor utilizacao de memoria). 
//e)um sistema de ordenaçao eficiente, se torna um facilitador de busca para o usuario ja que nao precisaria olhar todos os componentes da lista para achar a data procurada,alem de trazer uma organizaçao cronologica para a agenda em si.
