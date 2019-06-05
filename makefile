run: isingmodel.x
	./isingmodel.x;
	./autoko.x;

all: isingmodel.x autoko.x binder.x makeStartfile.x

binder.x: binder.cpp constanten.h
	g++ binder.cpp -o binder.x;

isingmodel.x: main.cpp *.h
	g++ main.cpp -o isingmodel.x;

autoko.x: autoko.cpp
	g++ autoko.cpp -o autoko.x;

makeStartfile.x: makeStartfile.cpp constanten.h
	g++ makeStartfile.cpp -o makeStartfile.x;

clean:
	rm *.x;
