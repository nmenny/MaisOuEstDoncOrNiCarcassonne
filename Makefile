CPP= g++ -Wall -o

sources= src/Joueurs.cpp src/Joueur.cpp src/Main.cpp src/Pres.cpp src/Pioche.cpp
objets= $(sources:.cpp=.o)

jeu: $(objets)
	$(CPP) $@ $^


%.o : %.cpp
	$(CPP) $@ -c $<


clean:
	rm src/*.o
	rm jeu