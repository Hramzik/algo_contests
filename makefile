

cc = gcc

#--------------------------------------------------

TASK_FOLDER   = src/a
UNITED_FOLDER = united

exefolder = exe

#--------------------------------------------------

define flags
	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
endef


sc = @ #showcommands
default_name = prog
default_path = $(exefolder)/$(default_name)

#--------------------------------------------------

all: task


task:
	$(sc) $(cc) \
	$(TASK_FOLDER)/task.cpp \
	-o $(default_path) $(flags) -lstdc++

uni:
	$(sc) $(cc) \
	$(UNITED_FOLDER)/united.cpp \
	-o $(default_path) $(flags) -lstdc++

