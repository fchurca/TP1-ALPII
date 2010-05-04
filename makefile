expr: expr.cpp
	c++ $? -c

Dexpr: expr.cpp
	c++ $? -o $@ -DEXPR_DEBUG

clean:
	rm -f Dexpr *.o *~

#debug: TP2
#	./TP2

.PHONY: clean debug
