TARGET_EXEC := a.out
BUILD_DIR := ./build
SRC_DIR := ./src

# This searches recursively by default
# The name of each of SRC starts with the SRC_DIR
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

# Gets a list of the sub dirs of SRC_DIR including itself
INC_DIRS := $(shell find $(SRC_DIR) -type d) 
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CXX := clang++
CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall -std=c++17

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "\nLinking to make a.out ..."
	$(CXX) $(OBJS) $(LDFLAGS)-o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo "\nBuilding $@"
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	rm -rf $(BUILD_DIR)

# The - here supresses errors of missing makefiles
# pastes the .d files into this 
-include $(DEPS)
