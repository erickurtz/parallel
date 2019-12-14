SEMLIBDIR = ../sem
SEMLIB = $(SEMLIBDIR)/sem.o
LIBS = $(SEMLIB) -lpthread 
CC = cc -std=c11 -Wall -pedantic -I$(SEMLIBDIR)

all : run_spscsd

$(SEMLIB) : $(SEMLIBDIR)/sem.h $(SEMLIBDIR)/sem.c $(SEMLIBDIR)/Makefile
	make -C $(SEMLIBDIR)

spscsd.exec : spscsd.c $(SEMLIB)
	$(CC) -o spscsd.exec spscsd.c $(LIBS)

run_spscsd : spscsd.exec
	./spscsd.exec

spscmd.exec: spscmd.c $(SEMLIB)
	$(CC) -o spscmd.exec spscmd.c $(LIBS)

run_spscmd: spscmd.exec
	./spscmd.exec 5

clean :
	rm -f *~ *.tmp *.exec
