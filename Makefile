LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -I/usr/include/SDL2

PLAYER_CLASS = -c Player.cpp -o Player.o
MAPBLOCKS_CLASS = -c MapBlocks.cpp -o MapBlocks.o
BULLET_CLASS = -c bullet.cpp -o bullet.o
ENEMY_CLASS = -c enemy.cpp -o enemy.o
GAMEOVER_CLASS = -c GameOver.cpp -o GameOver.o
STARTSCREEN_CLASS = -c StartScreen.cpp -o StartScreen.o
CAVESYSTEM_CLASS = -c CaveSystem.cpp -o CaveSystem.o
TEXT_CLASS = -c text.cpp -o text.o
KAMIKAZE_CLASS = -c Kamikaze.cpp -o Kamikaze.o
MISSILE_CLASS = -c missile.cpp -o missile.o
BOSS_CLASS = -c Boss.cpp -o Boss.o
INFOSCREEN_CLASS= -c InfoScreen.cpp -o InfoScreen.o

INCLUDED_CLASSES = CaveSystem.cpp Player.cpp MapBlocks.cpp bullet.cpp enemy.cpp StartScreen.cpp GameOver.cpp text.cpp Kamikaze.cpp missile.cpp DifficultySelectionScreen.cpp Boss.cpp InfoScreen.cpp
BRANDON_LIB = -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_mixer -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
JERRY_WIN = -lSDL2 -lSDL2_image -lSDL2_ttf -LC:\wingw_dev_lib\i686-w64-mingw32\bin -LC:\wingw_dev_lib\SDL2-2.0.10\x86_64-w64-mingw32\lib -IC:\wingw_dev_lib\SDL2-2.0.10\x86_64-w64-mingw32\include\SDL2

all: SDLCredits.cpp game_loop.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -o game_loop $(LINKER_FLAGS)

dilan: SDLCredits.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_mixer -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 -o game_loop.o

connor: SDLCredits.cpp game_loop.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits
	g++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -std=c++11 -o game_loop

tc: SDLCredits.cpp game_loop.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -o game_loop $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib

jerryWin: game_loop.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -o game_loop $(JERRY_WIN)


jlg: game_loop.cpp
	clang++ $(LINKER_FLAGS) $(PLAYER_CLASS)
	clang++ $(LINKER_FLAGS) $(MAPBLOCKS_CLASS)
	clang++ $(LINKER_FLAGS) $(BULLET_CLASS)
	clang++ $(LINKER_FLAGS) $(ENEMY_CLASS)
	clang++ $(LINKER_FLAGS) $(GAMEOVER_CLASS)
	clang++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -o game


jlet: test_enemy_move.cpp
	clang++ $(LINKER_FLAGS) $(PLAYER_CLASS)
	clang++ $(LINKER_FLAGS) $(MAPBLOCKS_CLASS)
	clang++ $(LINKER_FLAGS) $(BULLET_CLASS)
	clang++ $(LINKER_FLAGS) $(ENEMY_CLASS)
	clang++ $(LINKER_FLAGS) $(GAMEOVER_CLASS)
	clang++ $(INCLUDED_CLASSES) test_enemy_move.cpp $(LINKER_FLAGS)  -o enemy_test

brian: SDLCredits.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o game_loop



brandon: SDLCredits.cpp game_loop.cpp
	g++ $(PLAYER_CLASS) $(BRANDON_LIB)
	g++ $(BULLET_CLASS) $(BRANDON_LIB)
	g++ $(CAVESYSTEM_CLASS) $(BRANDON_LIB)
	g++ $(ENEMY_CLASS) $(BRANDON_LIB)
	g++ $(GAMEOVER_CLASS) $(BRANDON_LIB)
	g++ $(MAPBLOCKS_CLASS) $(BRANDON_LIB)
	g++ $(TEXT_CLASS) $(BRANDON_LIB)
	g++ $(KAMIKAZE_CLASS) $(BRANDON_LIB)
	g++ $(BOSS_CLASS) $(BRANDON_LIB)
	g++ $(INCLUDED_CLASSES) game_loop.cpp $(BRANDON_LIB) -o game_loop

brandon_enemy: test_enemy_move.cpp
	g++ -c brandon_enemy.cpp -o brandon_enemy.o -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
	g++ $(INCLUDED_CLASSES) brandon_enemy.o test_enemy_move.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o test_enemy_move

jake: SDLCredits.cpp game_loop.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -lSDL2_mixer -std=c++11 -o game_loop

boss_test: boss_test.cpp
	g++ $(PLAYER_CLASS) $(BRANDON_LIB)
	g++ $(BULLET_CLASS) $(BRANDON_LIB)
	g++ $(CAVESYSTEM_CLASS) $(BRANDON_LIB)
	g++ $(ENEMY_CLASS) $(BRANDON_LIB)
	g++ $(GAMEOVER_CLASS) $(BRANDON_LIB)
	g++ $(MAPBLOCKS_CLASS) $(BRANDON_LIB)
	g++ $(TEXT_CLASS) $(BRANDON_LIB)
	g++ $(KAMIKAZE_CLASS) $(BRANDON_LIB)
	g++ $(BOSS_CLASS) $(BRANDON_LIB)
	g++ $(INCLUDED_CLASSES) boss_test.cpp $(BRANDON_LIB) -o boss_test

cleanjake:
	rm game_loop
	rm highscore*

clean:
	rm *.o

winClean:
	erase *.o
	erase game_loop.exe
