include ../../config/constants.mk

HBDCC=$(MPICC) -fopenmp

CONFIG1 = -DBOUNDARY=1 -DK=0.1 -DM=100 -DNSTEPS=150 -DWSTEP=10 -DNX=10 -DPWIDTH=2 -DDEBUG
CONFIG2 = -DBOUNDARY=2 -DK=0.1 -DM=100 -DNSTEPS=200000 -DWSTEP=500 -DNX=200 -DPWIDTH=2
CONFIG3 = -DBOUNDARY=2 -DK=0.1 -DM=100 -DNSTEPS=1000 -DWSTEP=0 -DNX=2000 -DPWIDTH=2

# Converts an animated GIF out.gif to an MPEG-4 movie video.mp4
MOVOPTS = -movflags faststart -pix_fmt yuv420p -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2"

######################### MPI Striped Version #########################

mpi1: diffusion2d_striped.c
	$(MPICC) -o mpi1 $(FLAGS) $(CONFIG1) diffusion2d_striped.c $(LIB_GD)

mpi1.mp4: mpi1
	rm -f parout/out* mpi1.mp4
	$(MPIRUN) -n 4 ./mpi1
	mv parout/out.gif parout/out_mpi1.gif
	ls
	$(FFMPEG) -i parout/out_mpi1.gif $(MOVOPTS) mpi1.mp4

mpi2: diffusion2d_striped.c
	$(MPICC) -o mpi2 $(FLAGS) $(CONFIG2) diffusion2d_striped.c $(LIB_GD)

mpi2.mp4: mpi2
	rm -f parout/out* mpi2.mp4
	$(MPIRUN) -n 4 ./mpi2
	mv parout/out.gif parout/out_mpi2.gif
	ls
	$(FFMPEG) -i parout/out_mpi2.gif $(MOVOPTS) mpi2.mp4


mpi3: diffusion2d_striped.c
	$(MPICC) -o mpi3 $(FLAGS) $(CONFIG3) diffusion2d_striped.c $(LIB_GD)

mpi3.mp4: mpi3
	rm -f parout/out* mpi3.mp4
	$(MPIRUN) -n 4 ./mpi3
	mv parout/out.gif parout/out_mpi3.gif
	ls
	$(FFMPEG) -i parout/out_mpi3.gif $(MOVOPTS) mpi3.mp4

######################### Hybrid Version #########################

hbd1: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd1 $(FLAGS) -DNT=40 $(CONFIG1) diffusion2d_mpi_omp.c $(LIB_GD)

hbd1.mp4: hbd1
	rm -f parout/out* hbd1.mp4
	$(MPIRUN) -n 4 ./hbd1
	mv parout/out.gif parout/out_hbd1.gif
	ls
	$(FFMPEG) -i parout/out_hbd1.gif $(MOVOPTS) hbd1.mp4

hbd3_40_1: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd3_40_1 $(FLAGS) -DNT=1 $(CONFIG3) diffusion2d_mpi_omp.c $(LIB_GD)

hbd3_20_2: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd3_20_2 $(FLAGS) -DNT=2 $(CONFIG3) diffusion2d_mpi_omp.c $(LIB_GD)

hbd3_10_4: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd3_10_4 $(FLAGS) -DNT=4 $(CONFIG3) diffusion2d_mpi_omp.c $(LIB_GD)

hbd3_2_20: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd3_2_20 $(FLAGS) -DNT=20 $(CONFIG3) diffusion2d_mpi_omp.c $(LIB_GD)

hbd3_1_40: diffusion2d_mpi_omp.c
	$(HBDCC) -o hbd3_1_40 $(FLAGS) -DNT=40 $(CONFIG3) diffusion2d_mpi_omp.c $(LIB_GD)



hybrid_40_1: hbd3_40_1
	$(MPIRUN) -n 40 ./hbd3_40_1

hybrid_20_2: hbd3_20_2
	$(MPIRUN) -n 20 ./hbd3_20_2

hybrid_10_4: hbd3_10_4
	$(MPIRUN) -n 10 ./hbd3_10_4

hybrid_2_20: hbd3_2_20
	$(MPIRUN) -n 2 ./hbd3_2_20

hybrid_1_40: hbd3_1_40
	$(MPIRUN) -n 1 ./hbd3_1_40

hybrid_all: hbd3_40_1 hbd3_20_2 hbd3_10_4 hbd3_2_20 hbd3_1_40
	OMP_NUM_THREADS=1 $(MPIRUN) -n 40 -c 1 ./hbd3_40_1
	OMP_NUM_THREADS=2 $(MPIRUN) -n 20 -c 2 ./hbd3_20_2
	OMP_NUM_THREADS=4 $(MPIRUN) -n 10 -c 4 ./hbd3_10_4
	OMP_NUM_THREADS=20 $(MPIRUN) -n 2 -c 20 ./hbd3_2_20
	OMP_NUM_THREADS=40 $(MPIRUN) -n 1 -c 40 ./hbd3_1_40


## Checkerboard



clean:
	rm -f *.mp4 *1 *2 *3 *.o hbd* *~ parout/*

