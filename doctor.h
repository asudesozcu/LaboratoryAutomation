#ifndef DOCTOR_H
#define DOCTOR_H
#include "users.h"
#define INITIAL_CAPACITY 10


typedef struct Doctor
{
    struct User userInfo;
    struct Patient *patients;
    int patientCount;
    int capacity;
    char title[20];
    void (*requestBloodAnalysis)(int doctorID, int patientID, const char *surname);
    void (*requestUrineAnalysis)(int doctorid, int doctorPassword, int patientID, const char *surname);
    void (*addPatient)(struct Doctor *self, struct Patient *patient);
}Doctor;

 extern struct Doctor doctors[];
 extern int doctorsCount;
 extern int doctorsCapacity;

int requestBloodAnalysis(int doctorID, int patientID);
static void requestUrineAnalysis(struct Doctor *doctor, int patientID);

void addPatient(struct Doctor *self, struct Patient *patient);
struct Doctor createDoctor( char *title, int id, const char *name, const char *surname, const char *password, const char *username, const char *phone);
void addDoctortoDoctorsArray(struct Doctor *existingDoctor);
void deleteDoctor(int doctorID, int AdminID);
void DoctorInfo(struct Doctor *doctor);

void setName(struct Doctor *doctor, const char *name);
void setSurname(struct Doctor *doctor, const char *surname);
void setPassword(struct Doctor *doctor, const char *password);
void setUsername(struct Doctor *doctor, const char *username);
void setPhone(struct Doctor *doctor, const char *phone);

void printPatientInfo(const struct Patient *patient);
void printDoctorPatients(const struct Doctor *doctor);




#endif