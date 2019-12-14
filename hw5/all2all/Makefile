RUN = mpiexec

test: all2all.o driver.c
	mpicc -o driver.exe driver.c all2all.o
	$(RUN) -n 2 ./driver.exe

all2all: all2all.c
	mpicc -c -o all2all.o all2all.c

clean:
	rm -f *~ all2all.o driver.o driver.exe
