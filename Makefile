-include src/subdir.mk

RM := rm -rf
LIBS :=

# All Target
all: smartcopy

# Tool invocations
smartcopy: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"" -pthread -o"smartcopy" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	@echo "Cleaning up ..."
	$(RM) $(OBJS) $(C++_DEPS) $(C_DEPS) $(CC_DEPS) $(CPP_DEPS) $(EXECUTABLES) $(CXX_DEPS) $(C_UPPER_DEPS) smartcopy
	@echo 'done'

.PHONY: all clean dependents
.SECONDARY:
