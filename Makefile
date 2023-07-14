myshell: myshell.o parse.o  
	g++ -Wall -o $@ $^

myshell.o: myshell.cpp
	g++ -Wall -c $^

parse.o: parse.cpp
	g++ -Wall -c $^

clean:
	rm -f *.o myshell