all: ScaleImage.cpp 
	mkdir bin/
	mkdir resizedImages/
	mkdir rescaledImages/
	mkdir requantizedImages/
	g++ `pkg-config opencv --cflags` ScaleImage.cpp -o bin/ScaleImage `pkg-config opencv --libs`

clean:
	$(RM) -R bin/
	$(RM) -R resizedImages/
	$(RM) -R rescaledImages/
	$(RM) -R requantizedImages/