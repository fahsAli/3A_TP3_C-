compiler        = g++
files       = product.cpp client.cpp command.cpp shop.cpp program.cpp main.cpp

all: compile

compile: $(files)
	$(compiler) $(files) 

clean:
	rm -f a.out

exe:
	./a.out

