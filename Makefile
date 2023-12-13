CFLAGS = -Wall -Wextra -Werror

ASAN = -fsanitize=address,undefined -g

REPORT_DIR = report_dir
LIB_DIR = lib
EXECUTABLE = bin

OPTIM = -O0

LDFLAGS = 

all: compile

compile: formating
	cc -c *.c $(CFLAGS) $(LDFLAGS) $(OPTIM)	
	cc *.o $(CFLAGS) -o $(EXECUTABLE)_clean $(LDFLAGS) $(OPTIM)
	rm *.o

debug: formating
	cc -c -g *.c $(OPTIM)
	cc *.o -o $(EXECUTABLE)_debug $(LDFLAGS) $(OPTIM)
	rm *.o

asan: formating
	clang -c *.c $(CFLAGS) $(ASAN) $(OPTIM)
	clang *.o $(CFLAGS) $(ASAN) -o $(EXECUTABLE)_asan $(LDFLAGS) $(OPTIM)
	rm *.o

static: formating
	clang --analyze -Xanalyzer -analyzer-output=html -o $(REPORT_DIR) *.c

formating:
	clang-format *.c -i -style=webkit

clean:
	rm -f $(EXECUTABLE)* */*.html

help:
	@echo "Available targets:"
	@echo "  all      : Build the executable with default settings"
	@echo "  compile  : Build the executable"
	@echo "  debug    : Build the executable with debugging information"
	@echo "  asan     : Build the executable with AddressSanitizer"
	@echo "  static   : Run static analysis and generate HTML reports"
	@echo "  clean    : Remove generated files"
	@echo "  formating: Format source code using clang-format"
	@echo "  help     : Display this help message"
	
