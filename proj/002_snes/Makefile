all: snes

snes: snes.o nvme_base.o 
		g++ snes.o nvme_base.o -o snes

snes.o: snes.cpp snes.h 
		g++ -c snes.cpp snes.h

nvme_base.o: nvme_base.cpp nvme_base.h  
		g++ -c nvme_base.cpp nvme_base.h

clean:
		rm snes
		rm -rf ./*.o
		rm -rf ./*.gch