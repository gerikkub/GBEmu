BUILDPREFIX := build/
SOURCEPREFIX := source/

TARGET := main.exe
CFLAGS := -g -fvisibility=hidden -Wpointer-arith -Winit-self\
 -Wformat-nonliteral -Werror -W -Wall -Wno-unused-parameter -Ofast\
 -Wno-unused-function
LINUX := 1
OBJECTS := $(BUILDPREFIX)instruction_count.o $(BUILDPREFIX)timer.o $(BUILDPREFIX)joypad.o $(BUILDPREFIX)dma.o $(BUILDPREFIX)video.o $(BUILDPREFIX)mem.o $(BUILDPREFIX)core.o $(BUILDPREFIX)instructions.o \
		$(BUILDPREFIX)io.o $(BUILDPREFIX)main.o

all: $(TARGET) $(BUILD)
	
#	gcc -c main.c -o $(BUILDPREFIX)main.o $(CFLAGS)
#	gcc -c instructions.c -o $(BUILDPREFIX)instructions.o $(CFLAGS)
#	gcc -c core.c -o $(BUILDPREFIX)core.o $(CFLAGS)
#	gcc -c mem.c -o $(BUILDPREFIX)mem.o	 $(CFLAGS)
#	gcc -c io.c -o $(BUILDPREFIX)io.o	 $(CFLAGS)
#	gcc -c video.c -o $(BUILDPREFIX)video.o	 $(CFLAGS)
#	gcc -c dma.c -o $(BUILDPREFIX)dma.o	 $(CFLAGS)	
#	gcc -c joypad.c -o $(BUILDPREFIX)joypad.o	 $(CFLAGS)	
#	gcc -c timer.c -o $(BUILDPREFIX)timer.o	 $(CFLAGS)	
	
	
$(TARGET): $(OBJECTS)
	gcc -o main $(OBJECTS) -lmingw32 -lSDLmain -lSDL
	
$(BUILDPREFIX)%.o: $(SOURCEPREFIX)%.c
	gcc -c $< -o $@ $(CFLAGS)
	
linux: $(OBJECTS)
	gcc -o main $(OBJECTS) -lSDL

tetris:
	./main tetris.gb dump.bin reg.txt
	
tennis:
	./main tennis.gb dump.bin reg.txt
	
kirby:
	main.exe "Kirby's Dream Land.gb" dump.bin reg.txt
	
pokemon:
	main pokemon.gb dump.bin reg.txt
	
mario:
	main "Super Mario Land.gb" dump.bin reg.txt

test:
	main test.gb dump.bin reg.txt
	
runlinux:
	./main tetris.gb dump.bin reg.txt

refreshROM:
	cp ../../ROMs/GBC/Tetris.gb ./tetris.gb	
	
debug:
	gdb main.exe

debugLinux:
	gdb ./main
	
clean:
	rm $(BUILDPREFIX)*
