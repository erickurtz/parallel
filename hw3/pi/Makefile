CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
LINKS = -lm
SMALL  =        100
MEDIUM =   10000000
LARGE = 10000000000

HOST := $(shell hostname)
ifeq ($(HOST),cisc372)
RUN = srun
else
RUN = mpiexec
endif

run : pi_mpi
	$(RUN) -n 2 ./pi_mpi

pi_mpi : pi_mpi.c
	$(MPICC) -o pi_mpi pi_mpi.c

clean :
	rm -f pi pi_mpi *~ a.out

