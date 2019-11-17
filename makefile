# Makefile do Projeto Algo. Paralelos
# Algoritmo LSH para plataforma CUDA

#### Secao dos cabecalhos ####
PROJECTNAME=plsh
HOST_COMPILER=g++
CUDA_PATH =/usr/local/cuda
NVCC=$(CUDA_PATH)/bin/nvcc -ccbin $(HOST_COMPILER)
DEFS=
NVCCFLAGS=-m64 -g -G -c
BUILD_TYPE=debug
LDFLAGS=
INCLUDES=-I../../Common
LIBS=

BINDIR=bin
OBJDIR=obj
OBJFILES=main.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))
SOURCEDIR=src
TESTDIR=test

#### Secao das regras ####
$(OBJDIR)/%.o: $(SOURCEDIR)/%.cu
	@echo
	@echo Compilando $<...
	$(NVCC) $(INCLUDES) $(NVCCFLAGS) $< -o $@

# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.
.PHONY: all clean run

all: clean $(PROJECTNAME)

$(PROJECTNAME): $(OBJECTS)
	@echo
	@echo Gerando executavel...
	$(NVCC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

clean:
	@echo
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

run: $(PROJECTNAME)
	./$(BINDIR)/$(PROJECTNAME)