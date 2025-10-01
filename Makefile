CC = gcc
AR = ar

CFLAGS = -c
LIB_SRCS = libmouse.c
EXAMPLE_SRC = example.c

LIB_OBJS = $(LIB_SRCS:.c=.o)
EXAMPLE_OBJS = $(EXAMPLE_SRC:.c=.o)

OUTPUT_LIB = libmouse.a
OUTPUT_EXECUTABLE = example

all: $(OUTPUT_LIB)
executable: $(OUTPUT_EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(OUTPUT_LIB): $(LIB_OBJS)
	$(AR) rcs $(OUTPUT_LIB) $(LIB_OBJS)

$(OUTPUT_EXECUTABLE): $(EXAMPLE_OBJS) $(OUTPUT_LIB)
	$(CC) -o $(OUTPUT_EXECUTABLE) $(EXAMPLE_OBJS) $(OUTPUT_LIB)

clean:
	rm -rf $(OUTPUT_LIB) $(OUTPUT_EXECUTABLE) $(LIB_OBJS) $(EXAMPLE_OBJS)
