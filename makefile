####################################
# expr: expression matcher

#	Make library
expr: expr.cpp
	c++ $? -c

#	Make debug bin
Dexpr: expr.cpp
	c++ $? -o $@ -DEXPR_DEBUG

####################################
# fsnode: file system node model

#	Make library
fsnode: fsnode.cpp
	c++ $? -c

#	Make debug bin
Dfsnode: fsnode.cpp
	c++ $? -o $@ -DFSNODE_DEBUG

####################################
# clean: remove all binaries
#	Add specific bin names here
clean:
	rm -f Dexpr Dfsnode *.o *~

.PHONY: clean debug
