GCC = g++

out: bruteforce.o dp.o
	$(GCC) -o out main.cpp main.h bruteforce.o dp.o

bruteforce.o:
	$(GCC) -c bruteforce.cpp bruteforce.h

dp.o:
	$(GCC) -c dp.cpp dp.h

.PHONY: clean
clean:
	rm -rf *.o out *.h.gch