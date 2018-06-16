hdr = $(wildcard *.h)
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = WolfraMamat

all: $(exe)

$(exe): $(obj)
	echo $(obj)
	g++ -g $(obj) -o $@

%.o: %.cpp $(hdr)
# g++ -c -g -Wall $< -o $@
	echo $(obj)
		
clean: 
	rm $(obj) $(exe)
