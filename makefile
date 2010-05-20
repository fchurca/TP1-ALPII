####################################
# TPI: main binary

TPIV: main.cpp expr.cpp fsmodel.cpp fsnode.cpp tui.cpp
	c++ $? -g -o $@ -DFSMODEL_VECTOR

TPIL: main.cpp expr.cpp fsmodel.cpp fsnode.cpp tui.cpp
	c++ $? -g -o $@ -DFSMODEL_LIST

####################################
# expr: expression matcher

#	Make library
expr: expr.cpp
	c++ $? -c

#	Make debug bin
Dexpr: expr.cpp
	c++ $? -g -o $@ -DEXPR_DEBUG

####################################
# fsnode: file system node model

#	Make library
fsnode: fsnode.cpp
	c++ $? -c

#	Make debug bin
Dfsnode: fsnode.cpp
	c++ $? -g -o $@ -DFSNODE_DEBUG

####################################
# fsmodel: file system tree model; vector version

#	Make library
Vfsmodel: fsmodel.cpp fsnode.cpp expr.cpp
	c++ $? -c -DFSMODEL_VECTOR

#	Make debug bin
DVfsmodel: fsmodel.cpp fsnode.cpp expr.cpp
	c++ $? -g -o $@ -DFSMODEL_DEBUG -DFSMODEL_VECTOR

####################################
# fsmodel: file system tree model; list version

#	Make library
Lfsmodel: fsmodel.cpp fsnode.cpp expr.cpp
	c++ $? -c -DFSMODEL_LIST

#	Make debug bin
DLfsmodel: fsmodel.cpp fsnode.cpp expr.cpp
	c++ $? -g -o $@ -DFSMODEL_DEBUG -DFSMODEL_LIST

####################################
# clean: remove all binaries
#	Add specific bin names here
clean:
	rm -f TPIV TPIL Dexpr Dfsnode DVfsmodel DLfsmodel *.o *~

.PHONY: clean
