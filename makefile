fullRun: makeStartfile.x
	./makeStartfile.x;
	make run;

run: isingmodel.x messgroessen.x
	./isingmodel.x;
	./messgroessen.x;

all: isingmodel.x autoko.x messgroessen.x makeStartfile.x auswertung.x

messgroessen.x: messgroessen.cpp *.h
	g++ -std=c++11 messgroessen.cpp -o messgroessen.x;

isingmodel.x: main.cpp *.h
	g++ -std=c++11 main.cpp -o isingmodel.x;

autoko.x: autoko.cpp
	g++ -std=c++11 autoko.cpp -o autoko.x;

makeStartfile.x: makeStartfile.cpp constanten.h
	g++ -std=c++11 makeStartfile.cpp -o makeStartfile.x;

auswertung.x: auswertung.cpp constanten.h analyse.h
	g++ -std=c++11 auswertung.cpp -o auswertung.x

clean:
	rm *.x;
