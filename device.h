int deviceCount = 0;
typedef struct{
    void createDevice(const char* name){
        deviceCount++;
    }
}Device;