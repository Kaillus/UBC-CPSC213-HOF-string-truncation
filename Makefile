CFLAGS += -std=gnu11 -g -I..
MAIN_EXE = test
MAIN_OBJ = test.o list.o
SORT_EXE = trunc
SORT_OBJ = list.o trunc.o

EXES = $(MAIN_EXE) $(SORT_EXE)
OBJS = $(MAIN_OBJ) $(SORT_OBJ)

all: $(EXES)

$(MAIN_EXE): $(MAIN_OBJ)
$(SORT_EXE): $(SORT_OBJ)

clean:
	rm -f $(EXES) $(OBJS)
tidy:
	rm -f $(OBJS)
