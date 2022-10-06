// g++ -Wall consumo.cpp

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/**
 *  transforma potencia em w para kW
 *  parametro: inteiro w - potencia em watts
 *  retorno: valor calculado do tipo float
 */
float transforma_potencia(int w) {
    return (float)w/1000;
}

/**
 *  transforma minutos em horas
 *  parametro: float m - tempo em minutos
 *  retorno: valor calculado do tipo float
 */
float transforma_tempo(float min) {
    return min/60;
}

/**
 *  calcula o consumo energético em kWh
 *  parametro: flot m - potencia em kw
 *  parametro: float hora - tempo em h
 *  retorno: valor calculado para o consumo
 */
float calcula_consumo(float kw, float hora) {
    return kw*hora;
}

/********* Aqui comeca o codigo de teste. Nao modificar! ************/

int main()
{
    int w = 5200;
    float min = 15.0;

	float kw = transforma_potencia(w);
    float hora = transforma_tempo(min);
    float consumo = calcula_consumo(kw, hora);
	
    cout << "\n Horas = " << hora << "h";
    cout << "\n Potencia = " << kw << "kW";
    cout << "\n Consumo = " << consumo << "kWh";
	cout << endl;
	
    return 0;
}
