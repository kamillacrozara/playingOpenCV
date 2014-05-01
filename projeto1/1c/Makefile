all: projeto1c.cpp 
	$(RM) -R bin/
	$(RM) -R gaussianResult/
	mkdir bin/
	mkdir gaussianResult/
	g++ `pkg-config opencv --cflags` projeto1c.cpp -o bin/projeto1c `pkg-config opencv --libs`

clean:
	$(RM) -R bin/
	$(RM) -R gaussianResult/
