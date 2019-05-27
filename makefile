run: isingmodel.x
	./isingmodel.x;

all: isingmodel.x

isingmodel.x: main.cpp *.h
	g++ main.cpp -o isingmodel.x;

clean:
	rm *.x;
