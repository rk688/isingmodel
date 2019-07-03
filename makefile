run: isingmodel.x binder.x
	./isingmodel.x;
	./binder.x;

all: isingmodel.x autoko.x binder.x makeStartfile.x

binder.x: binder.cpp *.h
	g++ -std=c++11 binder.cpp -o binder.x;

isingmodel.x: main.cpp *.h
	g++ -std=c++11 main.cpp -o isingmodel.x;

autoko.x: autoko.cpp
	g++ -std=c++11 autoko.cpp -o autoko.x;

makeStartfile.x: makeStartfile.cpp constanten.h
	g++ -std=c++11 makeStartfile.cpp -o makeStartfile.x;

clean:
	rm *.x;
