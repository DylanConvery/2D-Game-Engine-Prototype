build:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o .\bin\debug\debug \
	-I"C:\DevelopmentLibraries\SDL2\include" \
	-L"C:\DevelopmentLibraries\SDL2\lib" \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-lmingw32 \
	-lSDL2main \
	-llua \
	-lSDL2 \
	-lSDL2_ttf \
	-lSDL2_image \
	-lSDL2_mixer

clean:
	rm ./bin/debug/debug

run:
	./bin/debug/debug
