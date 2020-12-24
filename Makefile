########################
#
# SFML-ready Makefile
# Author: Jacob Nardone
# Date: 12/24/2020
#
########################

CXX 		?= g++
TARGET 		?= final

BUILD_DIR 	?= bin
OBJ_DIR 	?= objs
SRC_DIR 	?= src

SRCS := $(notdir $(wildcard $(SRC_DIR)/*.cpp))
#$(info $$SRCS is [${SRCS}]) # print out sources
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

INCLUDES 	= -IC:/dev/libraries/SFML/include -Iinclude
DEV-DEPS 	= -LC:/dev/libraries/SFML/lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
RLS-DEPS 	= -LC:/dev/libraries/SFML/lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -mwindows -O2
	# mwindows: tells exe not to open seperate console window when running exe
	# O2: optimization level 2 (longer compile time)

MKDIR_P ?= mkdir -p

.PHONY: default
default: $(BUILD_DIR)/$(TARGET)	# set default goal

$(BUILD_DIR):
	$(MKDIR_P) $@

$(OBJ_DIR):
	$(MKDIR_P) $@


# link the executable
$(BUILD_DIR)/$(TARGET): $(OBJS) | $(OBJ_DIR) $(BUILD_DIR) # default goal
	$(CXX) $(OBJS) -o $@ $(DEV-DEPS)

# create the object files
$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(INCLUDES)


.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.exe
	rm -rf $(OBJ_DIR)


run:
	@printf "\n\n"
	@echo "Running:"
	@echo "=================================="
	@$(BUILD_DIR)/$(TARGET)
	@echo "=================================="
	@printf "\n\n"
