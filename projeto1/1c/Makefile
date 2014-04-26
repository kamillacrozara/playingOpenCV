all: projeto1c.cpp 
	mkdir bin/
	g++ `pkg-config opencv --cflags` projeto1c.cpp -o bin/projeto1c `pkg-config opencv --libs`

clean:
	$(RM) -R bin/
