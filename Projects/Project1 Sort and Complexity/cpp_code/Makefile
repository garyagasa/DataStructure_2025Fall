edit : reverse_polish_test.o reverse_polish.o
	g++ -o edit reverse_polish_test.o reverse_polish.o

reverse_polish.o : reverse_polish.cpp reverse_polish.h
	g++ -c reverse_polish.cpp

reverse_polish_test.o : reverse_polish_test.cpp reverse_polish.h
	g++ -c reverse_polish_test.cpp

clean :
	rm -f edit reverse_polish_test.o reverse_polish.o