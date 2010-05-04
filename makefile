####################################
# expr: expression matcher

#	Make library
expr: expr.cpp
	c++ $? -c

#	Make debug bin
Dexpr: expr.cpp
	c++ $? -o $@ -DEXPR_DEBUG

####################################
# clean: remove all binaries
#	Add specific bin names here
clean:
	rm -f Dexpr *.o

.PHONY: clean debug
