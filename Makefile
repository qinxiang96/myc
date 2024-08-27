CC := gcc
CFLAG := -O3 -Wall
OBJS := demo10.o xz_printf.o 
TARGET := eval

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c 
	$(CC) $(CFLAG) -c -o $@ $<