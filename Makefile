all:
	g++ main.cpp -o main.exe -DSFML_STATIC -I C:\SFML\include -L C:\SFML_build\lib -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 