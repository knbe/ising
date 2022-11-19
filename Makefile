files = main.c

run : $(files)
	cc $(files) -lm
