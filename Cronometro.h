/*******************************************************************************
 *	Cronometro.h
 *	Librería de cronómetros con resolución de microsegundos
 *	Implementación: Martín Muñoz
 *	Documentación:  Federico Churca Torrusio
*******************************************************************************/

#ifndef __CRONOMETRO_H__
#define __CRONOMETRO_H__

#include <time.h>
#include <sys/time.h>

class Cronometro{
private:
	struct timeval
		t_ini,
		t_fin;
	clock_t usecs;
	bool pausado;
	clock_t timeval_diff(struct timeval & a, struct timeval &b);
public:
	Cronometro();
	void iniciar();
	void pausar();
	void continuar();
	void parar();
	clock_t getTiempoTranscurrido();
};

#endif	//	__CRONOMETRO_H__
