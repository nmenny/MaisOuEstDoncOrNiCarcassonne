CPP= g++ -Wall -o

sources= src/Abbayes.cpp src/Jardins.cpp src/Jeu.cpp src/Joueur.cpp src/Joueurs.cpp src/Main.cpp src/Pioche.cpp src/Plateau.cpp src/Pres.cpp src/Rivieres.cpp src/Routes.cpp src/Tuile.cpp src/Villes.cpp
objets= $(sources:.cpp=.o)

jeu: $(objets)
	$(CPP) $@ $^


%.o : %.cpp
	$(CPP) $@ -c $<


clean:
	rm src/*.o
	rm jeu
