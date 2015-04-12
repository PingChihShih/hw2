CFLAGS = -O2 -Wall
CPPFLAGS = -O2 -std=c++11 -Wall

demo: bigdata.cpp myclass.cpp myclass.h
	g++ $(CPPFLAGS) bigdata.cpp myclass.cpp -o $@

clean:
	rm -rf demo

rundemo:
	./demo

runbypath:
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt
	
