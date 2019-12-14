CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
LINKS = -lm
SMALL  =        100
MEDIUM =   10000000
LARGE = 1000000000

HOST := $(shell hostname)
ifeq ($(HOST),cisc372)
RUN = srun
else
RUN = mpiexec
endif

all : seq_small seq_medium

pin : pin.c
	$(CC) -o pin pin.c $(LINKS)
pin_pt: pin_pt.c
	$(CC) -o pin_pt pin_pt.c $(LINKS) -lpthread -D_POSIX_C_SOURCE=199309L

seq_small : pin
	./pin $(SMALL)

seq_medium: pin
	./pin $(MEDIUM)

thread_medium: pin_pt
	./pin_pt 40 $(MEDIUM) 

thread_small: pin_pt
	./pin_pt 40 $(SMALL)

thread_large: pin_pt
	./pin_pt 40 $(LARGE)


clean :
	rm -f pin pin_mpi pin_pt *~ a.out
