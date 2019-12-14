include ../../config/constants.mk

.PHONY: all
all: test_small

mat_seq : matrix.c
	$(CC) -o mat_seq matrix.c $(LIB_MATH)

mat_seq_time: matrix.c 
	$(CC) -o mat_seq_time -DTIME matrix.c $(LIB_MATH)

seq_time: mat_seq_time
	$(RUN) ./mat_seq_time 10000 10000

.PHONY: seq
seq : mat_seq
	$(RUN) ./mat_seq 64 64

mat_cu : matrix.cu
	$(NVCC) -o mat_cu matrix.cu $(LIB_MATH)

mat_cu_time: matrix.cu
	$(NVCC) -o mat_cu_time -DTIME matrix.cu $(LIB_MATH)

.PHONY: cuda
cuda : mat_cu
	$(CUDA_RUN) ./mat_cu 64 64

cuda_time: mat_cu_time
	$(CUDA_RUN) ./mat_cu_time 10000 10000

.PHONY: test_small
test_small : mat_seq mat_cu
	$(RUN) ./mat_seq 64 64 > seq.out
	$(CUDA_RUN) ./mat_cu 64 64 > cuda.out
	ls
	diff seq.out cuda.out

test_big : mat_seq mat_cu
	$(RUN) ./mat_seq 10000 10000 > seq.out
	$(CUDA_RUN) ./mat_cu 10000 10000 > cuda.out
	ls
	diff seq.out cuda.out


.PHONY: clean
clean : 
	rm -f mat_* *~ *.out
