#ifndef PATIENT_H
#define PATIENT_H


typedef struct Patient {
    struct User userInfo;
    struct Analysis *myMedicalAnalysis; // MedicalAnalysis struct'ının bir pointer'ı
    struct Doctor *doctor;
    int analysisCount;
} Patient;

  struct Patient patients[500];
extern int patientCount;
extern int patientsCapacity;
 
void getPatientInfo( int patientID);
void setPatientPassword(struct Patient *patient, const char *newPassword);
void setPatientPhone(struct Patient *patient, const char *newPhone);
void setPatientName(struct Patient *patient, const char *newName);
void setPatientSurname(struct Patient *patient, const char *newSurname);
void setPatientDoctor(struct Patient *patient, struct Doctor *doctor);
void addToPatientsList(struct Patient *existingPatient);
struct Patient createPatient(const char *username,  int id, const char *password, const char *name, const char *surname, const char *phone);
void removePatientFromList(struct Patient *patientToRemove);
void addAnalysisToPatient(struct Patient *patient, struct Analysis *newAnalysis);



#endif 
