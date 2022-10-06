#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "componentes.hpp"

using namespace std;

/* --------------- */ 
/*    Componente   */ 
/* --------------- */ 

// Constructors

Componente::Componente()
{
    id = "";
    nome = "";
    categoria = "";
    preco = 0;
    quantidade = 0;
}

Componente::Componente(string c_id, string c_nome, int c_quantidade, float c_preco, string c_categoria)
{
    if(c_id.empty()) id = "";
    if(c_nome.empty()) nome = "";
    if(quantidade < 0) quantidade = 0;
    if(c_preco < 0) preco = 0;
    if(c_categoria.empty()) categoria = "";

    id = c_id;
    nome = c_nome;
    quantidade = c_quantidade;
    preco = c_preco;
    categoria = c_categoria;
}

// Get Methods

string Componente::getId() const
{
    return id;
}

string Componente::getNome() const
{
    return nome;
}

string Componente::getCategoria() const
{
    return categoria;
}

float Componente::getPreco() const
{
    return preco;
}

int Componente::getQuantidade() const
{
    return quantidade;
}

// Set Methods

void Componente::setId(string c_id)
{
    if(c_id.empty()) id = "";
    id = c_id;
}

void Componente::setNome(string c_nome)
{
    if(nome.empty()) nome = "";
    nome = c_nome;
}

void Componente::setQuantidade(int c_quantidade)
{
    if(quantidade < 0) quantidade = 0;
    quantidade = c_quantidade;
}

void Componente::setPreco(float c_preco)
{
    if(preco < 0) preco = 0;
    preco = c_preco;
}

void Componente::setCategoria(string c_categoria)
{
    if(c_categoria.empty()) categoria = "";
    categoria = c_categoria;
}

// Friend Fucntion

bool comparaComponentes(const Componente *c1, const Componente *c2)
{
    //if(c1 == NULL || c2 == NULL) return (o que retornar nesta situação?);

    if(c1->preco < c2->preco) {
        return true;
    } else if(c1->preco == c2->preco) {
        if(c1->id < c2->id) return true;
    }

    return false;
}

/* --------------- */ 
/*     Armazém     */ 
/* --------------- */

// Constructor

Armazem::Armazem()
{
    componentes.clear();
}

// Destructor

Armazem::~Armazem()
{
    for(Componente *elem: componentes) {
        delete elem;
    }
}

// Get Methods

vector<Componente*> Armazem::getComponentes() const
{
    return componentes;
}

size_t Armazem::getTamanho() const
{
    return componentes.size();
}

// Other Methods

int Armazem::componenteInsere(Componente *c)
{
    if(c == NULL) return -1;

    for(Componente *elem: componentes) {
        if(c->getId() == elem->getId()) {
            elem->setQuantidade(elem->getQuantidade() + c->getQuantidade());
            elem->setPreco(c->getPreco());

            delete c;
            return 1;
        }
    }

    componentes.push_back(c);
    return 0;
}

Componente *Armazem::componenteRemove(const string nome)
{   
    if(nome.empty()) return NULL;

    for(unsigned int i = 0; i < getTamanho(); i++) {
        if(componentes[i]->getNome() == nome) {
            Componente *ret = componentes[i];
            componentes.erase(componentes.begin()+i);
            
            return ret;
        }
    }

    return NULL;
}

int Armazem::importa(const string nome_ficheiro)
{
    if(nome_ficheiro.empty()) return -1;

    fstream f;
    f.open(nome_ficheiro, ios::in);
    string linha, token;
    vector<string> tokens;  
    
    while(getline(f, linha)) {
        stringstream ss_linha(linha);
        while(getline(ss_linha, token, ',')) {
            tokens.push_back(token);
        }

        //Inserir o componente no armazém
        Componente *a_inserir = new Componente(tokens[0], tokens[1], stoi(tokens[3]), stof(tokens[4]), tokens[2]);
        if(componenteInsere(a_inserir) == -1) return -1;
        
        tokens.clear();
    }

    f.close();
    return 0;
}

vector<int> Armazem::pesquisaCategoria(const string categoria)
{ 
    if(categoria.empty()) return {};

    vector<int> ret;
    for(unsigned int i = 0; i < getTamanho(); i++) {
        if(componentes[i]->getCategoria() == categoria) {
            ret.push_back(i);
        }
    }

    return ret;
}

void Armazem::ordena()
{
    for(Componente *prim_elem: componentes) {
        for(Componente *seg_elem: componentes) {
            if(comparaComponentes(prim_elem, seg_elem)) {
                swap(*prim_elem, *seg_elem);
            }
        }
    }

    /* Esta maneira seria ainda mais direta. Porém, foi advertido que poderia dar
    aso a um falso alerta de plágio, pelo que implementamos o sort manualmente. */
    //sort(componentes.begin(), componentes.end(), &comparaComponentes);
}