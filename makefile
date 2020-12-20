all: project3.out
project3.out: main.cpp avl.cpp
		g++ main.cpp avl.cpp -o project3.out
clean:
		rm project3.out