src_dir=../src/
test_dir=../test/
out_dir=../out/

ScreenRenderer.o: $(src_dir)ScreenRenderer.cpp $(src_dir)ScreenRenderer.h
	g++ -c $< -o $(out_dir)$@

MainGame.o: $(src_dir)MainGame.cpp $(src_dir)MainGame.h
	g++ -c $< -o  $(out_dir)$@

Pokemon.o: $(src_dir)Pokemon.cpp $(src_dir)Pokemon.h
	g++ -c $< -o  $(out_dir)$@

main_test.o: $(test_dir)main_test.cpp
	g++ -c $< -o  $(out_dir)$@

game.exe: MainGame.o ScreenRenderer.o Pokemon.o main_test.o
	g++ $^ -o $(out_dir)$@
