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

#define INITIAL_CAPACITY 10

struct Analysis *allAnalysis;

int numAnalyses = 0;
int analysesCapacity = 0;

char *bloodExaminations[] = {"WBC", "NEU", "LYM", "MONO", "EOS",
                             "BASO", "RBC", "HGB", "HCT", "MCV"};

char *urineExaminations[] = {"Glukoz", "Protein", "Bilirubin",
                             "Urobilinojen", "pH", "Hemoglobin", "Keton", "Nitrit", "Lokosit Esteraz", "Density"};

#define MIN_TEST_WBC 4.0
#define MAX_TEST_WBC 10.0

#define MIN_TEST_NEU 1.5
#define MAX_TEST_NEU 7.5

#define MIN_TEST_LYM 1.0
#define MAX_TEST_LYM 4.0

#define MIN_TEST_MONO 0.1
#define MAX_TEST_MONO 0.8

#define MIN_TEST_EOS 0.05
#define MAX_TEST_EOS 0.5

#define MIN_TEST_BASO 0.01
#define MAX_TEST_BASO 0.1

#define MIN_TEST_RBC 4.2
#define MAX_TEST_RBC 5.6

#define MIN_TEST_HGB 13.0
#define MAX_TEST_HGB 17.0

#define MIN_TEST_HCT 38.0
#define MAX_TEST_HCT 50.0

#define MIN_TEST_MCV 80.0
#define MAX_TEST_MCV 100.0

#define MIN_TEST_GLUCOSE 70.0
#define MAX_TEST_GLUCOSE 100.0

#define MIN_TEST_PROTEIN 6.0
#define MAX_TEST_PROTEIN 8.3

#define MIN_TEST_BILIRUBIN 0.1
#define MAX_TEST_BILIRUBIN 1.0

#define MIN_TEST_UROBILINOGEN 0.1
#define MAX_TEST_UROBILINOGEN 1.0

#define MIN_TEST_PH 4.5
#define MAX_TEST_PH 8.0

#define MIN_TEST_HEMOGLOBIN 12.0
#define MAX_TEST_HEMOGLOBIN 16.0

#define MIN_TEST_KETONE 0.0
#define MAX_TEST_KETONE 0.5

#define MIN_TEST_NITRITE 0.0
#define MAX_TEST_NITRITE 0.1

#define MIN_TEST_LEUKOCYTE_ESTERASE 0.0
#define MAX_TEST_LEUKOCYTE_ESTERASE 1.0

#define MIN_TEST_DENSITY 1.005
#define MAX_TEST_DENSITY 1.030

double MIN_TEST(const char *test)
{
    if (strcmp(test, "WBC") == 0)
    {
        return MIN_TEST_WBC;
    }
    else if (strcmp(test, "NEU") == 0)
    {
        return MIN_TEST_NEU;
    }
    else if (strcmp(test, "DENSITY") == 0)
    {
        return MIN_TEST_DENSITY;
    }
    else if (strcmp(test, "LEUKOCYTE_ESTERASE") == 0)
    {
        return MIN_TEST_LEUKOCYTE_ESTERASE;
    }
    else if (strcmp(test, "NITRITE") == 0)
    {
        return MIN_TEST_NITRITE;
    }
    else if (strcmp(test, "KETONE") == 0)
    {
        return MIN_TEST_KETONE;
    }
    else if (strcmp(test, "HEMOGLOBIN") == 0)
    {
        return MIN_TEST_HEMOGLOBIN;
    }
    else if (strcmp(test, "PH") == 0)
    {
        return MIN_TEST_PH;
    }
    else if (strcmp(test, "UROBILINOGEN") == 0)
    {
        return MIN_TEST_UROBILINOGEN;
    }
    else if (strcmp(test, "BILIRUBIN") == 0)
    {
        return MIN_TEST_BILIRUBIN;
    }
    else if (strcmp(test, "PROTEIN") == 0)
    {
        return MIN_TEST_PROTEIN;
    }
    else if (strcmp(test, "GLUCOSE") == 0)
    {
        return MIN_TEST_GLUCOSE;
    }
    else if (strcmp(test, "MVC") == 0)
    {
        return MIN_TEST_MCV;
    }
    else if (strcmp(test, "LYM") == 0)
    {
        return MIN_TEST_LYM;
    }
    else if (strcmp(test, "HCT") == 0)
    {
        return MIN_TEST_HCT;
    }
    else if (strcmp(test, "HGB") == 0)
    {
        return MIN_TEST_HGB;
    }
    else if (strcmp(test, "RBC") == 0)
    {
        return MIN_TEST_RBC;
    }
    else if (strcmp(test, "BASO") == 0)
    {
        return MIN_TEST_BASO;
    }
    else if (strcmp(test, "EOS") == 0)
    {
        return MIN_TEST_EOS;
    }
    else if (strcmp(test, "MONO") == 0)
    {
        return MIN_TEST_MONO;
    }
}

