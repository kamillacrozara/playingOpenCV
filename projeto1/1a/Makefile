all: projeto1a.cpp
	g++ `pkg-config opencv --cflags` projeto1a.cpp -o bin/projeto1a `pkg-config opencv --libs`

clean:
	$(RM) -R bin/
