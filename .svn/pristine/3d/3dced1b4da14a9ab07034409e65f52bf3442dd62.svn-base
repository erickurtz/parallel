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


run : pingpong
	$(RUN) -n 2 ./pingpong

run40 : pingpong
	$(RUN) -n 40 ./pingpong

pingpong : pingpong.c
	$(MPICC) -o pingpong pingpong.c


clean :
	rm -f pingpong *~ a.out

