build: compile link clean
compile:
	g++ -c main.cpp $(wildcard Source/PhysicsEngine/*.cpp)  $(wildcard Source/PhysicsEngine/Managers/*.cpp) $(wildcard Source/PhysicsEngine/Components/*.cpp)  $(wildcard Source/*.cpp) -I.\libraries\SFML-2.6.1\include -DSFML_STATIC

link:
	g++ $(wildcard *.o) -o main.exe -L.\libraries\SFML-2.6.1\lib -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lvorbisfile -lvorbis -lvorbisenc -lopengl32 -lopenal32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main -lflac -logg
run: build
	./main

debug: build
	gdb -x debug.gdb main.exe

clean: 
	rm *.o