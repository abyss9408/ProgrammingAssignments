DRIVER_OBJ = shellmain.obj

USHELL_CPP = uShell.cpp
USHELL_H = uShell.h uShell2.h uShell3.h
USHELL_OBJ = uShell.obj

REF_USHELL_OBJ = uShell_ref.obj

USHELL3_HELP_OBJ = uShell3_helper.obj

REF_USHELL2_OBJ = uShell2_ref.obj


ALL_OBJ = $(DRIVER_OBJ) $(USHELL_OBJ) $(REF_USHELL_OBJ) $(REF_USHELL2_OBJ) $(USHELL3_HELP_OBJ)

BUILD = g++ -std=c++17
FLAGS = -Werror -Wall -Wextra -pedantic 
TO_OBJ = -c

OUTPUT_FLAG = -o

EXE = $(OUTPUT_DIR)uShell

TEST_EXE = vpl_execution

# Default build rule  
# Build command for uShell.obj 
$(USHELL_OBJ) : $(USHELL_CPP) $(USHELL_H)
	$(BUILD) $(FLAGS) $(TO_OBJ) $(USHELL_CPP) $(OUTPUT_FLAG) $(USHELL_OBJ) 

uShell : $(ALL_OBJ)
	$(BUILD) $(OUTPUT_FLAG) $(EXE) $(ALL_OBJ)

	
.PHONY: rebuild
# Rebuild 
rebuild:
	-$(MAKE) clean
	-$(MAKE) uShell
	
# Default build rule  
uShell : $(ALL_OBJ)
	$(BUILD) $(OUTPUT_FLAG) $(EXE) $(ALL_OBJ)

# Clean
.PHONY: clean 
clean :
	-rm -f ${USHELL_OBJ}
	-rm -f ${EXE}	