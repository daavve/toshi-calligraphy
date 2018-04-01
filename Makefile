CFLAGS		= -march=native -mtune=native -mfpmath=sse -Wall -Wextra -O2
LFLAGS		= -lopencv_highgui -lopencv_core

all:		main.o ex-header.o locate_char.o dct.o
			gcc -o toshi-segment main.o ex-header.o locate_char.o dct.o $(LFLAGS)

main.o:		header.h main.c
			gcc -c -o main.o main.c $(CFLAGS)

ex-header.o:	header.h ex-header.c
				gcc -c -o ex-header.o ex-header.c $(CFLAGS)

locate_char.o:	header.h locate_char.c
				gcc -c -o locate_char.o locate_char.c 

dct.o:			dct.c header.h
				gcc -c -o dct.o dct.c $(CFLAGS)
				
clean:		
			rm *.o

# Note:  gcc -c means create object file
