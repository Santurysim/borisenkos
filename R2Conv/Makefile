CC = g++ $(CFLAGS)
CFLAGS = -g -O0 -I. -I.. -I/usr/X11R6/include -L/usr/X11R6/lib

conv: convmain.o R2Conv.o ../R2Graph/R2Graph.o ../GWindow/gwindow.o
	$(CC) -o conv convmain.o R2Conv.o \
		 ../R2Graph/R2Graph.o ../GWindow/gwindow.o -lX11

convtst: convtst.o R2Conv.o ../R2Graph/R2Graph.o
	$(CC) -o convtst convtst.o R2Conv.o ../R2Graph/R2Graph.o

convmain.o: convmain.cpp R2Conv.h PointDeq.h ../R2Graph/R2Graph.h
	$(CC) -c convmain.cpp

convtst.o: convtst.cpp R2Conv.h R2Conv.h PointDeq.h ../R2Graph/R2Graph.h
	$(CC) -c convtst.cpp

R2Conv.o: R2Conv.cpp R2Conv.h PointDeq.h ../R2Graph/R2Graph.h
	$(CC) -c R2Conv.cpp

../R2Graph/R2Graph.o: ../R2Graph/R2Graph.h ../R2Graph/R2Graph.cpp
	cd ../R2Graph; make R2Graph.o

../GWindow/gwindow.o: ../GWindow/gwindow.cpp ../GWindow/gwindow.h
	cd ../GWindow; make gwindow.o

clean:
	rm -f *.o convtst conv core
	cd ../GWindow; make clean
	cd ../R2Graph; make clean
