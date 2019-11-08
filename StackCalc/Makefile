CC = g++ $(CFLAGS)
CFLAGS = -g -O0

StackCalc: StackCalc.o RealStack.o
	$(CC) -o StackCalc StackCalc.o RealStack.o -lm

StackCalc.o: StackCalc.cpp RealStack.h
	$(CC) -c StackCalc.cpp

RealStack.o: RealStack.cpp RealStack.h
	$(CC) -c RealStack.cpp

clean:
	rm -f StackCalc *.o
