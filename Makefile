# paths on MAC OSX
SFML_LIB = -I/Users/Hipster/SFML/lib
SFML_INCLUDE = -I/Users/Hipster/SFML/include
SFML_FRAMEWORKS = -I/Library/Frameworks

LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
CXX = g++
CXXFLAGS = -g -std=c++11

all:

# %.0: %.cpp
# 	$(CXX) -c $< $(CXXFLAGS) -o %@

# %.o: %.hpp
# 	$(CXX) -c $< -o $@

# main: main.o
# 	@echo "** Building it!"
# 	$(CXX) -o main $(LIBS)

	# $(CXX) -c "main.cpp" -o main.o 
	
	$(CXX) "main.cpp" -o main $(LIBS)

install:
	@echo "doing the thing"