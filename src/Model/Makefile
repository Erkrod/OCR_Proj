
clean:
	-rm -f test*.ppm
	-rm -f *.o

TestIsolate: DIPs.o FileIO.o IsolateCharacter.o Image.o ImageList.o TestIsolateCharacter.o
	gcc -o TestIsolateCharacter DIPs.o FileIO.o IsolateCharacter.o Image.o ImageList.o TestIsolateCharacter.o	

TestIsolateGDB: DIPsGDB.o FileIOGDB.o IsolateCharacterGDB.o ImageGDB.o ImageListGDB.o TestIsolateCharacterGDB.o
	gcc -o TestIsolateCharacter DIPs.o FileIO.o IsolateCharacter.o Image.o ImageList.o TestIsolateCharacter.o -g

TestIsolateCharacter.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h TestIsolateCharacter.c
	gcc -c TestIsolateCharacter.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

IsolateCharacter.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h IsolateCharacter.c
	gcc -c IsolateCharacter.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

DIPs.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/DIPs.h DIPs.c
	gcc -c DIPs.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

FileIO.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/FileIO.h FileIO.c /home/group1/EECS22L/EECS22L_Project2/inc/Model/Image.h
	gcc -c FileIO.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

Image.o: Image.c /home/group1/EECS22L/EECS22L_Project2/inc/Model/Image.h
	gcc -c Image.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

ImageList.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/ImageList.h ImageList.c
	gcc -c ImageList.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

TestIsolateCharacterGDB.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h TestIsolateCharacter.c
	gcc -g -c TestIsolateCharacter.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

IsolateCharacterGDB.o: IsolateCharacter.c /home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h
	gcc -g -c IsolateCharacter.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

DIPsGDB.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/DIPs.h DIPs.c
	gcc -c DIPs.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

FileIOGDB.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/FileIO.h FileIO.c /home/group1/EECS22L/EECS22L_Project2/inc/Model/Image.h
	gcc -g -c FileIO.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

ImageGDB.o: Image.c /home/group1/EECS22L/EECS22L_Project2/inc/Model/Image.h
	gcc -g -c Image.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model

ImageListGDB.o: /home/group1/EECS22L/EECS22L_Project2/inc/Model/ImageList.h ImageList.c
	gcc -g -c ImageList.c -I /home/group1/EECS22L/EECS22L_Project2/inc/Model