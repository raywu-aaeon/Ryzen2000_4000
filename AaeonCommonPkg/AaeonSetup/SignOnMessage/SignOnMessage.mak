Prepare : $(BUILD_DIR)/SignOnMessage.uni

$(BUILD_DIR)/SignOnMessage.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated BIOS Sign-On Message Setup String. Do not modify$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
#string STR_BIOS_SIGNON_MESSAGE         #language eng \"    $(AAEON_MODEL_NAME) $(BIOS_SIGNON_VERSION)($(BIOS_BUILD_DAY))\"$(EOL)"\
> $(BUILD_DIR)\Temp.uni
	$(GENUNIFILE) $(BUILD_DIR)\Temp.uni $@


