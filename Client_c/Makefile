CC=clang
CFLAGS=-g -Wall -Wextra -Werror

EXEC=client-introduction client-tutoriel client-interactif client-TUTORIEL crypteMove BayOfPigs projetX planB oneMillion crypteSeq Northwood decrypteSeq LostCause oneMillion

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

client-TUTORIEL: client-TUTORIEL.o client.o

client-introduction: client-introduction.o client.o

client.o: client.c client.h

crypteMove.o: crypteMove.c crypteMove.h

crypteMove: crypteMove.o client.o

BayOfPigs: BayOfPigs.o client.o

projetX: projetX.o client.o

planB: planB.o client.o 

oneMillion: oneMillion.o client.o 
 
crypteSeq: crypteSeq.o client.o 

decrypteSeq: decrypteSeq.o client.o

Northwood: Northwood.o client.o

LostCause: LostCause.o client.o

oneMillion: oneMillion.o client.o

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