double MAX_TEST(const char *test)
{
    if (strcmp(test, "WBC") == 0)
    {
        return MAX_TEST_WBC;
    }
    else if (strcmp(test, "NEU") == 0)
    {
        return MAX_TEST_NEU;
    }
    else if (strcmp(test, "DENSITY") == 0)
    {
        return MAX_TEST_DENSITY;
    }
    else if (strcmp(test, "LEUKOCYTE_ESTERASE") == 0)
    {
        return MAX_TEST_LEUKOCYTE_ESTERASE;
    }
    else if (strcmp(test, "NITRITE") == 0)
    {
        return MAX_TEST_NITRITE;
    }
    else if (strcmp(test, "KETONE") == 0)
    {
        return MAX_TEST_KETONE;
    }
    else if (strcmp(test, "HEMOGLOBIN") == 0)
    {
        return MAX_TEST_HEMOGLOBIN;
    }
    else if (strcmp(test, "PH") == 0)
    {
        return MAX_TEST_PH;
    }
    else if (strcmp(test, "UROBILINOGEN") == 0)
    {
        return MAX_TEST_UROBILINOGEN;
    }
    else if (strcmp(test, "BILIRUBIN") == 0)
    {
        return MAX_TEST_BILIRUBIN;
    }
    else if (strcmp(test, "PROTEIN") == 0)
    {
        return MAX_TEST_PROTEIN;
    }
    else if (strcmp(test, "GLUCOSE") == 0)
    {
        return MAX_TEST_GLUCOSE;
    }
    else if (strcmp(test, "MVC") == 0)
    {
        return MAX_TEST_MCV;
    }
    else if (strcmp(test, "LYM") == 0)
    {
        return MAX_TEST_LYM;
    }
    else if (strcmp(test, "HCT") == 0)
    {
        return MAX_TEST_HCT;
    }
    else if (strcmp(test, "HGB") == 0)
    {
        return MAX_TEST_HGB;
    }
    else if (strcmp(test, "RBC") == 0)
    {
        return MAX_TEST_RBC;
    }
    else if (strcmp(test, "BASO") == 0)
    {
        return MAX_TEST_BASO;
    }
    else if (strcmp(test, "EOS") == 0)
    {
        return MAX_TEST_EOS;
    }
    else if (strcmp(test, "MONO") == 0)
    {
        return MAX_TEST_MONO;
    }
}

void setAnalysisStatus(int analysisid)
{

    for (size_t i = 0; i < numAnalyses; i++)
    {
        if (allAnalysis[i].id == analysisid)
        {
            // Analysis found, proceed with setting status
            for (size_t k = 0; k < allAnalysis[i].examinationlist->count; k++)
            {
                const char *currentTest = allAnalysis[i].examinationlist->examinations[i];

                double minNormalValue = MIN_TEST(currentTest);
                double maxNormalValue = MAX_TEST(currentTest);

                if (allAnalysis[i].resultvalue < minNormalValue)
                {
                    allAnalysis[i].type = LOW;
                }
                else if (allAnalysis[i].resultvalue > maxNormalValue)
                {
                    allAnalysis[i].type = HIGH;
                }
                else
                {
                    allAnalysis[i].resultvalue = NORMAL;
                }
            }
            printf("Analysis Type for ID %d set successfully.\n", analysisid);
            return; // Exit function after setting status
        }
    }
    // Analysis ID not found
    printf("Error: Analysis with ID %d not found.\n", analysisid);
    return;
}

