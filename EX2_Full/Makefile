all: my_grep

my_grep: main.o line_operations.o grep_functionality.o
	gcc -o my_grep main.o line_operations.o grep_functionality.o

main.o: main.c line_operations.h grep_functionality.h
	gcc -c main.c
  
line_operations.o:  line_operations.c line_operations.h grep_functionality.h
	gcc -c line_operations.c
  
grep_functionality.o: grep_functionality.c grep_functionality.h
	gcc -c grep_functionality.c
    
clean:
	-rm *.o my_grep
   
test: all 
	~nimrodav/grep_tests/run_all.sh
  
