CXX      =  g++ 
CXXFLAGS = -ggdb 
TARGET   = ../build


all: mktarget baseRun nodeRun txaver

mktarget:
	mkdir -p $(TARGET)

txaver: aver.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)/$@

main: main.cpp $(TARGET)/base_receiver.o $(TARGET)/sender.o  $(TARGET)/average.o $(TARGET)/receiver.o $(TARGET)/node.o $(TARGET)/nodeMap.o $(TARGET)/socketC.o
	$(CXX) $(CXXFLAGS)  -lpthread -pthread $^ -o $(TARGET)/$@

baseRun: baseRun.cpp $(TARGET)/base_receiver.o $(TARGET)/sender.o $(TARGET)/timeout.o $(TARGET)/average.o $(TARGET)/receiver.o $(TARGET)/node.o $(TARGET)/nodeMap.o $(TARGET)/socketC.o
	$(CXX) $(CXXFLAGS)  -lpthread -pthread $^ -o $(TARGET)/$@

nodeRun: nodeRun.cpp $(TARGET)/base_receiver.o $(TARGET)/hello.o $(TARGET)/sender.o  $(TARGET)/average.o $(TARGET)/receiver.o $(TARGET)/node.o $(TARGET)/nodeMap.o $(TARGET)/socketC.o
	$(CXX) $(CXXFLAGS)  -lpthread -pthread $^ -o $(TARGET)/$@



$(TARGET)/sender.o: sender.cpp  $(TARGET)/node.o
	$(CXX) $(CXXFLAGS) sender.cpp  -c -o $@


$(TARGET)/node.o: $(TARGET)/average.o node.cpp
	$(CXX) $(CXXFLAGS)   node.cpp  -c -o $@

$(TARGET)/average.o: average.c
	$(CXX) $(CXXFLAGS) average.c -c -o $@

$(TARGET)/base_receiver.o: base_receiver.cpp $(TARGET)/receiver.o
	$(CXX) $(CXXFLAGS) base_receiver.cpp -c -o $@

$(TARGET)/receiver.o: receiver.cpp
	$(CXX) $(CXXFLAGS) -lpthread -pthread receiver.cpp -c -o $@

$(TARGET)/hello.o: hello.cpp $(TARGET)/nodeMap.o
	$(CXX) $(CXXFLAGS) -lpthread -pthread hello.cpp -c -o $@

$(TARGET)/timeout.o:timeout.cpp
	$(CXX) $(CXXFLAGS) -lpthread -pthread timeout.cpp -c -o $@

$(TARGET)/nodeMap.o: nodeMap.cpp
	$(CXX) $(CXXFLAGS) $^  -c -o $@

$(TARGET)/socketC.o: socketC.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@

clean:
	rm -f *.o sender base_receiver
	rm -rf $(TARGET)
