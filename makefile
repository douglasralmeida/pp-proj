#### Secao dos cabecalhos ####
PROJECTNAME=indexer
CXXFLAGS=-std=c++11 -g -c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/cpu/

LDFLAGS=-g
LDLIBS=

BINDIR=bin
OBJDIR=obj
#OBJFILES=dataset.o hashtable.o lsh.o superbit.o lsh_superbit.o test-lshsb.o
#OBJFILES=dataset.o hashtable.o lsh.o superbit.o lsh_superbit.o indexer.o
OBJFILES=superbit.o test-superbit.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src/cpu

#### Secao das regras ####
$(OBJDIR)/%.o: $(SOURCEDIR)/%.cc
	@echo
	@echo Compilando $<...
	$(CXX) $(INCLUDES) $(CXXFLAGS) $< -o $@

# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.
.PHONY: all clean run

all: $(PROJECTNAME).exe

$(PROJECTNAME).exe: $(OBJECTS)
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)

clean:
	@echo
	@echo Excluindo executavel...
	del $(BINDIR)\$(PROJECTNAME).exe
	@echo Excluindo objetos...
	del $(OBJECTS)

run: $(PROJECTNAME).exe
	./$(BINDIR)/$(PROJECTNAME).exe