#include "Cronometro.h"

clock_t Cronometro::timeval_diff(struct timeval & a, struct timeval &b){
	return
		(a.tv_sec - b.tv_sec) * 1000000 +
		(a.tv_usec - b.tv_usec);
}
Cronometro::Cronometro(){
	iniciar();
}
void Cronometro::iniciar(){
	this->usecs = 0;
	pausado = false;
	gettimeofday(&t_ini, NULL);
}
void Cronometro::pausar(){
	gettimeofday(&t_fin, NULL);
	this->usecs += this->timeval_diff(this->t_fin, this->t_ini);
	t_ini = t_fin;
	pausado = true;
}
void Cronometro::continuar(){
	if (this->pausado){
		gettimeofday(&t_ini, NULL);
		this->pausado = false;
	}
}
void Cronometro::parar(){
	if (!this->pausado){
		this->pausar();
	}
}
clock_t Cronometro::getTiempoTranscurrido(){
	return this->usecs;
}

