all: projeto1b_c.cpp
	g++ `pkg-config opencv --cflags` projeto1b_c.cpp -o projeto1b_c `pkg-config opencv --libs`

clean:
	$(RM) projeto1b_c
	$(RM) baboon_*
	$(RM) lena_*
