all: dev

.PHONY: all

exe = GetCrunked

bin:
	@echo "building directory $@"
	mkdir -p $@


bin/main.o: src/main.cpp | bin
	@echo building $@
	g++ -o $@ -c $^ -IC:\dev\libraries\SFML\include -Iinclude


dev: bin/main.o | bin
	@echo building dev
	g++ -o bin/${exe} $^ -LC:\dev\libraries\SFML\lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lfreetype -lopengl32 -lwinmm -lgdi32


release: bin/main.o | bin
	@echo building release
	g++ -o bin/${exe} $^ res/my.res -LC:\dev\libraries\SFML\lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lfreetype -lopengl32 -lwinmm -lgdi32 -mwindows -O2


portable: release
	@echo creating portable
	@cp -r bin/ portable/
	@cp -r res/ portable/res/


run:
	@printf "\n\n"
	@echo "Running:"
	@echo "=================================="
	@bin/${exe}
	@echo "=================================="
	@printf "\n\n"



clean:
	@echo cleaning...
	rm -f bin/*.o
	rm -f bin/*.exe
