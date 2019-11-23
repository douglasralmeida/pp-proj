#### Secao dos cabecalhos ####
PROJECTNAME=indexer
CXXFLAGS=-g -c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/

LDFLAGS=-g
LDLIBS=

BINDIR=bin
OBJDIR=obj
OBJFILES=dataset.o indexer.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src

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