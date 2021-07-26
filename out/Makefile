#makefile


VPATH =.. ; ../lib

OBJ=  _main.o  _linux.o lcd.o line.o  arc.o cursor.o  fillarc.o fillpoly.o  floodfill.o    gvar.h graphics.h

all:demo echo

demo: $(OBJ)
	gcc  -lm   -o $@    $(filter-out %.h, $(OBJ))

echo:
	@echo
	@echo ^o^ Congratulations !
	@echo
	

%.o : %.c
	gcc  -g -c -o $@ $<        -I../lib	
	
clean: 
	@rm *.o demo -f
	@echo delete all......done 
