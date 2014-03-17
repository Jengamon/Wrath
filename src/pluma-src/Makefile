all: compile link

compile:
	g++ -I../../include -c -fPIC *.cpp

link:
	g++ -shared  *.o -ldl -o libpluma.so

clean:
	rm *.o libpluma.so