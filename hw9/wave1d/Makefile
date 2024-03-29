# Makefile for wave1d : 1-dimensional wave equation simulator
include ../../config/constants.mk

NAME = wave1d

# Converts an animated GIF out.gif to an MPEG-4 movie video.mp4
MOVOPTS = -movflags faststart -pix_fmt yuv420p -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2"

# The following will take a 20 fps movie and speed it up 3x without
# dropping frames, yielding a 60 fps movie which is 1/3 as long:
# ffmpeg -i video.mp4 -r 60 -filter:v "setpts=0.333333333*PTS" output.mp4

clean:
	rm -f *.exec *.gif *~ gdtest *.tmp a.out *.mp4
	rm -f specout/out*


######################### Sequential Version #########################

seq.exec:
	$(CC) -std=c11 -o seq.exec $(NAME).c $(LIB_GD) $(LIB_MATH)

seqdebug.exec:
	$(CC) -std=c11 -o seqdebug.exec $(NAME).c -DDEBUG $(LIB_GD) $(LIB_MATH)

s0.gif: seq.exec config0.txt
	rm -f seqout/out*
	rm -f s0.gif
	$(RUN) ./seq.exec config0.txt s0.gif

s1.gif: seq.exec config1.txt
	rm -f seqout/out*
	rm -f s1.gif
	$(RUN) ./seq.exec config1.txt s1.gif

s1.mp4: s1.gif
	rm -f s1.mp4
	$(FFMPEG) -i s1.gif $(MOVOPTS) s1.mp4

s2.gif: seq.exec config2.txt
	rm -f seqout/out*
	rm -f s2.gif
	$(RUN) ./seq.exec config2.txt s2.gif

s2.mp4: s2.gif
	rm -f s2.mp4
	$(FFMPEG) -i s2.gif $(MOVOPTS) s2.mp4

######################### CUDA Version #########################

cuda.exec:
	$(NVCC) -o cuda.exec $(NAME).cu $(LIB_GD) $(LIB_MATH)

cudadebug.exec: 
	$(NVCC) -o cudadebug.exec $(NAME).cu -DDEBUG $(LIB_GD) $(LIB_MATH) 

cu0.gif: cuda.exec config0.txt
	rm -f parout/out*
	rm -f cu0.gif
	$(CUDARUN) ./cuda.exec config0.txt cu0.gif

cu1.gif: cuda.exec config1.txt
	rm -f parout/out*
	rm -f cu1.gif
	$(CUDARUN) ./cuda.exec config1.txt cu1.gif

cu2.gif: cuda.exec config2.txt
	rm -f parout/out*
	rm -f cu2.gif
	$(CUDARUN) ./cuda.exec config2.txt cu2.gif

###########DEBUG#####################

cu4.gif: cuda.exec config4.txt
	rm -f parout/out*
	rm -f cu4.gif 
	$(CUDARUN) ./cuda.exec config4.txt cu4.gif 

s4.gif: seq.exec config4.txt 
	$(RUN) ./seq.exec config4.txt s4.gif 
