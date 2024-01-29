#ifndef DEVICE_H
#define DEVICE_H

typedef enum DeviceStatus
{
    inUse,
    broken,
    usable
} DeviceStatus;

typedef struct Device
{
    int id;
     char *name;
    DeviceStatus status;
} Device;

extern int Devicessize ;
extern struct Device devices[500] ;

int deviceCapacity=0;


void setDeviceStatus(int deviceId, DeviceStatus newStatus);
void createDevice(int deviceId, const char *deviceName, DeviceStatus deviceStatus);
void addDevice(struct Device *existingDevice);
void deleteDevice(int deviceId);
 char *deviceStatusToString(DeviceStatus status) ;

// USED FILE
void writeDevicesToFile(struct Device *devices);
void removeDeviceByAdmin(int deviceID, int adminId);
void updateDeviceStatus(int labWorkerID, int deviceID, DeviceStatus newStatus);

#endif