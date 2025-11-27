run: obj/Trojan.o obj/confirm.o obj/opnPrt.o obj/rs.o
	@mkdir -p bin
	gcc obj/Trojan.o obj/confirm.o obj/opnPrt.o obj/rs.o -o ./bin/run

obj/Trojan.o: src/Trojan.c inc/headers.h
	@mkdir -p obj
	gcc -I inc/ -c src/Trojan.c -o obj/Trojan.o

obj/confirm.o: src/confirm.c inc/headers.h
	gcc -I inc/ -c src/confirm.c -o obj/confirm.o
	
obj/opnPrt.o: src/opnPrt.c inc/headers.h
	gcc -I inc/ -c src/opnPrt.c -o obj/opnPrt.o
	
obj/rs.o: src/rs.c inc/headers.h
	gcc -I inc/ -c src/rs.c -o obj/rs.o

clean:
	rm obj/*.o ./bin/run
