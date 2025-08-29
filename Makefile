TARGET := mdlx-cli

CC := g++
CFLAGS := -std=c++11
# CFLAGS += -Wall -Wextra
CFLAGS += -Wno-sign-compare
LDFLAGS :=

export TARGET CC CFLAGS LDFLAGS

.PHONY: all clean

all:
	make $@ -C src
	mv src/$(TARGET) .

clean:
	make $@ -C src
	rm -f $(TARGET)
