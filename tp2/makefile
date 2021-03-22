INC_DIR     = include
SRC_DIR     = src
BUILD_DIR   = build
TARGET_DIR  = bin
SRC         = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS     = $(wildcard $(INC_DIR)/*.h)
OBJ         = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET      = $(TARGET_DIR)/tp2.out

CC       = g++
CFLAGS   = -g -Wall -Werror -Wno-unused-variable -Wno-unused-function -Wno-unused-const-variable
INCLUDES = -I$(INC_DIR)
DIRS     = $(BUILD_DIR) $(TARGET_DIR)

all: $(DIRS) $(TARGET)

$(BUILD_DIR):
	@echo mkdir $@
	@mkdir -p $@

$(TARGET_DIR):
	@echo mkdir $@
	@mkdir -p $@

$(TARGET): $(OBJ)
	@echo LD $@
	@$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo CC $@
	@$(CC) $(INCLUDES) $(CFLAGS) $< -c -o $@

clean:
	@for item in $(DIRS); do \
        if [ -d $$item ] ; then \
                echo "RM -r $$item"; \
                $(RM) -r $$item ; \
	else \
		echo "$$item already removed" ;\
	fi \
	done

clean-test:
	@$(MAKE) -C tests clean

check: all
	@$(MAKE) -C tests check

test: all
	@$(MAKE) -C tests

run: all
	@echo "-------exec-------"
	@./$(TARGET)

.PHONY: clean clean-check run check
