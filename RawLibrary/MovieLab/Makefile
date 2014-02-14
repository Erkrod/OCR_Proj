#####################################################
# Makefile: Makefile for Assignment5 EECS22 Fall2011
#
# 10/10/11 Weiwei Chen: initial solution version                  
#
#####################################################

# design names
DESIGN = MovieLab
MOVIES = out.yuv juliaset.yuv
CC = gcc
#DEBUG = -g -DDEBUG 
DEBUG = -O2
CFLAGS = -ansi -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) -lm

all: MovieLab

#target to generate Image.o
Image.o: Image.h Image.c
	$(CC) $(CFLAGS) -c Image.c -o Image.o

#target to generate ImageList.o
ImageList.o: ImageList.h ImageList.c
	$(CC) $(CFLAGS) -c ImageList.c -o ImageList.o

#target to generate Movie.o
Movie.o: Movie.h Movie.c
	$(CC) $(CFLAGS) -c Movie.c -o Movie.o

#target to generate PhotoLab.o
MovieLab.o: MovieLab.c
	$(CC) $(CFLAGS) -c MovieLab.c -o MovieLab.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c
	$(CC) $(CFLAGS) -c DIPs.c -o DIPs.o

MovieLab: MovieLab.o Image.o ImageList.o Movie.o DIPs.o
	$(CC) $(LFLAGS) MovieLab.o  Image.o ImageList.o Movie.o DIPs.o -o MovieLab


memcheck: MovieLab
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -bw
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -vflip
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -hmirror
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -edge
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -sharp
	valgrind --leak-check=full MovieLab -i anteater -o out1 -f 150 -s 352x288 -cut 1-80
	valgrind --leak-check=full MovieLab -i anteater -o out2 -f 150 -s 352x288 -cut 81-150
	valgrind --leak-check=full MovieLab -i out1 -cat out2 -o out -f 80 -fcat 70 -s 352x288
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -fast 3
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -resize 50
	valgrind --leak-check=full MovieLab -i anteater -o out -f 150 -s 352x288 -rvs

play:
	~eecs22/bin/yay -s 352x288 out.yuv &
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(MOVIES)
    
