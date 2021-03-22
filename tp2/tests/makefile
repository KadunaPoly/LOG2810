TESTS =	bin/test-parser.out

INC_DIR     = ../include
SRC_DIR     = src
BUILD_DIR   = build
TARGET_DIR  = bin
SRC         = $(wildcard $(SRC_DIR)/*.c)
OBJ         = $(filter-out ../build/main.o, $(wildcard ../build/*.o))
PROTECT     = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


CC       = g++
CFLAGS   = -g -Wall -Werror -Wno-unused-variable -Wno-unused-function -Wno-unused-const-variable
INCLUDES = -I$(INC_DIR)
DIRS     = $(BUILD_DIR) $(TARGET_DIR)

.SECONDARY: $(OBJS)

all: $(DIRS) $(TESTS)

$(BUILD_DIR):
	@echo mkdir $@
	@mkdir -p $@

$(TARGET_DIR):
	@echo mkdir $@
	@mkdir -p $@

$(TARGET_DIR)/%.out: $(BUILD_DIR)/%.o $(OBJ)
	@echo LD $@
	@$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
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

check: all
	@echo ; \
	echo ------test------ ; \
	echo ; \
	for item in $(TESTS); do \
		echo ----./$$item----; \
		echo ; \
		./$$item ; \
	done ; \
	echo \

.PHONY: all clean check
