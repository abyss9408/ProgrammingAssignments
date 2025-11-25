DRIVER_OBJ = shellmain.obj

USHELL_CPP = uShell.cpp 
USHELL_H = uShell.h
USHELL_OBJ = uShell.obj 
USHELL_HELP_OBJ = uShell_helper.obj

REF_USHELL_OBJ = uShell_ref.obj

ALL_OBJ = $(DRIVER_OBJ) $(USHELL_OBJ) $(USHELL_HELP_OBJ) 
REF_ALL_OBJ = $(DRIVER_OBJ) 

BUILD = g++ -std=c++17
FLAGS = -Werror -Wall -Wextra -pedantic 
TO_OBJ = -c

OUTPUT_FLAG = -o

EXE = $(OUTPUT_DIR)uShell 
REF_EXE = $(OUTPUT_DIR)uShell_ref 

# Build command for uShell.obj 
$(USHELL_OBJ) : $(USHELL_CPP) $(USHELL_H)
	$(BUILD) $(FLAGS) $(TO_OBJ) $(USHELL_CPP) $(OUTPUT_FLAG) $(USHELL_OBJ)

# Default build rule  
uShell : $(ALL_OBJ)
	$(BUILD) $(OUTPUT_FLAG) $(EXE) $(ALL_OBJ)

# Clean 
clean :
	-rm -f ${USHELL_OBJ}
	-rm -f ${EXE}
    
# Rebuild 
rebuild:
	-$(MAKE) clean
	-$(MAKE) uShell