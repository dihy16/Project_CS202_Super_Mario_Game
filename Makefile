build: compile link clean
compile:
	g++ -c main.cpp $(wildcard Source/*.cpp)  -I.\libraries\SFML-2.6.1\include -DSFML_STATIC

link:
	g++ $(wildcard *.o) -o main.exe -L.\libraries\SFML-2.6.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
run: build
	./main

debug: build
	gdb -x debug.gdb main.exe

neat:
	rm *.o

clean: 
	rm *.o