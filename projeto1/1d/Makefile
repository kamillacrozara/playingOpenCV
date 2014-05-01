all: projeto1d.cpp 
	$(RM) -R bin/
	$(RM) -R result/
	mkdir bin/
	mkdir result/
	g++ `pkg-config opencv --cflags` projeto1d.cpp -o bin/projeto1d `pkg-config opencv --libs` -std=c++11

clean:
	$(RM) -R bin/
	$(RM) -R result/
