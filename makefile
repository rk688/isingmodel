run: isingmodel.x
	./isingmodel.x;
	./autoko.x;

all: isingmodel.x autoko.x

isingmodel.x: main.cpp *.h
	g++ main.cpp -o isingmodel.x;

autoko.x: autoko.cpp
	g++ autoko.cpp -o autoko.x;

clean:
	rm *.x;
