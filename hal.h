void HalDebugPutc(char c);
void HalDebugPuts(const char* str);
void HalSetupMemory();
void HalSetMMUTTB(void* ttb);
void HalEnableMMU();
void HalEnableICache();
void HalEnableDCache();
void HalHaltCPU();
void HalSetMMUDomain();
