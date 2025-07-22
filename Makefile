TARGET = imobiliaria

CXX = /c/msys64/ucrt64/bin/g++.exe

CXXFLAGS = -std=c++11 -Wall -g

SRCS = main.cpp Imovel.cpp Corretor.cpp Cliente.cpp Agendamento.cpp

OBJS = $(SRCS:.cpp=.o)

MAKE_CMD = mingw32-make

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET).exe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: test1 test2 test3

test1: $(TARGET)
	./$(TARGET).exe < teste1_entrada.txt > actual_output_teste1.txt
	diff actual_output_teste1.txt teste1_saida.txt

test2: $(TARGET)
	./$(TARGET).exe < teste2_entrada.txt > actual_output_teste2.txt
	diff actual_output_teste2.txt teste2_saida.txt

test3: $(TARGET)
	./$(TARGET).exe < teste3_entrada.txt > actual_output_teste3.txt
	diff actual_output_teste3.txt teste3_saida.txt

.PHONY: tests_all
tests_all: test1 test2 test3

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).exe actual_output_teste*.txt # Adicionado arquivos de saida de teste para limpeza
