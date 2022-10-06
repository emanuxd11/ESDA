// g++ -Wall GAC.cpp

#include <iostream>
#include <string>

using namespace std;

class Aluno
{
private: // Porque e', para ja', importante? Experimente comentar a linha...
  string nome;
  string curso;
  int numero;
  float media;

public:
  Aluno(string nom) { /* completar (alinea a)) */
    nome = nom;
    numero = 0;
    media = 0;
  }
  
  Aluno(string nom, string cur, int num) { /* completar (alinea a)) */
    nome = nom;
    curso = cur;
    numero = num;
    media = 0;
  }

  /* completar (alinea b)) */
  void set_curso(string cur) {
    curso = cur;
  }

  void set_num(int num) {
    numero = num;
  }

  void set_media(float med) {
    media = med;
  }

  float get_media() {
    return media;
  }

  /* completar (alinea c)) */
  void imprimir(ostream &os) const {
    os << "\t" << nome << "\t| " << curso << "\t| " << numero << "\t| " << media << "\n";
  }

  /* completar (alinea d)) */
  string sigla() const {
    string ret = "";

    for(char c: nome) {
      if(isupper(c)) {
        ret += c;
      }
    }

    return ret;
  }
};

int main()
{

  Aluno a1("Pedro Ferreira");
  Aluno a2("Ana Martins", "Direito", 2022045);
  Aluno a3("Manuel Silva", "Arquitetura", 2021033);

  /* completar (alinea b)) */
  a1.set_curso("Medicina");
  a1.set_num(2020123);
  a1.set_media(10.3);
  a2.set_media(18.2);
  a3.set_media(16);

  cout << "Lista de alunos: (nome | curso | numero | media)" << endl;
  /*cout << "\t" << a1.nome << "\t| " << a1.curso << "\t| " << a1.numero << "\t| " << a1.media << endl;
  cout << "\t" << a2.nome << "\t| " << a2.curso << "\t| " << a2.numero << "\t| " << a2.media << endl;
  cout << "\t" << a3.nome << "\t| " << a3.curso << "\t| " << a3.numero << "\t| " << a3.media << endl;*/

  /* completar (alinea c)) */
  //cout << "\nPela funcao:\n";
  Aluno al("Alberto Mateus", "Engenharia", 2019197); 
  a1.imprimir(cout);
  a2.imprimir(cout);
  a3.imprimir(cout);
  al.imprimir(cout);

/*
  ofstream f("out.txt");
  a1.imprimir(f);
  a2.imprimir(f);
*/

  /* completar (alinea d) */
  cout << a1.sigla() << "\n";
  cout << a2.sigla() << "\n";
  cout << a3.sigla() << "\n";
  cout << al.sigla() << "\n";

  return 0;
}