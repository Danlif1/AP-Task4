

CXX := g++
CXXFLAGS := -std=c++11
SERVERSOURCES = $(wildcard ServerFiles/CommandFiles/*.cpp ) $(wildcard ServerFiles/PointFiles/*.cpp ) $(wildcard ServerFiles/KNNFiles/*.cpp )  $(wildcard ServerFiles/CLIFiles/*.cpp ) $(wildcard ServerFiles/*.cpp )  $(wildcard SocketFiles/*.cpp )
CLIENTSOURCES = $(wildcard ClientFiles/*.cpp ) $(wildcard SocketFiles/*.cpp )

serverNclient : $(SERVERSOURCES) $(CLIENTSOURCES)
	$(CXX) $(CXXFLAGS)  $(CLIENTSOURCES) -o clientrun
	$(CXX) $(CXXFLAGS)  $(SERVERSOURCES) -o serverrun -lpthread

server : $(SERVERSOURCES)
	$(CXX) $(CXXFLAGS)  $(SERVERSOURCES) -o serverrun -lpthread
client : $(CLIENTSOURCES)
	$(CXX) $(CXXFLAGS)  $(CLIENTSOURCES) -o clientrun
