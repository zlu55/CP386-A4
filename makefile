All: runq1 runq2

runq1: 191739390_190454440_a04_q1.c
	gcc -o 

CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = Question1 Question2 
OBJFILES = Question1.o Question2.o
all: $(TARGET)
Question1: 191739390_190454440_a04_q1.c
	$(CC) $(CFLAGS) -o Question1 191739390_190454440_a04_q1.c $(LDFLAGS)
Question2: 191739390_190454440_a04_q2.c
	$(CC) $(CFLAGS) -o Question2 191739390_190454440_a04_q2.c $(LDFLAGS)

runq1: Question1
	./Question1 10 5 7 8
runq2: Question2
	./Question2 1000000
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
