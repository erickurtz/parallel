CC = cc -pedantic -std=c11
LINKS = -lm -lpthread


run1 : bank
	./bank 53.25 5 7
bank : bank.c
	$(CC) -o bank bank.c $(LINKS)

run2: bank2
	./bank2 53.25 5 7

bank2: bank2.c
	$(CC) -o bank2 bank2.c $(LINKS)

debug_run2: bank2
	valgrind --leak-check=full  --show-leak-kinds=all --track-origins=yes  --log-file=valgrind-out.txt ./bank2 52.50 5 7 


clean :
	rm -f bank bank2 *~ 
