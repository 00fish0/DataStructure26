# Makefile for compiling all .cpp files in current directory

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O2

# Debug flags for array bounds checking
DEBUG_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
VALGRIND_FLAGS = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes

# Directories
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Find all .cpp files in current directory
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Generate corresponding .o files in obj directory
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
# Generate executable names (without .cpp extension)
TARGETS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%)

# Default target
.PHONY: all clean help debug valgrind

all: $(TARGETS)

# Debug build with sanitizers
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGETS)
	@echo "Debug build complete with AddressSanitizer and UBSan"

# Rule to create executable for each .cpp file
$(BINDIR)/%: $(OBJDIR)/%.o | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Built executable: $@"

# Rule to compile .cpp to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled: $< -> $@"

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Individual targets for easy running
.PHONY: binarytree sort sort-debug sort-valgrind

binarytree: $(BINDIR)/BinaryTree
	@echo "Running BinaryTree..."
	./$(BINDIR)/BinaryTree

sort: $(BINDIR)/Sort
	@echo "Running Sort..."
	./$(BINDIR)/Sort

# Debug version with sanitizers
sort-debug: clean
	@echo "Building Sort with debug flags..."
	$(MAKE) debug
	@echo "Running Sort with AddressSanitizer..."
	ASAN_OPTIONS=abort_on_error=1:halt_on_error=1 ./$(BINDIR)/Sort

# Valgrind memory check
sort-valgrind: $(BINDIR)/Sort
	@echo "Running Sort with Valgrind..."
	valgrind $(VALGRIND_FLAGS) ./$(BINDIR)/Sort

# Static analysis
static-check:
	@echo "Running static analysis..."
	cppcheck --enable=all --std=c++11 $(SOURCES)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Cleaned build files"

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build all executables"
	@echo "  debug        - Build with debug flags (AddressSanitizer, UBSan)"
	@echo "  binarytree   - Build and run BinaryTree"
	@echo "  sort         - Build and run Sort"
	@echo "  sort-debug   - Build and run Sort with memory debugging"
	@echo "  sort-valgrind - Run Sort with Valgrind memory check"
	@echo "  static-check - Run static analysis with cppcheck"
	@echo "  clean        - Remove build files"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Executables will be created in bin/ directory:"
	@for target in $(TARGETS); do echo "  $$target"; done
	@echo ""
	@echo "Debug options:"
	@echo "  make sort-debug    - Detects buffer overflows, use-after-free, etc."
	@echo "  make sort-valgrind - Detailed memory error detection"
	@echo "  make static-check  - Static code analysis"