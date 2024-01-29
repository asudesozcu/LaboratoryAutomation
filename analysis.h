#ifndef ANALIZ_H
#define ANALIZ_H
#define INITIAL_CAPACITY 10





typedef enum {
    BLOOD,
    URINE
} AnalysisType;

typedef enum {
    LOW,
    NORMAL,
    HIGH
} ResultType;

typedef enum {
    INPROGRESS,
    TESTCONCLUDED
} AnalysisStatus;



typedef struct Analysis{
    AnalysisType type;
    ResultType result;
    AnalysisStatus status;
     char *date;
    struct Doctor *doctor;
    struct Patient *patient;
    int id;
    double resultvalue;
    struct ExaminationList *examinationlist;
} Analysis;


typedef struct ExaminationList {
     char **examinations;
    int count;
} ExaminationList;


extern  struct Analysis *allAnalysis;
int numAnalyses ;
int analysesCapacity ;
extern  char *bloodExaminations[];
extern  char *urineExaminations[];

void setAnalysisStatus(int analysisid);
ExaminationList createExaminationList(AnalysisType analysisType);
void printAnalyses(struct Analysis *existingAnalysis);
void addAnalysisToList(struct Analysis *existingAnalysis);


void writeAnalysisToFile(int UserID, struct Analysis *analysize);
#endif