
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"
void addUserLabWorker(struct LabWorker *labWorker);

struct Device devices[500];
struct LabWorker *labWorkers;
int labWorkerCount = 0;
int labWorkerCapacity = 0;

void createLabWorker(const char *username, const long id, const char *password, const char *name, const char *surname, const char *phone)
{
    struct LabWorker newLabworker;
    newLabworker.userInfo.name = malloc(sizeof(100));
    newLabworker.userInfo.surname = malloc(sizeof(100));
    newLabworker.userInfo.username = malloc(sizeof(100));
    newLabworker.userInfo.password = malloc(sizeof(100));
    newLabworker.userInfo.phone = malloc(sizeof(100));

    for (int i = 0; i < numberOfUsers; i++)
    {
        if (users[i].id == id)
        {
            printf("Hata: This id is already in use.\n");
            return;
        }
    }

    strcpy(newLabworker.userInfo.username, username);
    strcpy(newLabworker.userInfo.password, password);
    strcpy(newLabworker.userInfo.name, name);
    strcpy(newLabworker.userInfo.surname, surname);
    strcpy(newLabworker.userInfo.phone, phone);
    newLabworker.userInfo.type = LABMAN;

    newLabworker.userInfo.id = id;
    addToWorkersList(&newLabworker);
    addUserLabWorker(&newLabworker);
}

void addToWorkersList(struct LabWorker *existingWorker)
{
    // Eğer dizinin kapasitesi yetersizse genişlet
    if (labWorkerCount >= labWorkerCapacity)
    {
        if (labWorkerCapacity == 0)
        {
            labWorkerCapacity = INITIAL_CAPACITY;
        }
        else
        {
            labWorkerCapacity += 10;
        }

        struct LabWorker *newLabWorker = realloc(labWorkers, labWorkerCapacity * sizeof(struct LabWorker));

        if (newLabWorker == NULL)
        {
            printf("Problem in memory allocation\n");
            return;
        }

        labWorkers = newLabWorker;
    }

    // Mevcut hastayı ekle
    labWorkers[labWorkerCount] = *existingWorker;
    labWorkerCount++;

}
// Function to check if a LabWorker with the given username exists
int labWorkerExists(const char *desiredUsername)
{
    for (int i = 0; i < labWorkerCount; ++i)
    {
        if (strcmp(labWorkers[i].userInfo.username, desiredUsername) == 0)
        {
            return 1; // LabWorker found
        }
    }

    return 0; // LabWorker not found
}

// Function to find a LabWorker by ID and password
struct LabWorker findLabWorker(int LabWorkerId, const char *labWorkerPassword)
{
    struct LabWorker emptyLabWorker = {0};

    for (int i = 0; i < labWorkerCount; ++i)
    {
        labWorkers[i].userInfo.password = malloc(sizeof(200));

        if (labWorkers[i].userInfo.id == LabWorkerId)
        {
            if (strcmp(labWorkers[i].userInfo.password, labWorkerPassword) == 0)
            {
                return labWorkers[i]; // LabWorker found
            }
            else
            {
                // Şifre eşleşmiyor
                break;
            }
        }
    }

    // Return an "empty" LabWorker if not found
    printf("LabWorker not found or password is incorrect.\n");
    return emptyLabWorker;
}

// Function to change the device status
void changeDeviceStatus(char *labWorkerPassword, int LabWorkerId, int DeviceID, const char *deviceName)
{
    // LabWorker'ı bul
    struct LabWorker foundLabWorker = findLabWorker(LabWorkerId, labWorkerPassword);

    // Eğer Device bulunamadıysa
    int deviceIndex = -1; // Bulunamadı durumunu belirtmek için başlangıç değeri

    for (int i = 0; i < Devicessize; ++i)
    {
        devices[i].name = malloc(sizeof(200));
        if (devices[i].id == DeviceID && strcmp(devices[i].name, deviceName) == 0)
        {
            // Device bulunduğunda index'i sakla
            deviceIndex = i;
            break;
        }
    }

    if (deviceIndex != -1)
    {
        // Device found, update status based on entered value
        char status[50];

        printf("Enter the new status for Device ID %d: ", DeviceID);
        scanf("%s", status);

        if (strcmp(status, "inUse") == 0)
        {
            devices[deviceIndex].status = inUse;
        }
        else if (strcmp(status, "broken") == 0)
        {
            devices[deviceIndex].status = broken;
        }
        else if (strcmp(status, "usable") == 0)
        {
            devices[deviceIndex].status = usable;
        }
        else
        {
            printf("Unauthorized status. Allowed statuses: inUse, broken, usable.\n");
        }
    }
    else
    {
        // Device bulunamadıysa
        printf("Device not found.\n");
    }
}

