# Makefile do Projeto Algo. Paralelos
# Algoritmo LSH para plataforma CUDA

#### Secao dos cabecalhos ####
PROJECTNAME=indexer-cuda
HOST_COMPILER=g++
CUDA_PATH =/usr/local/cuda
NVCC=$(CUDA_PATH)/bin/nvcc -ccbin $(HOST_COMPILER)
DEFS=
NVCCFLAGS=-std=c++11 -m64 -g -G -c
BUILD_TYPE=debug
LDFLAGS=
INCLUDES=-I../../Common -Iinclude/gpu
LIBDIRS=-L/usr/local/cuda-10.1/lib64
LDLIBS=-lcudart

BINDIR=bin
OBJDIR=obj
OBJFILES=gpu.ou superbit.ou test-superbit.ou
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))

SOURCEDIR=src/gpu
TESTDIR=test

#### Secao das regras ####
$(OBJDIR)/%.ou: $(SOURCEDIR)/%.cu
	@echo
	@echo Compilando $<...
	$(NVCC) $(NVCCFLAGS) $(INCLUDES)  $< -o $@

# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.
.PHONY: all clean run

all: clean $(PROJECTNAME)

$(PROJECTNAME): $(OBJECTS)
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBDIRS) $(LDLIBS)

clean:
	@echo
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

run: $(PROJECTNAME)
	./$(BINDIR)/$(PROJECTNAME)
