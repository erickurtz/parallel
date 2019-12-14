include ../../config/constants.mk

seq: integral.exe Makefile
	$(RUN) ./integral.exe

integral.exe: integral.c Makefile
	$(CC) -o integral.exe integral.c -lm

par: integral_mpi.exe Makefile
	$(MPIRUN) -n 2 ./integral_mpi.exe

integral_mpi.exe: integral_mpi.c Makefile
	$(MPICC) -o integral_mpi.exe integral_mpi.c -lm

nb: integral_nb.exe Makefile
	$(MPIRUN) -n 2 ./integral_nb.exe

integral_nb.exe: integral_nb.c Makefile
	$(MPICC) -o integral_nb.exe integral_nb.c -lm

clean:
	rm -f *~ *.exe a.out
