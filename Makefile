app: main.o add_content.o create.o display.o search.o choices.o utilities.o gameplay.o
	gcc -o app main.o add_content.o create.o display.o search.o choices.o utilities.o gameplay.o

main.o: main.c
	gcc -c main.c

add_content.o: add_content.c
	gcc -c add_content.c

create.o: create.c
	gcc -c create.c

display.o: display.c
	gcc -c display.c   

gameplay.o: gameplay.c
	gcc -c gameplay.c

search.o : search.c
	gcc -c search.c

choices.o : choices.c
	gcc -c choices.c

utilities.o : utilities.c
	gcc  -c utilities.c

clean:
	rm -f *.o myprogram