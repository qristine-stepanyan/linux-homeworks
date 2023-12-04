all:demo-application

demo-application:demo-application.o
	g++ demo-application.o -o demo-application

demo-application.o:demo-application.cpp parallel_scheduler.cpp
	g++ -c demo-application.cpp -pthread

clean:
	rm *.o demo-application
