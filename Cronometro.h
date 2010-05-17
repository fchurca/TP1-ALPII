/******************************************************************************
* Algoritmos y Programación II - 75.41 *
* Cátedra Ing. Patricia Calvo *
* Facultad de Ingeniería - Universidad de Buenos Aires *
******************************************************************************/
/* TDA Cronometro
* Archivo : Cronometro.h
* Versión : 1.0
*/
#ifndef __CRONOMETRO_H__
#define __CRONOMETRO_H__
#include <time.h>
#include <sstream>
/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/
/* Definición del TDA Cronometro */
class Cronometro{
    
private:
/******************************************************************************/
/* Definicion de Atributos */
/*--------------------------*/
/* El atributo inicio guarda el tiempo en que se inicia el cronometro*/
    clock_t inicio;
/* El atributo cronometro guarda la suma de los intervalos de tiempo entre que se
inicia el cronometro y se pausa, o se inicia y se detiene*/
    long contador;
/* El atributo pausado guarda el estado actual del cronometro, si esta pausado
o no*/
     bool pausado;
/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/
/*
pre : ninguna.
post: Crea un Cronometro inicializado en cero.
*/
public:
    
Cronometro(){ iniciar();}
    
/*
pre : el cronometro debe haber sido creado con el constructor.
post: Borra todos los tiempos acumulados y estable el instante en que se
comienza a contar el tiempo.
*/
 
void iniciar(){
    
    contador = 0;
    inicio = clock();
    this->pausado = false;}

/*
pre : el cronometro debe haber sido creado con el constructor.
post: Acumula el tiempo transcurrido desde la creacion, inicio o continuar
(lo ultimo que haya pasado).
*/

void pausar(){
    
    clock_t fin;
    fin = clock();
    contador += fin - inicio;
    this->pausado = true;}
    
/*
pre : el cronometro debe haber sido creado con el constructor.
post: Estable el instante a partir del cual se cuenta el tiempo.
*/

void continuar(){
    
    if (this->pausado){
    inicio = clock();
    this->pausado = false;}
}

/*
pre : El cronometro debe haber sido creado con el constructor.
post: Finaliza la cuenta y acumula todos los tiempos transcurridos.
*/

void parar(){
    
    if (!this->pausado){
    this->pausar();
    this->pausado = true;}
}

/*
pre : El cronometro debe haber sido creado con el constructor.
post: Devuelve una leyenda con los milisegundos que estan acumulados.
*/

std::string toString(){
    
    std::stringstream convertidor;
    convertidor << this->contador;
    return "Transcurrieron " + convertidor.str() + " milisegundos";}

/*
pre : El cronometro debe haber sido creado con el constructor.
post: Devuelve la cantidad de milisegundos que estan acumulados.
*/

long getTiempoTranscurrido(){
    
    return this->contador;}
    
};

#endif /* __CRONOMETRO_H__ */





