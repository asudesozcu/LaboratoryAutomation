#include <stdlib.h>
#include <stdio.h>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"

struct Device devices[500];
int Devicessize = 0;

void setDeviceStatus(int deviceId, DeviceStatus newStatus)
{
    for (int i = 0; i < Devicessize; i++)
    {
        if (devices[i].id == deviceId)
        {
            devices[i].status = newStatus;
            return; // id bulunduğunda işlemi bitir
        }
    }
    printf("Not found device\n");
}

void createDevice(int deviceId, const char *deviceName, DeviceStatus deviceStatus)
{
    for (int i = 0; i < Devicessize; i++)
    {

        if (devices[i].id == deviceId)
        {
            printf("Hata: This id is already in use.\n");
            return;
        }
    }

    Device newDevice;
    newDevice.id = deviceId;
    newDevice.name = malloc(strlen(deviceName) + 1);

    if (newDevice.name == NULL)
    {
        perror("Hata: Memory Allocation Problem");
        exit(EXIT_FAILURE);
    }

    strcpy(newDevice.name, deviceName);
    newDevice.status = deviceStatus;

    addDevice(&newDevice);
}
void addDevice(struct Device *existingDevice)
{
    // Eğer dizinin kapasitesi yetersizse genişlet
    if (Devicessize >= deviceCapacity)
    {

        if (deviceCapacity == 0)
        {
            deviceCapacity = INITIAL_CAPACITY;
        }
        else
        {
            deviceCapacity += 10;
        }
    }
    // Mevcut hastayı ekle
    devices[Devicessize] = *existingDevice;
    Devicessize++;


    writeDevicesToFile(devices);
}

void writeDevicesToFile(struct Device *devices)
{
    FILE *file = fopen("devices.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open the file for writing.\n");
        return;
    }
    for (int i = 0; i < Devicessize; ++i)
    {
        // Check if the device is not null
        if (devices[i].id != 0)
        {

            fprintf(file, "Device ID: %d\n", devices[i].id);

            // Dynamically allocate memory for the name
            char *name = (char *)malloc(sizeof(200));

            strcpy(name, devices[i].name);

            fprintf(file, "Name: %s\n", name);

            fprintf(file, "Status: %s\n", deviceStatusToString(devices[i].status));

            fprintf(file, "-------------------------\n");
        }
    }

    fclose(file);
}
char *deviceStatusToString(DeviceStatus status)
{
    switch (status)
    {
    case inUse:
        return "inUse";
    case broken:
        return "broken";
    case usable:
        return "usable";
    }
}
void removeDeviceByAdmin(int deviceID, int adminId)
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (users[i].isAdmin)
        {
            for (int j = 0; j < Devicessize; ++j)
            {
                if (devices[j].id == deviceID)
                {
                    FILE *file, *tempFile;
                    char line[1000];

                    // Open the source file in read mode
                    file = fopen("devices.txt", "r");
                    if (file == NULL)
                    {
                        perror("Error opening the file");
                        exit(EXIT_FAILURE);
                    }

                    // Open a temporary file in write mode
                    tempFile = fopen("temp.txt", "w");
                    if (tempFile == NULL)
                    {
                        fclose(file);
                        perror("Error creating the file");
                        exit(EXIT_FAILURE);
                    }

                    // Check each line of the file
                    while (fgets(line, sizeof(line), file) != NULL)
                    {
                        char *str = (char *)malloc(12);
                        sprintf(str, "%d", deviceID);
                        if (strstr(line, str) == NULL)
                        {
                            // If not, write the line to the temporary file
                            fputs(line, tempFile);
                        }
                        free(str);
                    }

                    // Close the files
                    fclose(file);
                    fclose(tempFile);

                    // Remove the source file
                    if (remove("devices.txt") != 0)
                    {
                        perror("Error removing the file");
                        exit(EXIT_FAILURE);
                    }

                    // Rename the temporary file with the source file name
                    if (rename("temp.txt", "devices.txt") != 0)
                    {
                        perror("Error renaming the file");
                        exit(EXIT_FAILURE);
                    }

                    // Now, delete the device in memory
                    deleteDevice(deviceID);
                    printf("Device deleted.\n");

                    return; // Exit the loop if the admin is found
                }
            }
        }
    }

    printf("You are not allowed to delete devices.\n");
}
void deleteDevice(int deviceId)
{
    for (int i = 0; i < Devicessize; i++)
    {
        if (devices[i].id == deviceId)
        {

            // Set id to 0 and name and status to NULL
            devices[i].id = 0;
            devices[i].name = '\0';
            devices[i].status = '\0';

            // Shift the remaining devices to fill the gap
            for (int j = i; j < Devicessize - 1; j++)
            {
                devices[j] = devices[j + 1];
            }

            // Decrease the device count
            Devicessize--;
        }
    }
}
void updateDeviceStatus(int labWorkerID, int deviceID, DeviceStatus newStatus)
{

    FILE *file = fopen("devices.txt", "r+");
    if (!file)
    {
        fprintf(stderr, "Error: Could not open the file for reading and writing.\n");
        return;
    }

    char *line = (char *)malloc(1000); // Dynamically allocate memory for the line
    if (!line)
    {
        fclose(file);
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 1000, file))
    {
        if (strstr(line, "Device ID:") && strstr(line, "Status:"))
        {
            int currentDeviceID;
            if (sscanf(line, "Device ID: %d", &currentDeviceID) == 1)
            {
                if (currentDeviceID == deviceID)
                {
                    // Move the file pointer back to the beginning of the line
                    fseek(file, -(long)strlen(line), SEEK_CUR);

                    // Write the new status directly to the file
                    fprintf(file, "Status: %s\n", deviceStatusToString(newStatus));

                    fclose(file);
                    printf("Device status updated for ID %d by lab worker ID %d.\n", deviceID, labWorkerID);

                    // Update in-memory devices
                    setDeviceStatus(deviceID, newStatus);

                    // Free dynamically allocated memory
                    free(line);

                    return;
                }
            }
            else
            {
                // Handle sscanf failure
                fprintf(stderr, "Error: Failed to read Device ID from line: %s\n", line);
            }
        }
    }

    fclose(file);
    free(line);
    printf("Device with ID %d not found in the file.\n", deviceID);
}