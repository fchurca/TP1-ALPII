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
# fsnode: file system tree model

#	Make library
fsmodel: fsmodel.cpp
	c++ $? -c

#	Make debug bin
Dfsmodel: fsmodel.cpp
	c++ $? -g -o $@ -DFSMODEL_DEBUG

####################################
# clean: remove all binaries
#	Add specific bin names here
clean:
	rm -f Dexpr Dfsnode *.o *~

.PHONY: clean
