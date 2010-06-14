@ECHO off
color 71

TITLE Programa de Busqueda
CLS

:Inicio 
TITLE Programa de Busqueda
CLS
ECHO.
ECHO.
ECHO           Algoritmos y Programacion II
ECHO.
ECHO                   Catedra Calvo
ECHO.
ECHO                 Trabajo Practico
ECHO.
ECHO.
ECHO.

ECHO 		Integrantes: 
ECHO.
ECHO.

ECHO 	Federico Churca
ECHO.
ECHO 	Nicolas Sama
ECHO.
ECHO 	Mariano
ECHO.
ECHO 	Martin 
ECHO.
ECHO 	Fiona Gonzalez Lisella
ECHO.
ECHO.

ECHO Por favor presione cualquier tecla para continuar

PAUSE > nul

GOTO menu


 
:Menu
TITLE Programa de Busqueda 
CLS
ECHO.
ECHO.
ECHO Bienvenido al programa de busqueda.
ECHO.
ECHO.
ECHO 1. Buscar Utilizando Lista
ECHO.
ECHO 2. Buscar Utilizando Vector
ECHO.
ECHO 3. Buscar Utilizando Arbol
ECHO.
ECHO 4. Clean
ECHO.
ECHO 5. Ayuda
ECHO.
ECHO 6. Salir
ECHO.
 
SET /p menup=Escribe el numero de la opcion elegida: 
IF %menup%==1 GOTO makelista
IF %menup%==2 GOTO makevector	
IF %menup%==3 GOTO makearbol
IF %menup%==4 GOTO BoolGen
IF %menup%==5 GOTO makemanual 
IF %menup%==6 exit
	ELSE GOTO error
 
 
:Error
TITLE Se ha producido un error
CLS
ECHO.
ECHO Ha elegido un numero incorrecto
ECHO Has escrito "%menup%". Debe escribir el numero que indica la opcion.
ECHO Pulse una tecla para volver al menu.
PAUSE > nul
 
GOTO Menu

 
:makelista

CLS
ECHO.
ECHO Bienvenido a la busqueda por Lista
ECHO.
START TPIL.exe
ECHO.
ECHO Pulse una tecla para volver
PAUSE > nul
GOTO Menu
 

:makevector

CLS
ECHO.
ECHO Bienvenido a la busqueda por vector
START TPIV.exe
ECHO.
ECHO.
ECHO Pulse una tecla para volver
PAUSE > nul
GOTO Menu
 
 
 
:makearbol

CLS
ECHO Bienvenido a la busqueda por arbol enario
ECHO.
START TPIA.exe
ECHO.

ECHO.
ECHO Pulse una tecla para volver menu
PAUSE > nul
GOTO Menu
 
:makemanual
CLS
ECHO.
START Manual.doc
ECHO.
ECHO Pulse una tecla para volver menu

PAUSE > nul
GOTO Menu
 
 
:boolGen

CLS
ECHO.
ECHO ¿Desea regenerar todos los archivos?
ECHO.
ECHO 1. Si
ECHO.
ECHO 2. No
ECHO.

SET /p menup=Escribe el numero de la opcion elegida: 
IF %menup%==1 GOTO makegen
IF %menup%==2 GOTO menu
	ELSE GOTO error
ECHO.
ECHO.

:makegen

DEL  *.exe *.o
c++ main.cpp expr.cpp FSMoDEL.cpp FMoDEL.cpp tui.cpp -g -o TPIL -DFSMODEL_LIST
c++ main.cpp expr.cpp FSMoDEL.cpp FMoDEL.cpp tui.cpp -g -o TPIV -DFSMODEL_VECTOR
c++ main.cpp expr.cpp fsmoDEL.cpp fsnode.cpp tui.cpp -g -o TPIA -DFSMODEL_ARBOL
ECHO Se han regenerado todos los ejecutables.
ECHO.
ECHO.
ECHO Presione una tecla para volver al menu
ECHO.
PAUSE>nul
GOTO Menu