void getInfo(struct LabWorker *labWorker)
{
    printf("ID: %d\n", labWorker->userInfo.id);
    printf("Name: %s\n", labWorker->userInfo.name);
    printf("Username: %s\n", labWorker->userInfo.username);
    printf("Password: %s\n", labWorker->userInfo.password);
    printf("Patient ID: %d\n", labWorker->userInfo.id);
}

void removeLabWorker(int labWorkerId, int userId)
{
    // Kullanıcı ID'sini kontrol et
    for (int i = 0; i < numberOfUsers; ++i)
    {
        if (users[i].id == userId)
        {
            // ID eşleşti, isAdmin kontrolü yap
            if (users[i].isAdmin)
            {
                // LabWorkers dizisinde LabWorker'ı bul
                for (int j = 0; j < labWorkerCount; ++j)
                {
                    if (labWorkers[j].userInfo.id == labWorkerId)
                    {
                        // Sadece belirli labWorkerId'ye sahip olan elemanın tüm üyelerini NULL veya uygun bir başlangıç değeri ile temizle
                        memset(&labWorkers[j].userInfo, 0, sizeof(struct LabWorker));
                        // veya uygun başka bir değerle temizleme yapabilirsiniz

                        // LabWorkers dizisinden LabWorker'ı çıkart
                        for (int k = j; k < labWorkerCount - 1; ++k)
                        {
                            labWorkers[k] = labWorkers[k + 1];
                        }

                        // LabWorker sayısını güncelle
                        --labWorkerCount;

                        // Users dizisinden LabWorker'ı çıkart
                        for (int k = i; k < numberOfUsers - 1; ++k)
                        {
                            users[k] = users[k + 1];
                        }

                        // Users dizisindeki son elemanı temizle
                        memset(&users[numberOfUsers - 1], 0, sizeof(struct User));

                        printf("LabWorker with ID %d removed.\n", labWorkerId);
                        return;
                    }
                }

                // LabWorker bulunamadı
                printf("LabWorker with ID %d not found.\n", labWorkerId);
            }
            else
            {
                // isAdmin false ise yetki hatası ver
                printf("Permission denied. User with ID %d is not an admin.\n", userId);
            }
            return; // İşlem yapıldıktan sonra fonksiyondan çık
        }
    }

    // Kullanıcı bulunamadı
    printf("User with ID %d not found.\n", userId);
}

void setLabWorkerName(struct User *user, const char *name) {
    user->name = (char *)malloc(strlen(name) + 1);
    if (user->name != NULL) {
        strcpy(user->name, name);
    } else {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void setLabWorkerSurname(struct User *user, const char *surname) {
    user->surname = (char *)malloc(strlen(surname) + 1);
    if (user->surname != NULL) {
        strcpy(user->surname, surname);
    } else {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void setLabWorkerUsername(struct User *user, const char *username) {
    user->username = (char *)malloc(strlen(username) + 1);
    if (user->username != NULL) {
        strcpy(user->username, username);
    } else {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void setLabWorkerPassword(struct User *user, const char *password) {
    user->password = (char *)malloc(strlen(password) + 1);
    if (user->password != NULL) {
        strcpy(user->password, password);
    } else {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void setLabWorkerAdminStatus(struct LabWorker *labworker, int userID) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (users[i].id == userID) {
            // ID matched, check if the user is an admin
            if (users[i].isAdmin) {
                // Allocate memory for the isAdmin attribute
                labworker->userInfo.isAdmin = (bool *)malloc(sizeof(bool));
                
                    labworker->userInfo.isAdmin = true;
               
            } else {
                // isAdmin is false, permission error
                printf("Permission denied. User with ID %d is not an admin.\n", userID);
            }
            return; // Exit the function after processing
        }
    }

    printf("User with ID %d not found.\n", userID);
}