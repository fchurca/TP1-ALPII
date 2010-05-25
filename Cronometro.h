/*******************************************************************************
 *	Cronometro.h
 *	Librería de cronómetros con resolución de microsegundos
 *	Implementación:	Martín Muñoz
*******************************************************************************/

#ifndef __CRONOMETRO_H__
#define __CRONOMETRO_H__


#include <stdio.h>
#include <time.h>
#include <sys/time.h>

class Cronometro{
private:
	struct timeval
		t_ini,
		t_fin;
	clock_t usecs;
	bool pausado;
	clock_t timeval_diff(struct timeval & a, struct timeval &b){
		return
			(a.tv_sec - b.tv_sec) * 1000000 +
			(a.tv_usec - b.tv_usec);
	};
public:

	Cronometro(){
		iniciar();
	};

	void iniciar(){
		this->usecs = 0;
		pausado = false;
		gettimeofday(&t_ini, NULL);
	};

	void pausar(){
		gettimeofday(&t_fin, NULL);
		this->usecs += this->timeval_diff(this->t_fin, this->t_ini);
		t_ini = t_fin;
		pausado = true;
	};

	void continuar(){
		if (this->pausado){
			gettimeofday(&t_ini, NULL);
			this->pausado = false;
		}
	};
	void parar(){
		if (!this->pausado){
			this->pausar();
		}
	};

	clock_t getTiempoTranscurrido(){
		return this->usecs;
	};
};


#endif	//	__CRONOMETRO_H__
