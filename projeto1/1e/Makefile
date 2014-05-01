all: projeto1e.cpp 
	$(RM) -R bin/
	$(RM) -R result/
	mkdir bin/
	mkdir result/
	g++ `pkg-config opencv --cflags` projeto1e.cpp -o bin/projeto1e `pkg-config opencv --libs` -std=c++11

clean:
	$(RM) -R bin/
	$(RM) -R result/