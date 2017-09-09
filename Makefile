
TARGET=libanalogrytm_test

CC=gcc

CFLAGS= -Wall -Wno-unused-value -Wno-unused-function

CFLAGS += -DAR_DEBUG

EXE_OBJ= \
	testcases/main.o

LIB_OBJ= \
	pattern.o \
	kit.o \
	sound.o \
	sysex.o

OBJ= \
	$(LIB_OBJ) \
	$(EXE_OBJ)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

.c.o:
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ) $(TARGET)

real_clean: clean
	rm -f `find . -name \*~`
