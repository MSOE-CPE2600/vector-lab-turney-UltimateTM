CC=gcc
CFLAGS=-c -Wall
LDFLAGS= -lm
SOURCES= main.c input.c vec_operations.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= vec_calculator
all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d