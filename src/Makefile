SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	-$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	-$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
