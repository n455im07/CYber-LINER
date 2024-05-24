app: Objects/main.o Objects/add_content.o Objects/create.o Objects/display.o \
     Objects/search.o Objects/choices.o Objects/utilities.o Objects/gameplay.o
	gcc -o app Objects/main.o Objects/add_content.o Objects/create.o \
	    Objects/display.o Objects/search.o Objects/choices.o \
	    Objects/utilities.o Objects/gameplay.o

Objects/main.o: main.c
	gcc -c main.c -o Objects/main.o

Objects/add_content.o: add_content.c
	gcc -c add_content.c -o Objects/add_content.o

Objects/create.o: create.c
	gcc -c create.c -o Objects/create.o

Objects/display.o: display.c
	gcc -c display.c -o Objects/display.o

Objects/gameplay.o: gameplay.c
	gcc -c gameplay.c -o Objects/gameplay.o

Objects/search.o: search.c
	gcc -c search.c -o Objects/search.o

Objects/choices.o: choices.c
	gcc -c choices.c -o Objects/choices.o

Objects/utilities.o: utilities.c
	gcc -c utilities.c -o Objects/utilities.o

clean:
	rm -f Objects/*.o app
