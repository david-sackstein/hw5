hdr = $(wildcard *.h)
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = WolfraMamat

all: $(exe)

$(exe): $(obj)
	g++ -g $(obj) -o $@

%.o: %.cpp $(hdr)
	g++ -c -g -Wall $< -o $@
		
clean: 
	rm $(obj) $(exe)
