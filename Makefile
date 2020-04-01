ScreenRenderer.o: ScreenRenderer.cpp ScreenRenderer.h
	g++ -c $<

MainGame.o: MainGame.cpp MainGame.h
	g++ -c $<

game.exe: MainGame.o ScreenRenderer.o
	g++ $^ -o $@
