# Makefile

#### Secao dos cabecalhos ####
PROJECTNAME=plsh
CC=gcc
DEFS=

CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 

LIBS=
LDFLAGS=
BINDIR=bin
OBJDIR=obj
OBJFILES=xxhash.o main.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src
TESTDIR=test

#### Secao das regras ####
$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@(echo. && echo Compilando $<...)
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.
.PHONY: all clean run nfo debug

all: clean $(PROJECTNAME).exe
	
$(PROJECTNAME).exe: $(OBJECTS)
	@(echo. && echo Gerando executavel...)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

clean:
	@echo Executando limpeza...
	del /q $(addprefix $(OBJDIR)\, $(OBJFILES))
	del /q $(BINDIR)\$(PROJECTNAME).exe
	
debug:
	gdb -q -ex 'cd bin' --args $(BINDIR)\$(PROJECTNAME).exe
	
run:
	cd bin && $(PROJECTNAME).exe	
	
info:
	@(echo Informacoes do sistema: && echo.)
	@(ver | find "Microsoft")
	@(echo Arquitetura: ^< %PROCESSOR_ARCHITECTURE%)
	@(gcc -v 2>&1 | find "gcc version")
	@(gcc -v 2>&1 | find "Target")	
	@(gdb -v | find "GNU gdb")
	@(ld -v | find "GNU ld")
	@(dlltool --version | find "GNU dlltool")
	@(make -v | find "GNU Make")