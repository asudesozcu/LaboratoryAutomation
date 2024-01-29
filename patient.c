#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"
void addUserPatient(struct Patient *patient);

#define INITIAL_CAPACITY 10

int patientCount = 0;
int patientsCapacity = 0;

void getPatientInfo(int patientID)
{

    for (size_t i = 0; i < patientCount; i++)
    {
        if (patients[i].userInfo.id == patientID)
        {
            // Hastanın bilgilerini konsola yazdır
            printf("Patient Information:\n");
            printf("Username: %s\n", patients[i].userInfo.username);
            printf("Password: %s\n", patients[i].userInfo.password);
            printf("Phone: %s\n", patients[i].userInfo.phone);
            printf("Patient ID: %d\n", patients[i].userInfo.id);
        }
    }
}

void setPatientPassword(struct Patient *patient, const char *newPassword)
{
    // Eğer yeni bir şifre verildiyse, güncelle
    if (newPassword != NULL)
    {
        strcpy(patient->userInfo.password, newPassword);
    }
}

void setPatientPhone(struct Patient *patient, const char *newPhone)
{
    // Eğer yeni bir telefon numarası verildiyse, güncelle
    if (newPhone != NULL)
    {
        strcpy(patient->userInfo.phone, newPhone);
    }
}

void setPatientName(struct Patient *patient, const char *newName)
{
    // Eğer yeni bir isim verildiyse, güncelle
    if (newName != NULL)
    {
        strcpy(patient->userInfo.name, newName);
    }
}

void setPatientSurname(struct Patient *patient, const char *newSurname)
{
    // Eğer yeni bir soyisim verildiyse, güncelle
    if (newSurname != NULL)
    {
        strcpy(patient->userInfo.surname, newSurname);
    }
}

void setPatientDoctor(struct Patient *patient, struct Doctor *doctor)
{
    // Eğer yeni bir doktor bilgisi verildiyse, güncelle
    if (doctor != NULL)
    {
        patient->doctor = doctor;
    }
    addPatient(doctor, patient);
}

void addToPatientsList(struct Patient *existingPatient)
{

    // Eğer dizinin kapasitesi yetersizse genişlet
    if (patientCount >= patientsCapacity)
    {
        if (patientsCapacity == 0)
        {
            patientsCapacity = INITIAL_CAPACITY;
        }
        else
        {
            patientsCapacity += 10;
        }

        
        patients[patientCount] = *existingPatient;
        patientCount++;
    }
    // Mevcut hastayı ekle
}

struct Patient createPatient(const char *username,  int id, const char *password, const char *name, const char *surname, const char *phone)
{    Patient newPatient;

    for (int i = 0; i < numberOfUsers; i++)
    {
        if (users[i].id == id)
        {
            newPatient.userInfo.id=-1;
            printf("This id is already taken.\n");
            return newPatient;
        }
    }
    newPatient.userInfo.name = malloc(sizeof(100));
    newPatient.userInfo.surname = malloc(sizeof(100));
    newPatient.userInfo.username = malloc(sizeof(100));
    newPatient.userInfo.password = malloc(sizeof(100));
    newPatient.userInfo.phone = malloc(sizeof(100));

    strcpy(newPatient.userInfo.username, username);
    strcpy(newPatient.userInfo.password, password);
    strcpy(newPatient.userInfo.name, name);
    strcpy(newPatient.userInfo.surname, surname);
    strcpy(newPatient.userInfo.phone, phone);
    newPatient.userInfo.type = PATIENT;
    newPatient.userInfo.id = id;
    newPatient.myMedicalAnalysis = NULL;
    newPatient.doctor = NULL;

    addToPatientsList(&newPatient);

    addUserPatient(&newPatient);
    return newPatient;
    printf("Patient created!");
}

void removePatientFromList(struct Patient *patientToRemove)
{

    for (size_t i = 0; i < patientCount; ++i)
    {
        if (&patients[i] == patientToRemove)
        {
            memset(&patients[i].userInfo, 0, sizeof(struct Patient));
            // Remove the patient from the array
            for (size_t j = i; j < patientCount - 1; ++j)
            {
                patients[j] = patients[j + 1];
            }

            // Clear the last element in the array
            memset(&patients[patientCount - 1], 0, sizeof(struct Patient));

            // Update the patient count
            --patientCount;

            // Exit the function as the patient is found and removed
            return;
        }
    }

    for (size_t i = 0; i < numberOfUsers; ++i)
    {
        if (users[i].id == patientToRemove->userInfo.id)
        {

            // Remove the user from the array
            for (size_t j = i; j < numberOfUsers - 1; ++j)
            {
                users[j] = users[j + 1];
            }

            // Clear the last element in the array
            memset(&users[numberOfUsers - 1], 0, sizeof(struct User));

            // Update the user count
            --numberOfUsers;

            // Set patientToRemove to NULL after the loop
            patientToRemove = NULL;

            // Exit the function as the user is found and removed
            return;
        }
    }

    // Notify if the patient or user is not found
    printf("Patient or user not found.\n");
}

void addAnalysisToPatient(struct Patient *patient, struct Analysis *newAnalysis)
{

    // NULL kontrolü
    if (patient == NULL || newAnalysis == NULL)
    {
        printf("Invalid arguments for adding analysis to patient.\n");
        return;
    }

    // Yeni boyut hesaplanıyor
    size_t newSize = (patient->analysisCount + 1) * sizeof(struct Analysis);

    // realloc başarısız olursa NULL dönebilir, bu yüzden geçici bir işaretçi kullanıyoruz
    struct Analysis *temp = realloc(patient->myMedicalAnalysis, newSize);

    // realloc başarılı olup olmadığını kontrol et
    patient->myMedicalAnalysis = malloc(sizeof(200));
    if (temp != NULL)
    {
        patient->myMedicalAnalysis = temp;
        patient->myMedicalAnalysis[patient->analysisCount] = *newAnalysis;
        patient->analysisCount++;
        printf("Analysis added to the patient successfully.\n");
    }
    else
    {
        printf("Error allocating memory for patient analyses.\n");

        // Bellek tahsisi başarısız olduysa, mevcut myMedicalAnalysis dizisini serbest bırak
        free(patient->myMedicalAnalysis);
        patient->myMedicalAnalysis = NULL;
    }
}