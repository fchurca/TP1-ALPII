@ECHO OFF
REM	menu.bat
REM	Archivo de lotes para manejo y ejecución de TPI-ALPII
REM	Autores:
REM		Fiona Gonzalez Lisella
REM		Nicolas Sama
REM		Federico Churca

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
ECHO 	Mariano Fernandez Vidal
ECHO.
ECHO 	Martin Munoz
ECHO.
ECHO 	Fiona Gonzalez Lisella
ECHO.
ECHO.
ECHO Por favor presione cualquier tecla para continuar
PAUSE > nul

:Menu
TITLE Programa de Busqueda 
CLS
ECHO Bienvenido al programa de busqueda.
ECHO.
ECHO 1. Buscar Utilizando Lista
ECHO.
ECHO 2. Buscar Utilizando Vector
ECHO.
ECHO 3. Buscar Utilizando Arbol
ECHO.
ECHO 4. Regenerar ejecutables
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
ECHO Bienvenido a la busqueda por arbol eneario
ECHO.
START TPIT.exe
ECHO.
ECHO.
ECHO Pulse una tecla para volver menu
PAUSE > nul
GOTO Menu

:makemanual
CLS
ECHO.
START Manual.pdf
ECHO.
ECHO Pulse una tecla para volver menu
PAUSE > nul
GOTO Menu

:boolGen
ECHO.
ECHO Esto eliminará los ejecutables existentes primero. ¿Continuar?
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
DEL *.exe
c++ main.cpp Cronometro.cpp expr.cpp FSModel.cpp FModel.cpp tui.cpp -g -o TPIL -DFSMODEL_LIST
c++ main.cpp Cronometro.cpp expr.cpp FSModel.cpp FModel.cpp tui.cpp -g -o TPIV -DFSMODEL_VECTOR
c++ main.cpp Cronometro.cpp expr.cpp FSModel-tree.cpp FModel.cpp tui.cpp -g -o TPIT -DFSMODEL_TREE
ECHO.
ECHO Se han regenerado todos los ejecutables
ECHO.
ECHO.
ECHO Presione una tecla para volver al menu
ECHO.
PAUSE > nul
GOTO Menu

