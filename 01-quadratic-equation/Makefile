CXX=clang++
CXXFLAGS=-c -D _DEBUG -ggdb3 -std=c++03 -Wall -Wextra -Weffc++ -Wcast-align -Wcast-qual -Wchar-subscripts -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE -O0
TARGET=bin

all: $(TARGET)

bin: main.o solve_equation.o read_print.o is_zero.o
	$(CXX) main.o solve_equation.o read_print.o is_zero.o -o $(TARGET)

main.o: main.c
	$(CXX) $(CXXFLAGS) main.c -o main.o

solve_equation.o: solve_equation.c
	$(CXX) $(CXXFLAGS) solve_equation.c -o solve_equation.o

read_print.o: read_print.c
	$(CXX) $(CXXFLAGS) read_print.c -o read_print.o

is_zero.o: is_zero.c
	$(CXX) $(CXXFLAGS) is_zero.c -o is_zero.o

clean:
	rm -rf *.o $(TARGET)

clean.o:
	rm -rf *.o