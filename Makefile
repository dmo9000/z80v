all: z80v

OBJS=z80.o sysbus.o main.o  

z80v: z80opmap.h $(OBJS)
	gcc -o z80v $(OBJS)

z80opmap.h: opcode.map mkopmap.pl
	./mkopmap.pl < opcode.map > z80opmap.h

clean:
	rm -f *.stackdump *.o main z80v z80opmap.h
