// labworker.h
#ifndef LABWORKER_H
#define LABWORKER_H

#include "users.h"

typedef struct LabWorker{
    struct User userInfo;

}LabWorker;

extern struct LabWorker *labWorkers;
extern int labWorkerCount;
extern int labWorkerCapacity;

void createLabWorker(const char *username, const long id, const char *password, const char *name, const char *surname, const char *phone);
void addToWorkersList(struct LabWorker *existingWorker);

int labWorkerExists(const char *desiredUsername);
// Function to find a LabWorker by ID and password
struct LabWorker findLabWorker(int LabWorkerId, const char *labWorkerPassword) ;
// Function to change the device status
void changeDeviceStatus(char *labWorkerPassword, int LabWorkerId, int DeviceID, const char *deviceName);
void getInfo(struct LabWorker *labWorker);
void removeLabWorker(int LabWorkerId, int userID);

void setLabWorkerPassword(struct User *user, const char *password);
void setLabWorkerName(struct User *user, const char *name);
void setLabWorkerSurname(struct User *user, const char *surname);
void setLabWorkerUsername(struct User *user, const char *username);


void setLabWorkerAdminStatus(struct LabWorker *labworker, int userID);
#endif 
