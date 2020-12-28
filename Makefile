########################
#
# SFML-ready Makefile
# Author: Jacob Nardone
# Date: 12/24/2020
#
########################

CXX 		?= g++
TARGET 		?= final

BUILD_DIR 	?= build
OBJ_DIR 	?= objs
SRC_DIR 	?= src
RES_DIR		?= res

SRCS := $(notdir $(wildcard $(SRC_DIR)/*.cpp))
#$(info $$SRCS is [${SRCS}]) # print out sources
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

INCLUDES 	= -IC:/dev/libraries/SFML/include -Iinclude
DEV_DEPS 	= -LC:/dev/libraries/SFML/lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
RLS_DEPS 	= -LC:/dev/libraries/SFML/lib -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -mwindows -O2
	# mwindows: tells exe not to open seperate console window when running exe
	# O2: optimization level 2 (longer compile time)

MKDIR_P ?= mkdir -p


# link the dev target
.PHONY: dev
dev: $(OBJS) | $(OBJ_DIR) $(BUILD_DIR) # default goal
	@echo linking dev
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$(TARGET) $(DEV_DEPS)


# link the release target
.PHONY: release
release: $(OBJS) | $(OBJ_DIR) $(BUILD_DIR)
	@echo linking release
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$(TARGET) $(RLS_DEPS)


.PHONY: portable
portable: release
	@echo creating portable
	@rm -rf portable
	@cp -r $(BUILD_DIR)/ portable/
	@cp -r $(RES_DIR)/ portable/$(RES_DIR)/


# required directories
$(BUILD_DIR):
	$(MKDIR_P) $@

$(OBJ_DIR):
	$(MKDIR_P) $@


# create the object files
$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(INCLUDES)


.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.exe
	rm -rf $(OBJ_DIR)

# run the target
run:
	@printf "\n\n"
	@echo "Running:"
	@echo "=================================="
	@$(BUILD_DIR)/$(TARGET)
	@echo "=================================="
	@printf "\n\n"
