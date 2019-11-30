#### Secao dos cabecalhos ####
PROJECTNAME=indexer
INCLUDES=-Iinclude
CXXFLAGS=-std=c++11 -g -c -Wall -Wextra -Wpedantic $(DEFS)
LDFLAGS=-g
LDLIBS=
PROJFILES=dataset.o hashtable.o lsh.o superbit.o lsh_superbit.o indexer.o

CUDAPROJECTNAME=indexer-cuda
HOST_COMPILER=g++
CUDA_PATH =/usr/local/cuda
CUDA_INCLUDES=-I../../Common $(INCLUDES)
CUDALIBDIRS=-L/usr/local/cuda-10.1/lib64
CUDALDLIBS=-lcudart
NVCC=$(CUDA_PATH)/bin/nvcc -ccbin $(HOST_COMPILER)
NVCCFLAGS=-std=c++11 -m64 -g -G -c
BUILD_TYPE=debug
CUDAPROJFILES=
CUDADEFS=-DUSE_GPU

TESTARFILES=test-array.o
TESTHTFILES=hashtable.o test-hashtable.o
TESTSBFILES=timer.o superbit.o test-superbit.o
TESTDSFILES=hashtable.o lsh.o superbit.o lsh_superbit.o dataset.o test-dataset.o
TESTLSHFILES=hashtable.o timer.o lsh.o superbit.o lsh_superbit.o dataset.o test-lshsb.o
TESTCUDASBFILES=gpu.ou timer.o superbit.ou test-superbit.oc
TESTCUDASLHFILES=gpu.ou timer.o hashtable.o lsh.o superbit.ou lsh_superbit.o dataset.o test-lshsb.oc

ALLFILES=gpu.o timer.o dataset.o hashtable.o lsh.o superbit.o superbit.ou lsh_superbit.o test-array.o test-hashtable.o test-superbit.o test-superbit.oc test-dataset.o test-lshsb.o test-lshsb.oc indexer.o
ALLOBJECTS=$(addprefix $(OBJDIR)/, $(ALLFILES))

ARGS_INDEXER=data/dataset.dat

BINDIR=bin
OBJDIR=obj
SOURCEDIR=src

#### Secao das regras ####
$(OBJDIR)/%.o: $(SOURCEDIR)/%.cc
	@echo
	@echo Compilando $<...
	$(CXX) $(INCLUDES) $(CXXFLAGS) $< -o $@

$(OBJDIR)/%.oc: $(SOURCEDIR)/%.cc
	@echo
	@echo Compilando $<...
	$(NVCC) $(CUDADEFS) $(INCLUDES) $(NVCCFLAGS) $< -o $@

$(OBJDIR)/%.ou: $(SOURCEDIR)/%.cu
	@echo
	@echo Compilando $<...
	$(NVCC) $(INCLUDES) $(NVCCFLAGS) $< -o $@

# Impede do comando nao ser executado caso exista um arquivo de mesmo nome ja atualizado.
.PHONY: all clean run

all: $(PROJECTNAME) $(CUDAPROJECTNAME)

$(PROJECTNAME): $(addprefix $(OBJDIR)/, $(PROJFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)

$(CUDAPROJECTNAME): $(addprefix $(OBJDIR)/, $(CUDAPROJFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(CUDALIBDIRS) $(CUDALDLIBS)

clean:
	@echo
	@echo Excluindo executavel...
	rm -f $(BINDIR)\$(PROJECTNAME)
	rm -f $(BINDIR)\$(CUDAPROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(ALLOBJECTS)

cuda: $(CUDAPROJECTNAME)
	./$(BINDIR)/$(CUDAPROJECTNAME) $(ARGS_INDEXER)

memcheck: 
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(EXE)

run: $(PROJECTNAME)
	./$(BINDIR)/$(PROJECTNAME) $(ARGS_INDEXER)

test: $(addprefix $(OBJDIR)/, $(TESTFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)

test-cuda: $(addprefix $(OBJDIR)/, $(TESTFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(CUDALIBDIRS) $(CUDALDLIBS)

test-array: $(addprefix $(OBJDIR)/, $(TESTARFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)
	@echo Executanto teste de array...
	./$(BINDIR)/$@

test-hashtable: $(addprefix $(OBJDIR)/, $(TESTHTFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)
	@echo Executanto teste da tabela hash...
	./$(BINDIR)/$@

test-sb: $(addprefix $(OBJDIR)/, $(TESTSBFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)
	@echo Executanto teste do superbit...
	./$(BINDIR)/$@

test-cudasb: $(addprefix $(OBJDIR)/, $(TESTCUDASBFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(CUDALIBDIRS) $(CUDALDLIBS)
	@echo Executanto teste do CUDA superbit...
	./$(BINDIR)/$@

test-lsh: $(addprefix $(OBJDIR)/, $(TESTLSHFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)
	@echo Executanto teste do LSH...
	./$(BINDIR)/$@

test-cudalsh: $(addprefix $(OBJDIR)/, $(TESTCUDASLHFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(CUDALIBDIRS) $(CUDALDLIBS)
	@echo Executanto teste do CUDA LSH...
	./$(BINDIR)/$@

test-dataset: $(addprefix $(OBJDIR)/, $(TESTDSFILES))
	@echo
	@echo Gerando executavel...
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)
	@echo Executanto teste do dataset...
	./$(BINDIR)/$@
