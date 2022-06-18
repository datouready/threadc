pro	:	main.cpp
	g++ -o pro mythread.cpp main.cpp -lpthread
run : pro
	./pro