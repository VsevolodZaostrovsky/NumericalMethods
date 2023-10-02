all: 
	gcc main.c Solution.c -lm -o app

t1: 
	gcc t1tests.c Solution.c -lm -o t1

nm:
	gcc pcalculation.c -lm

clean:
	rm -rf *.o vector

gr:
	chmod +x printAll.gpi
	./printAll.gpi

grnm:
	chmod +x printDependence.gpi
	./printDependence.gpi