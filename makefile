####################################
# TPIX: main binaries

all: TPIV TPIL TPIT

TPIV: main.cpp expr.cpp FSModel.cpp FModel.cpp tui.cpp
	c++ $? -g -o $@ -DFSMODEL_VECTOR

TPIL: main.cpp expr.cpp FSModel.cpp FModel.cpp tui.cpp
	c++ $? -g -o $@ -DFSMODEL_LIST
	
TPIT: main.cpp expr.cpp FModel.cpp tui.cpp
	c++ $? -g -o $@ -DFSMODEL_TREE

####################################
# expr: expression matcher

#	Make library
expr: expr.cpp
	c++ $? -c

#	Make debug bin
Dexpr: expr.cpp
	c++ $? -g -o $@ -DEXPR_DEBUG

####################################
# clean: remove all binaries
#	Add specific bin names here
clean:
	rm -f TPIV TPIL TPIT Dexpr Dfsnode DVfsmodel DLfsmodel *.o *~

.PHONY: clean
