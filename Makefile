build: compile link clean
compile:
	g++ -c -g main.cpp $(wildcard Source/PhysicsEngine/*.cpp)  $(wildcard Source/PhysicsEngine/Managers/*.cpp) $(wildcard Source/PhysicsEngine/Components/*.cpp)  Source/mario.cpp Source/enemy.cpp  -I.\libraries\SFML-2.6.1\include -DSFML_STATIC

link:
	g++ $(wildcard *.o) -o main.exe -L.\libraries\SFML-2.6.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
run: build
	./main

debug: build
	gdb -x debug.gdb main.exe

clean: 
	rm *.o