CURR_DIR 		:=  $(shell pwd | sed 's/ /\\ /g') # path to current dir
CLASSES_DIR_NAME	:= classes
DATA_DIR_NAME		:= data
CLASSES_DIR		:= $(strip $(CURR_DIR))/$(CLASSES_DIR_NAME) # strip removes trailing white space
CC			:= g++
CFLAGS			:= -I$(CURR_DIR) -I$(CLASSES_DIR)

OBJS			:= ukulele.o customErrorClass.o

UkuleleChordFinder: main.cpp ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

ukulele.o: $(strip $(CLASSES_DIR_NAME))/ukulele.cpp $(strip $(CLASSES_DIR_NAME))/ukulele.h
	${CC} -c -o $@ $< ${CFLAGS}

customErrorClass.o: $(strip $(CLASSES_DIR_NAME))/customErrorClass.cpp $(strip $(CLASSES_DIR_NAME))/customErrorClass.h
	${CC} -c -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm *.o