#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"

#define INITIAL_CAPACITY 10
struct User users[100];
int numberOfUsers = 0;
int capacity = 0;

const char *accountTypeToString(AccountType type)
{
    switch (type)
    {
    case PATIENT:
        return "PATIENT";
    case DOCTOR:
        return "DOCTOR";
    case LABMAN:
        return "LABMAN";
    default:
        return "PATIENT";
    }
}
struct User *verifyUser(const char *inputUsername, const char *inputPassword)
{
    for (int i = 0; i < numberOfUsers; ++i)
    {
        
        
        if (strcmp(inputUsername, users[i].username) == 0 &&
            strcmp(inputPassword, users[i].password) == 0)
        {
            return &users[i]; // Kullanıcı bulundu, kullanıcı bilgilerini döndür
        }
    }

    return NULL; // Kullanıcı bulunamadı veya şifre yanlış
}
struct Patient *verifyPatient(const char *inputUsername, const char *inputPassword)
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (strcmp(inputUsername, patients[i].userInfo.username) == 0 &&
            strcmp(inputPassword, patients[i].userInfo.password) == 0)
        {
            return &patients[i]; // Patient found, return patient information
        }
    }

    return NULL; // Patient not found or password is incorrect
}


struct Doctor *verifyDoctor(const char *inputUsername, const char *inputPassword)
{
    for (int i = 0; i < doctorsCount; ++i)
    {
        doctors[i].userInfo.password = malloc(sizeof(200));
        doctors[i].userInfo.username = malloc(sizeof(200));
        if (strcmp(inputUsername, doctors[i].userInfo.username) == 0 &&
            strcmp(inputPassword, doctors[i].userInfo.password) == 0)
        {
            return &doctors[i];
        }
    }

    return NULL; // Kullanıcı bulunamadı veya şifre yanlış
}
struct LabWorker *verifyLabWorker(const char *inputUsername, const char *inputPassword)
{
    for (int i = 0; i < labWorkerCount; ++i)
    {
        labWorkers[i].userInfo.password = malloc(sizeof(200));
        labWorkers[i].userInfo.username = malloc(sizeof(200));
        if (strcmp(inputUsername, labWorkers[i].userInfo.username) == 0 &&
            strcmp(inputPassword, labWorkers[i].userInfo.password) == 0)
        {
            return &labWorkers[i];
        }
    }

    return NULL; // Kullanıcı bulunamadı veya şifre yanlış
}

extern void addUserLabWorker(struct LabWorker *labWorker)
{
    struct User *newuser = (struct User *)malloc(sizeof(struct User));
    if (newuser == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newuser->name = (char *)malloc(strlen(labWorker->userInfo.name) + 1);
    newuser->surname = (char *)malloc(strlen(labWorker->userInfo.surname) + 1);
    newuser->username = (char *)malloc(strlen(labWorker->userInfo.username) + 1);
    newuser->password = (char *)malloc(strlen(labWorker->userInfo.password) + 1);
    newuser->phone = (char *)malloc(strlen(labWorker->userInfo.phone) + 1);

    newuser->id = labWorker->userInfo.id;
    strcpy(newuser->name, labWorker->userInfo.name);
    strcpy(newuser->surname, labWorker->userInfo.surname);
    strcpy(newuser->username, labWorker->userInfo.username);
    strcpy(newuser->password, labWorker->userInfo.password);
    strcpy(newuser->phone, labWorker->userInfo.phone);
    newuser->isAdmin = labWorker->userInfo.isAdmin;
    newuser->type = LABMAN;

    users[numberOfUsers] = *newuser;
    (numberOfUsers)++;

}
// Function to add a patient
 void addUserPatient(struct Patient *patient)
{
    struct User *newuser = (struct User *)malloc(sizeof(struct User));
    if (newuser == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    newuser->id = patient->userInfo.id;
   newuser->name = (char *)malloc(strlen(patient->userInfo.name) + 1);
    newuser->surname = (char *)malloc(strlen(patient->userInfo.surname) + 1);
    newuser->username = (char *)malloc(strlen(patient->userInfo.username) + 1);
    newuser->password = (char *)malloc(strlen(patient->userInfo.password) + 1);
    newuser->phone = (char *)malloc(strlen(patient->userInfo.phone) + 1);


    newuser->id = patient->userInfo.id;
    strcpy(newuser->name, patient->userInfo.name);
    strcpy(newuser->surname, patient->userInfo.surname);
    strcpy(newuser->username, patient->userInfo.username);
    strcpy(newuser->password, patient->userInfo.password);
    strcpy(newuser->phone, patient->userInfo.phone);
    newuser->isAdmin = patient->userInfo.isAdmin;
    newuser->type = PATIENT;
    users[numberOfUsers] = *newuser;
    (numberOfUsers)++;
}

// Function to add a doctor
 void addUserDoctor(struct Doctor *doctor)
{
    struct User *newuser = (struct User *)malloc(sizeof(struct User));
    if (newuser == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newuser->name = (char *)malloc(strlen(doctor->userInfo.name) + 1);
    newuser->surname = (char *)malloc(strlen(doctor->userInfo.surname) + 1);
    newuser->username = (char *)malloc(strlen(doctor->userInfo.username) + 1);
    newuser->password = (char *)malloc(strlen(doctor->userInfo.password) + 1);
    newuser->phone = (char *)malloc(strlen(doctor->userInfo.phone) + 1);

    newuser->id = doctor->userInfo.id;
    strcpy(newuser->name, doctor->userInfo.name);
    strcpy(newuser->surname, doctor->userInfo.surname);
    strcpy(newuser->username, doctor->userInfo.username);
    strcpy(newuser->password, doctor->userInfo.password);
    strcpy(newuser->phone, doctor->userInfo.phone);
    newuser->isAdmin = doctor->userInfo.isAdmin;
    newuser->type = DOCTOR;

    users[numberOfUsers] = *newuser;
    (numberOfUsers)++;
}
