run: isingmodel.x
	./isingmodel.x;
	./autoko.x;

all: isingmodel.x autoko.x binder.x makeStartfile.x

binder.x: binder.cpp constanten.h analyse.h
	g++ binder.cpp -std=c++11 -o binder.x;

isingmodel.x: main.cpp *.h
	g++ main.cpp -std=c++11 -o isingmodel.x;

autoko.x: autoko.cpp
	g++ autoko.cpp -std=c++11 -o autoko.x;

makeStartfile.x: makeStartfile.cpp constanten.h
	g++ makeStartfile.cpp -std=c++11 -o makeStartfile.x;

clean:
	rm *.x;
