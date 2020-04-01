ScreenRenderer.o: ScreenRenderer.cpp ScreenRenderer.h
	g++ -c $<

MainGame.o: MainGame.cpp MainGame.h
	g++ -c $<

Pokemon.o: Pokemon.cpp Pokemon.h
	g++ -c $<

main_test.o: main_test.cpp
	g++ -c $<

game.exe: MainGame.o ScreenRenderer.o Pokemon.o main_test.o
	g++ $^ -o $@
