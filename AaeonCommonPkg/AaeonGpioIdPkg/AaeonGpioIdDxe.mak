
Prepare :  $(BUILD_DIR)/AaeonGpioIdFunctions.h

$(BUILD_DIR)/AaeonGpioIdFunctions.h:  $(BUILD_DIR)/token.mak
	$(ECHO) \
#define AAEON_GPIO_ID_INIT_FUNCTION $(AAEON_GPIO_ID_INIT_FUNCTION)$(EOL)\
> $(BUILD_DIR)/AaeonGpioIdFunctions.h