#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "device.h"
#include "doctor.h"
#include "patient.h"
#include "users.h"
#include "labworker.h"
#include "analysis.h"
void addUserDoctor(struct Doctor *doctor);

struct Doctor doctors[100];
int doctorsCount = 0;
int doctorsCapacity = 0;

int requestBloodAnalysis(int doctorID, int patientID)
{    Analysis *newAnalysis = (Analysis *)malloc(sizeof(Analysis));

    // Belirtilen doktor ID'sine sahip doktoru bul
    struct Doctor *doctor = (struct Doctor *)malloc(sizeof(struct Doctor));
    for (size_t i = 0; i < doctorsCount; ++i)
    {
        if (doctors[i].userInfo.id == doctorID)
        {
            doctor = &doctors[i];
            break;
        }
    }

    if (doctor == NULL)
    {
        printf("Doctor not found with ID %d.\n", doctorID);
        return 0 ;
    }

    // Dynamically allocate memory for the patient
    struct Patient *patient = (struct Patient *)malloc(sizeof(struct Patient));
    if (patient == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < patientCount; ++i)
    {
        if (patients[i].userInfo.id == patientID)
        {
            patient = &patients[i];
            break;
        }
    }

    if (patient == NULL)
    {
        printf("Patient not found with ID %d.\n", patientID);
        free(patient); // Free allocated memory before returning
        return 0;
    }

    // Test adlarını yazdır
    printf("Available blood tests:\n");
    ExaminationList bloodTests = createExaminationList(BLOOD);
    for (size_t i = 0; i < bloodTests.count; i++)
    {
        printf("%d. %s\n", i + 1, bloodTests.examinations[i]);
    }

    // Kullanıcıdan test seçmesini iste
    printf("Select a blood test (1-%zu): ", bloodTests.count);
    size_t selectedTestIndex;
    scanf("%zu", &selectedTestIndex);

    // Seçilen test adını yazdır
    printf("Selected blood test: %s\n", bloodTests.examinations[selectedTestIndex - 1]);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Dynamically allocate memory for the date
    char *date = (char *)malloc(21 * sizeof(char)); // YYYY-MM-DD HH:MM:SS formatında tarih için 20 karakterlik bir dizi
    if (date == NULL)
    {
        printf("Memory allocation failed\n");
        free(patient); // Free allocated memory before returning
        exit(EXIT_FAILURE);
    }

    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

    // Dynamically allocate memory for the analysis
    if (newAnalysis == NULL)
    {
        printf("Memory allocation failed\n");
        free(patient); // Free allocated memory before returning
        free(date);
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate memory for the examination
    newAnalysis->examinationlist = (ExaminationList *)malloc(sizeof(ExaminationList));
    if (newAnalysis->examinationlist == NULL)
    {
        printf("Memory allocation failed\n");
        free(patient); // Free allocated memory before returning
        free(date);
        free(newAnalysis);
        exit(EXIT_FAILURE);
    }

    newAnalysis->doctor = doctor;
    newAnalysis->date = date;
    newAnalysis->patient = patient;
    newAnalysis->type = BLOOD;
    newAnalysis->id = numAnalyses + 1;
    printf("%s requests blood analysis for Patient ID %d\n", doctor->userInfo.name, patient->userInfo.id);

    // Dynamically allocate memory for the examination name
    newAnalysis->examinationlist->examinations = (char **)malloc(strlen(bloodExaminations[selectedTestIndex]) + 1);
    if (newAnalysis->examinationlist->examinations == NULL)
    {
        printf("Memory allocation failed\n");
        free(patient); // Free allocated memory before returning
        free(date);
        free(newAnalysis->examinationlist);
        free(newAnalysis);
        exit(EXIT_FAILURE);
    }

    newAnalysis->examinationlist->examinations[0] = bloodExaminations[selectedTestIndex];

    numAnalyses++;
    // Analizi array'e ekle
    addAnalysisToList(newAnalysis);
    addAnalysisToPatient(patient, newAnalysis);
    return newAnalysis->id;
    // Analiz talebini oluştur
    printf("%s requests blood analysis for Patient ID %d\n", doctor->userInfo.name, patient->userInfo.id);
}

static void requestUrineAnalysis(struct Doctor *doctor, int patientID)
{

    
    struct Patient *patient;
    for (size_t i = 0; i < patientCount; ++i)
    {
        if (patients[i].userInfo.id == patientID)
        {
            patient = &patients[i];
            break;
        }
    }

    // Test adlarını yazdır
    printf("Available urine tests:\n");
    ExaminationList urineTests = createExaminationList(URINE);
    for (size_t i = 0; i < urineTests.count; ++i)
    {
        printf("%d. %s\n", i + 1, urineTests.examinations[i]);
    }

    // Kullanıcıdan test seçmesini iste
    printf("Select a urine test (1-%zu): ", urineTests.count);
    size_t selectedTestIndex;
    scanf("%zu", &selectedTestIndex);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char date[20]; // YYYY-MM-DD HH:MM:SS formatında tarih için 20 karakterlik bir dizi
    strftime(date, 21, "%Y-%m-%d %H:%M:%S", &tm);

    Analysis *newAnalysis = (Analysis *)malloc(sizeof(Analysis));
    if (newAnalysis == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newAnalysis->doctor = doctor;
    newAnalysis->date = (char *)malloc(21 * sizeof(char)); // Allocate memory for the date
    if (newAnalysis->date == NULL)
    {
        printf("Memory allocation failed\n");
        free(newAnalysis);
        exit(EXIT_FAILURE);
    }

    strcpy(newAnalysis->date, date);

    newAnalysis->patient = patient;
    newAnalysis->type = URINE;
    

    // Allocate memory for the examinationlist
    newAnalysis->examinationlist = (ExaminationList *)malloc(sizeof(ExaminationList));
    if (newAnalysis->examinationlist == NULL)
    {
        printf("Memory allocation failed\n");
        free(newAnalysis->date);
        free(newAnalysis);
        exit(EXIT_FAILURE);
    }
    // Allocate memory for the examinations array
    newAnalysis->examinationlist->examinations = (char **)malloc(strlen(urineExaminations[selectedTestIndex]) + 1);
    if (newAnalysis->examinationlist->examinations == NULL)
    {
        printf("Memory allocation failed\n");
        free(newAnalysis->date);
        free(newAnalysis->examinationlist);
        free(newAnalysis);
        exit(EXIT_FAILURE);
    }

    newAnalysis->examinationlist->examinations[0] = urineExaminations[selectedTestIndex];
    printf("%s requests %s for Patient ID %d\n", doctor->userInfo.name, urineTests.examinations[selectedTestIndex - 1], patientID);

    numAnalyses++;
    // Analizi array'e ekle
    addAnalysisToList(newAnalysis);
    addAnalysisToPatient(patient, newAnalysis);

    
}

void addPatient(struct Doctor *self, struct Patient *patient)
{
    // Hastayı doktorun listesine ekleyerek başarılı bir şekilde eklediğimizi gösterir
    // Doktorun hastalar dizisini dinamik olarak genişlet
    if (self->patientCount >= self->capacity)
    {
        self->capacity += 10;
        struct Patient *newPatients = (struct Patient *)realloc(self->patients, self->capacity * sizeof(struct Patient));

        if (newPatients == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        self->patients = newPatients;
    }

    // Hasta ekleyerek başarılı bir şekilde eklediğimizi gösterir
    self->patients[self->patientCount++] = *patient;
    printf("Hasta eklenmiştir.\n");
}

struct Doctor createDoctor(char *title, int id, const char *name, const char *surname, const char *password, const char *username, const char *phone)
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (users[i].id == id)
        {
            printf("Hata: This id is already in use.\n");
            // Hata durumu için NULL döndür
            struct Doctor nullDoctor = {0}; // veya NULL, başka bir değer
            return nullDoctor;
        }
    }

    struct Doctor *newDoctor = (struct Doctor *)calloc(1, sizeof(struct Doctor));

    newDoctor->userInfo.type = DOCTOR;

    newDoctor->userInfo.name = (char *)malloc(strlen(name) + 1);
    newDoctor->userInfo.surname = (char *)malloc(strlen(surname) + 1);
    newDoctor->userInfo.username = (char *)malloc(strlen(username) + 1);
    newDoctor->userInfo.password = (char *)malloc(strlen(password) + 1);
    newDoctor->userInfo.phone = (char *)malloc(strlen(phone) + 1);

    // Kullanıcı bilgilerini ayarla
    strcpy(newDoctor->title, title);
    newDoctor->userInfo.id = id; // tamsayıyı doğrudan atama yap

    strcpy(newDoctor->userInfo.name, name);
    strcpy(newDoctor->userInfo.surname, surname);
    strcpy(newDoctor->userInfo.password, password);
    strcpy(newDoctor->userInfo.username, username);
    strcpy(newDoctor->userInfo.phone, phone);
    newDoctor->userInfo.type = DOCTOR; // enum'u doğrudan atama yap

    newDoctor->patients = NULL;
    newDoctor->patientCount = 0;
    newDoctor->requestBloodAnalysis = NULL;
    newDoctor->requestUrineAnalysis = NULL;

    addUserDoctor(newDoctor);
    addDoctortoDoctorsArray(newDoctor);

    return *newDoctor;
}

void addDoctortoDoctorsArray(struct Doctor *existingDoctor)
{
    if (doctorsCount >= doctorsCapacity)
    {
        // Doktorlar dizisini genişlet
        if (doctorsCapacity == 0)
        {
            doctorsCapacity = INITIAL_CAPACITY;
        }
        else
        {
            doctorsCapacity += 2;
        }

        if (doctors == NULL)
        {
            printf("Problem in memory allocation\n");
            return;
        }
    }

    // Doktoru ekleyerek başarılı bir şekilde eklediğimizi gösterir
    doctors[doctorsCount++] = *existingDoctor;
    doctorsCount++;
}
void deleteDoctor(int doctorID, int adminID)
{
    for (int i = 0; i < numberOfUsers; ++i)
    {
        if (users[i].id == adminID && users[i].isAdmin)
        {
            // Admin user found with matching ID and isAdmin true

            // Check if the doctor exists in the doctors array
            for (int j = 0; j < doctorsCount; ++j)
            {
                if (doctors[j].userInfo.id == doctorID)
                {
                    // Dynamically allocate memory for a new array of doctors
                    struct Doctor *newDoctors = (struct Doctor *)malloc((doctorsCount - 1) * sizeof(struct Doctor));
                    if (newDoctors == NULL)
                    {
                        printf("Memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }

                    // Copy doctors before the deleted doctor to the new array
                    for (int k = 0; k < j; ++k)
                    {
                        newDoctors[k] = doctors[k];
                    }

                    // Copy doctors after the deleted doctor to the new array
                    for (int k = j + 1; k < doctorsCount; ++k)
                    {
                        newDoctors[k - 1] = doctors[k];
                    }

                    // Free the memory of the old doctors array

                    // Update the doctors array with the new array

                    // Clear the last element in the users array
                    memset(&users[numberOfUsers - 1], 0, sizeof(struct User));

                    // Update the user count
                    --numberOfUsers;

                    // Update the doctor count
                    --doctorsCount;

                    // Exit the function as the doctor is found and removed
                    return;
                }
            }

            // Doctor not found
            printf("Doctor with ID %d not found.\n", doctorID);
            return;
        }
    }

    // Admin user not found or isAdmin is false
    printf("Permission denied. User with ID %d is not an admin.\n", adminID);
}

void DoctorInfo(struct Doctor *doctor)
{
    printf("Doktor Bilgileri:\n");
    printf("Title: %s\n", doctor->title);
    printf("Name: %s\n", doctor->userInfo.name);
    printf("Surname: %s\n", doctor->userInfo.surname);
    printf("Password: %s\n", doctor->userInfo.password);
    printf("Username: %s\n", doctor->userInfo.username);
    printf("Phone: %s\n", doctor->userInfo.phone);
}

void setName(struct Doctor *doctor, const char *name)
{
    // Allocate memory for the name
    doctor->userInfo.name = (char *)malloc(strlen(name) + 1);
    if (doctor->userInfo.name == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(doctor->userInfo.name, name);
}

void setSurname(struct Doctor *doctor, const char *surname)
{
    // Allocate memory for the surname
    doctor->userInfo.surname = (char *)malloc(strlen(surname) + 1);
    if (doctor->userInfo.surname == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(doctor->userInfo.surname, surname);
}

void setPassword(struct Doctor *doctor, const char *password)
{
    // Allocate memory for the password
    doctor->userInfo.password = (char *)malloc(strlen(password) + 1);
    if (doctor->userInfo.password == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(doctor->userInfo.password, password);
}

void setUsername(struct Doctor *doctor, const char *username)
{
    // Allocate memory for the username
    doctor->userInfo.username = (char *)malloc(strlen(username) + 1);
    if (doctor->userInfo.username == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(doctor->userInfo.username, username);
}

void setPhone(struct Doctor *doctor, const char *phone)
{
    // Allocate memory for the phone
    doctor->userInfo.phone = (char *)malloc(strlen(phone) + 1);
    if (doctor->userInfo.phone == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(doctor->userInfo.phone, phone);
}

void printPatientInfo(const struct Patient *patient)
{
    printf("Patient Information:\n");
    printf("ID: %d\n", patient->userInfo.id);
    printf("Name: %s\n", patient->userInfo.name);
    printf("Surname: %s\n", patient->userInfo.surname);
    printf("Password: %s\n", patient->userInfo.password);
    printf("Phone: %s\n", patient->userInfo.phone);
    printf("Doctor: %s\n", patient->doctor ? patient->doctor->userInfo.name : "Not avalaible");
    printf("\n");
}

// Doktorun hastalarını yazdırır
void printDoctorPatients(const struct Doctor *doctor)
{
    printf("Doctor's Patients:\n");
    for (int i = 0; i < doctor->patientCount; ++i)
    {
        printPatientInfo(&doctor->patients[i]);
    }
}