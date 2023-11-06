COMPILE = gcc -g
OFILES = main.o flight.o

flight: $(OFILES)
	$(COMPILE) -o flight $(OFILES)

main.o: main.c flight.h
	$(COMPILE) -c main.c

flight.o: flight.c flight.h
	$(COMPILE) -c flight.c

clean:
	/bin/rm -f *.o flight 
