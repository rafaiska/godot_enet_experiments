CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -g
LIBS = -lenet -lspdlog -lfmt

TARGET = rapinae
SOURCES = main.cpp actor.cpp attribute.cpp map.cpp actor_serializer.cpp timer.cpp physics_processor.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)