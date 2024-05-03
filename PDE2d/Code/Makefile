all: 
	gcc main.c 2dFourierApprox.c -lm -o app
nm:
	gcc pcalculation.c -lm -o nm

clean:
	rm -rf *.o vector

gr:
	chmod +x printAll.gpi
	./printAll.gpi

grnm:
	chmod +x printDependence.gpi
	./printDependence.gpi