ExaminationList createExaminationList(AnalysisType analysisType)
{
    ExaminationList list;

    switch (analysisType)
    {
    case BLOOD:
        list.count = sizeof(bloodExaminations) / sizeof(bloodExaminations[0]);
        list.examinations = (char **)malloc(list.count * sizeof(char *));
        if (list.examinations == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < list.count; ++i)
        {
            list.examinations[i] = strdup(bloodExaminations[i]);
            if (list.examinations[i] == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }
        break;
    case URINE:
        list.count = sizeof(urineExaminations) / sizeof(urineExaminations[0]);
        list.examinations = (char **)malloc(list.count * sizeof(char *));
        if (list.examinations == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < list.count; ++i)
        {
            list.examinations[i] = strdup(urineExaminations[i]);
            if (list.examinations[i] == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }
        break;
    default:
        list.examinations = NULL;
        list.count = 0;
        break;
    }

    return list;
}

void printAnalyses(struct Analysis *existingAnalysis)
{
   
    for (size_t i = 0; i < doctorsCount; ++i)
    {    

        if (doctors[i].userInfo.id == existingAnalysis->doctor->userInfo.id)
        {
            printf("ID: %d\n", existingAnalysis->id);
            printf("Doctor: %s\n", existingAnalysis->doctor->userInfo.name);
            printf("Type: %s\n", existingAnalysis->type == BLOOD ? "Blood" : "Urine");
            printf("Date: %s\n", existingAnalysis->date);
            printf("Result: %s\n", existingAnalysis->result);
            printf("Status: %s\n", existingAnalysis->status);
            
        }break;
    }

    for (size_t i = 0; i < patientCount; ++i)
    {   

        if (patients[i].userInfo.id == existingAnalysis->patient->userInfo.id)
        {    
            printf("ID: %d\n", existingAnalysis->id);
            printf("Doctor: %s\n", existingAnalysis->doctor->userInfo.name);
            printf("Type: %s\n", existingAnalysis->type == BLOOD ? "Blood" : "Urine");
            printf("Date: %s\n", existingAnalysis->date);
            printf("Result: %s\n", existingAnalysis->result);
            printf("Status: %s\n", existingAnalysis->status);
            printf("Patient: %s\n", existingAnalysis->patient->userInfo.name);
           
        }break;
    }
}

void addAnalysisToList(struct Analysis *existingAnalysis)
{
    if (numAnalyses >= analysesCapacity)
    {
        // Expand the analyses array
        if (analysesCapacity == 0)
        {
            analysesCapacity = INITIAL_CAPACITY;
        }
        else
        {
            analysesCapacity += 2;
        }

        struct Analysis *newAnalysis = realloc(allAnalysis, analysesCapacity * sizeof(Analysis));
        if (newAnalysis == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        allAnalysis = newAnalysis;
    }
    // Set the ID and add the analysis
    allAnalysis[numAnalyses++] = *existingAnalysis;
    printf("Analysis has been added to the general list.\n");
}

/* void writeAnalysisToFile(int UserID, struct Analysis *analysize)
{
    // Analizi bul
    if (analysize == NULL)
    {
        printf("Analysis with ID %d not found.\n", analysize->id);
        return;
    }

    if (UserID == analysize->doctor->userInfo.id || UserID == analysize->patient->userInfo.id)
    {   

        // Check if the patient is deleted (userInfo is NULL)
        if (analysize->patient->userInfo.id == 0 || analysize->doctor->userInfo.id == 0)
        {
            printf("Patient or doctor has been deleted. Analysis with ID %d cannot be written to file.\n", analysize->id);
            return;
        }

        // Dynamic memory allocation for file name
        char *fileName = malloc(50);
        if (fileName == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

       

        FILE *file = fopen("analyses.txt", "w");
        if (file == NULL)
        { 
            perror("Error opening file");
            return;
        }

        // Dynamic memory allocation for strings
        char *doctorInfo = malloc(strlen(analysize->doctor->userInfo.name) + strlen(analysize->doctor->userInfo.surname) + 3);
        char *patientInfo = malloc(strlen(analysize->patient->userInfo.name) + strlen(analysize->patient->userInfo.surname) + 12);

        if (doctorInfo == NULL || patientInfo == NULL)
        {
            perror("Memory allocation error");
            free(fileName);
            free(doctorInfo); // Free dynamically allocated memory in case of an error
            free(patientInfo);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Format strings
        sprintf(doctorInfo, "%s %s", analysize->doctor->userInfo.name, analysize->doctor->userInfo.surname);
        sprintf(patientInfo, "%s %s %d", analysize->patient->userInfo.name, analysize->patient->userInfo.surname, analysize->patient->userInfo.id);

        // Analiz bilgilerini dosyaya yaz
        fprintf(file, "Analysis ID: %d\n", analysize->id);

        // Doktorun bilgilerini dosyaya yaz
        fprintf(file, "Doctor: %s\n", doctorInfo);

        // Hastanın bilgilerini dosyaya yaz
        fprintf(file, "Patient: %s\n", patientInfo);

        // Analiz sonuçlarını dosyaya yaz
        fprintf(file, "Type: %s\n", analysize->type == BLOOD ? "Blood" : "Urine");
        fprintf(file, "Date: %s\n", analysize->date);
        fprintf(file, "Result:%s\n", analysize->result);
        fprintf(file, "Status:%s\n", analysize->status);
        printf("ok5");

        // Dosyayı kapat
        fclose(file);

        // Free dynamically allocated memory
        free(fileName);
        free(doctorInfo);
        free(patientInfo);

        printf("Analysis details written to file.\n");
    }
    else
    {
        printf("File is accessible only for doctor and patient.\n");
    }
} */