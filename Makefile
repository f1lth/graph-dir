all: graph

graph: graph.c
	gcc -o graph graph.c

clean:
	rm graph

