#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "device.c"
#include "doctor.c"
#include "patient.c"
#include "users.c"
#include "labworker.c"
#include "analysis.c"

void displayMenuforDoctor()
{
    printf("1.Request Blood Analysis\n");
    printf("2. Request Urine Analysis \n");
    printf("3. Create Patient\n");
    printf("4. Add Patient \n");
    printf("5. Print Analysis\n");
    printf("6. See Your Info \n");
    printf("7. See Patient Info\n");
    printf("8. See your all patients\n");
    printf("9. Change your Information\n"); // setname,surname vs.
    printf("10. Change Account\n");
    printf("0. Exit\n");
}

void displayMenuforAdmin()
{
    printf("1.Create Doctor\n");
    printf("2. Create Lab Worker \n");
    printf("3. Add Device\n");
    printf("4. Remove Doctor \n");
    printf("5. Remove Lab Worker\n");
    printf("6. Remove Device \n");
    printf("7. Add New Doctor\n"); // addDoctorToArray
    printf("8. Set Admin \n");     // setadminlabworker
    printf("9. Remove Patient\n"); // from the list
    printf("10. Write Devices to File\n");
    printf("11. Change your Information\n"); // setname,surname vs.
    printf("12. Change Account\n");
    printf("0. Exit\n");
}

void displayMenuforLabWorker()
{
    printf("1.Create Device\n");
    printf("2. Update Device Status  \n");
    printf("3. Update Device Status on the document\n");
    printf("4.  Write devices on the document\n");
    printf("5. Set Analysis Status\n");
    printf("6. Add Analysis To Patient \n");
    printf("7. Add New Device\n");          // addDoctorToArray
    printf("8. Change your Information\n"); // setname,surname vs.
    printf("9. Change Account\n");
    printf("0. Exit\n");
}

void displayMenuforPatient()
{
    printf("1. See Analysis\n");
    printf("2. See your information\n");
    printf("3. Choose Doctor\n");
    printf("4. Change your Information\n"); // set name, surname, etc.
    printf("5. Change Account\n");
    printf("0. Exit\n");
}

void displayChangeInfo()
{
    printf("1 Set Name\n");
    printf("2. Set Surname  \n");
    printf("3. Set Password");
    printf("4. Set phone\n");
    printf("0. Exit\n");
}

int main()
{

    createPatient("jane_smith", 5, "pass987", "Jane", "Smith", "555-5678");

    createPatient("p1", 12, "p", "Asude", "Sozcu", "551-5678");

    createLabWorker("lw", 3, "p", "Alice", "Johnson", "555-9876");
    createLabWorker("lab_worker1", 123, "lab_worker_password", "Lab", "Worker", "555-1111");

    // Create two doctors
    createDoctor("Dr.", 1, "John", "Doe", "p", "d", "555-1234");
    createDoctor("Dr.", 2, "Jane", "Smith", "pass4 56", "dr_smith", "555-5678");

    Analysis *newAnalysis = (Analysis *)malloc(sizeof(Analysis));
    struct ExaminationList *newList = (struct ExaminationList *)malloc(sizeof(struct ExaminationList));
    newList->examinations = &bloodExaminations[3];
    newList->count = 1;
    newAnalysis->id = 121;
    newAnalysis->resultvalue = 0.5;
    newAnalysis->type = BLOOD;
    newAnalysis->result = NORMAL;
    newAnalysis->status = INPROGRESS;
    newAnalysis->examinationlist = newList;

    for (size_t i = 0; i < patientCount; i++)
    {
        if (patients[i].userInfo.id == 12)
            newAnalysis->patient = &patients[i];
    }
    for (size_t i = 0; i < doctorsCount; i++)
    {
        if (doctors[i].userInfo.id == 1)
            newAnalysis->doctor = &doctors[i];
    }

    addAnalysisToList(newAnalysis);
    createDevice(1, "dev1", inUse);
    createDevice(2, "dev2", inUse);
    createDevice(3, "dev3", broken);
changeAccount:
    char inputtedUserName[25];
    char inputtedPassword[25];

    printf("To Start Automation Please Enter username: ");
    scanf("%s", inputtedUserName);

    printf("Enter password: ");
    scanf("%s", inputtedPassword);

    struct User *authenticatedUser = verifyUser(inputtedUserName, inputtedPassword);
    if (authenticatedUser != NULL)
    {
    //    printf("Welcome,  %s %d\n", authenticatedUser->username, numberforaccounttype);
   

        if (authenticatedUser->type == LABMAN)
        {
            for (int i = 0; i < labWorkerCount; ++i)
            {

                if (strcmp(inputtedUserName, labWorkers[i].userInfo.username) == 0 &&
                    strcmp(inputtedPassword, labWorkers[i].userInfo.password) == 0)
                {
                    struct LabWorker *authenticatedLabWorker = &labWorkers[i];
                }
            }
            int isAdminAsLabWorker;
            printf("Do you want to continue as admin? (0 for No, 1 for Yes): ");
            scanf("%d", &isAdminAsLabWorker);
            if(isAdminAsLabWorker==1){
                goto jump;
            }
            while (1)
            {
                displayMenuforLabWorker();
                int choice;
                printf("Enter your choice: ");
                scanf("%d", &choice);
                int deviceid;
                char devicename[20];
                int tempStatus;

                switch (choice)
                {
                case 1:

                    printf("Enter Device ID: ");
                    scanf("%d", &deviceid);
                    printf("Enter Device Name: ");
                    scanf("%s", devicename);

                    printf("Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ");
                    scanf("%d", &tempStatus);
                    DeviceStatus inputStatus;

                    // Aldığınız değeri enum'a dönüştürün
                    switch (tempStatus)
                    {
                    case 0:
                        inputStatus = inUse;
                        break;
                    case 1:
                        inputStatus = broken;
                        break;
                    case 2:
                        inputStatus = usable;
                        break;
                    default:

                        printf("Please enter a invalid value.");
                        break;
                    }
                    createDevice(deviceid, devicename, inputStatus);
                    printf("Create Device Succesful");
                    break;

                case 2:
                    int deviceidforcase2;
                    printf("Enter Device ID: ");
                    scanf("%d", &deviceidforcase2);

                    int tempStatusfor2;
                    printf("Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ");
                    scanf("%d", &tempStatusfor2);
                    DeviceStatus inputStatusfor2;

                    switch (tempStatusfor2)
                    {
                    case 0:
                        inputStatusfor2 = inUse;
                        break;
                    case 1:
                        inputStatusfor2 = broken;
                        break;
                    case 2:
                        inputStatusfor2 = usable;
                        break;
                    default:
                        printf("Please write valid value");
                        break;
                    }

                    setDeviceStatus(deviceidforcase2, inputStatusfor2);
                    printf("set Device Status Succesful");
                    break;
                case 3:
                    int deviceidforcase3;
                    printf("Enter Device ID: ");
                    scanf("%d", &deviceidforcase3);

                    int tempStatusfor3;
                    printf("Enter Device Status (0 for InUse, 1 for Broken, 2 for Usable): ");
                    scanf("%d", &tempStatusfor3);
                    DeviceStatus inputStatusfor3;

                    switch (tempStatusfor3)
                    {
                    case 0:
                        inputStatusfor3 = inUse;
                        break;
                    case 1:
                        inputStatusfor3 = broken;
                        break;
                    case 2:
                        inputStatusfor3 = usable;
                        break;
                    default:
                        printf("Please write valid value");
                        break;
                    }
                    updateDeviceStatus(authenticatedUser->id, deviceidforcase3, inputStatusfor3);
                    printf("Update Device Status Succesful");
                    break;
                case 4:
                    writeDevicesToFile(devices);
                    printf("write Devices To File Succesful");
                    break;
                case 5:
                    int analysisidforcase5;
                    printf("Enter Analysis ID: ");
                    scanf("%d", &analysisidforcase5);
                    setAnalysisStatus(analysisidforcase5);
                    printf("set Analysis Status Succesful");
                    break;
                case 6:
                    int analysisidforcase6;
                    printf("Enter Analysis ID: ");
                    scanf("%d", &analysisidforcase6);

                    int patientidforcase6;
                    printf("Enter Patient ID: ");
                    scanf("%d", &patientidforcase6);

                    // Find the analysis with the provided ID
                    for (size_t i = 0; i < numAnalyses; i++)
                    {
                        if (allAnalysis[i].id == analysisidforcase6)
                        {
                            // Find the patient with the provided ID
                            for (size_t j = 0; j < patientCount; j++)
                            {
                                if (patients[j].userInfo.id == patientidforcase6)
                                {
                                    // Add the analysis to the patient
                                    addAnalysisToPatient(&patients[j], &allAnalysis[i]);
                                    printf("add Analysis To Patient Succesful");
                                    return -1; // Exit function after adding analysis to patient
                                }
                            }

                            // Patient with the provided ID not found
                            printf("Error: Patient with ID %d not found.\n", patientidforcase6);
                            return -1;
                        }
                    }

                    break;
                case 7:
                    int deviceidforcase7;
                    printf("Enter Device ID: ");
                    scanf("%d", &deviceidforcase7);
                    for (size_t i = 0; i < Devicessize; i++)
                    {
                        if (devices[i].id == deviceidforcase7)
                        {
                            addDevice(&devices[i]);
                            printf("add device Succesful");
                        }
                    }

                    break;
                case 8:
                    int labWorkerPropertyChoice;
                    displayChangeInfo();
                    scanf("%d", &labWorkerPropertyChoice);

                    switch (labWorkerPropertyChoice)
                    {
                    case 1:
                        // Set Lab Worker Name
                        printf("Enter new name: ");
                        char newName[50];
                        scanf("%s", newName);
                        setLabWorkerName(authenticatedUser, newName);
                        printf("Lab Worker's name updated successfully.\n");
                        break;
                    case 2:
                        // Set Lab Worker Surname
                        printf("Enter new surname: ");
                        char newSurname[50];
                        scanf("%s", newSurname);
                        setLabWorkerSurname(authenticatedUser, newSurname);
                        printf("Lab Worker's name updated successfully.\n");

                        break;
                    case 3:
                        // Set Lab Worker Username
                        printf("Enter new username: ");
                        char newUsername[50];
                        scanf("%s", newUsername);
                        setLabWorkerUsername(authenticatedUser, newUsername);
                        printf("Lab Worker's username updated successfully.\n");

                        break;
                    case 4:
                        // Set Lab Worker Password
                        printf("Enter new password: ");
                        char newPassword[50];
                        scanf("%s", newPassword);
                        setLabWorkerPassword(authenticatedUser, newPassword);
                        printf("Lab Worker's password updated successfully.\n");

                        break;

                    default:
                        printf("Invalid choice for Lab Worker property.\n");
                        break;
                    }

                    break;
                case 9:
                    printf("Changing account...\n");
                    goto changeAccount;
                    break;
                case 0:
                    printf("Exiting the program.\n");
                    return -1; // Exit the function
                    break;

                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
                }
            }
        }

        else if (authenticatedUser->type == PATIENT)
        {
            struct Patient *authenticatedPatient;
            for (int i = 0; i < patientCount; ++i)
            {

                if (strcmp(inputtedUserName, patients[i].userInfo.username) == 0 &&
                    strcmp(inputtedPassword, patients[i].userInfo.password) == 0)
                {
                    authenticatedPatient = &patients[i];
                }
            }

            // Patient *authenticatedPatient = (Patient *)malloc(sizeof(Patient));
            // authenticatedPatient = (verifyPatient(inputtedUserName, inputtedPassword));

            while (1)
            {
                displayMenuforPatient();
                int choice;
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    int analysisID;
                    int analysisIDforcase2_2;

                case 1:

                    printf("Enter your analysis id: ");
                    // scanf("%d", &analysisID);

                    for (size_t i = 0; i < numAnalyses; i++)
                    {
                        printf("before1");

                        if (allAnalysis[i].id == 121)
                        {
                            printf("before");
                            printAnalyses(&allAnalysis[i]);
                        }
                    }

                    break;

                case 2:
                    getPatientInfo(authenticatedUser->id);
                    break;
                case 3:
                    char nameforcase4[25];
                    char surnameforcase4[25];
                    printf("Write doctor name and surname");
                    scanf("%s %s", nameforcase4, surnameforcase4);
                    for (size_t i = 0; i < doctorsCount; i++)
                    {
                        if (strcmp(doctors[i].userInfo.name, nameforcase4) && strcmp(doctors[i].userInfo.surname, surnameforcase4))
                        {
                            setPatientDoctor(authenticatedPatient, &doctors[i]);
                        }
                    }

                    break;
                case 4:
                    int PatientPropertyChoice;
                    displayChangeInfo();
                    scanf("%d", &PatientPropertyChoice);

                    switch (PatientPropertyChoice)
                    {
                    case 1:
                        printf("Enter new name: ");
                        char newNameforpatient[50];
                        scanf("%s", newNameforpatient);
                        setLabWorkerName(authenticatedUser, newNameforpatient);
                        printf("Your name updated successfully.\n");
                        break;
                    case 2:
                        printf("Enter new surname: ");
                        char newSurnameforpatient[50];
                        scanf("%s", newSurnameforpatient);
                        setLabWorkerSurname(authenticatedUser, newSurnameforpatient);
                        printf("Your surname updated successfully.\n");

                        break;
                    case 3:
                        printf("Enter new username: ");
                        char newUsernameforpatient[50];
                        scanf("%s", newUsernameforpatient);
                        setLabWorkerUsername(authenticatedUser, newUsernameforpatient);
                        printf("Your username updated successfully.\n");

                        break;
                    case 4:
                        printf("Enter new password: ");
                        char newPasswordforpatient[50];
                        scanf("%s", newPasswordforpatient);
                        setLabWorkerPassword(authenticatedUser, newPasswordforpatient);
                        printf("Your password updated successfully.\n");

                        break;
                    case 5:
                        printf("Changing account...\n");
                        goto changeAccount;
                        break;
                    case 0:
                        printf("Exiting the program.\n");
                        return -1; // Exit the function
                        break;
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                        break;
                    }
                }
            }
        }
        else if (authenticatedUser->type == DOCTOR)
        {
            struct Doctor *authenticatedDoctor;
            for (int i = 0; i < doctorsCount; ++i)
            {

                if (strcmp(inputtedUserName, doctors[i].userInfo.username) == 0 &&
                    strcmp(inputtedPassword, doctors[i].userInfo.password) == 0)
                {

                    authenticatedDoctor = &doctors[i];
                    break;
                }
            }
            while (1)
            {
                displayMenuforDoctor();
                int DoctorPropertyChoice;
                char newNamefordoctor[50];
                int idforcase7;
                char newSuramefordoctor[50];
                char newUseramefordoctor[50];

                char newPasswordfordoctor[50];
                int idforcase4;
                char usernameforcase3[50];
                int idforcase3;
                char passwordforcase3[50];
                char nameforcase3[50];
                char surnameforcase3[50];
                char phoneforcase3[15];
                int patientidcase2;
                int patientidcase1;

                int choicefordoctor;
                int idforcase5;

                printf("Enter your choice: ");
                scanf("%d", &choicefordoctor);

                switch (choicefordoctor)
                {
                case 1:
                    printf("Enter patient ID: ");
                    scanf("%d", &patientidcase1);
                    requestBloodAnalysis(authenticatedUser->id, patientidcase1);

                    break;
                case 2:
                    printf("Enter patient ID: ");
                    scanf("%d", &patientidcase2);
                    requestUrineAnalysis(authenticatedDoctor, patientidcase2);
                    break;
                case 3:

                    printf("Enter username: ");
                    scanf("%s", usernameforcase3);

                    printf("Enter ID: ");
                    scanf("%d", &idforcase3);

                    printf("Enter password: ");
                    scanf("%s", passwordforcase3);

                    printf("Enter name: ");
                    scanf("%s", nameforcase3);

                    printf("Enter surname: ");
                    scanf("%s", surnameforcase3);

                    printf("Enter phone: ");
                    scanf("%s", phoneforcase3);
                    createPatient(usernameforcase3, idforcase3, passwordforcase3, nameforcase3, surnameforcase3, phoneforcase3);
                    break;
                case 4:
                    printf("Enter patient ID: ");
                    scanf("%d", &idforcase4);
                    for (size_t i = 0; i < patientCount; i++)
                    {
                        if (patients[i].userInfo.id == idforcase4)
                        {


                            addPatient(authenticatedDoctor, &patients[i]);
                        }
                    }
                    break;
                case 5:
                    printf("Enter Analysis ID: ");
                    scanf("%d", &idforcase5);
                    for (size_t i = 0; i < numAnalyses; i++)
                    {
                        if (allAnalysis[i].id == idforcase5)
                        {
                            printAnalyses(&allAnalysis[i]);
                            break;
                        }
                    }

                    break;
                case 6:
                    DoctorInfo(authenticatedDoctor);
                    break;
                case 7:

                    printf("Enter Patient ID: ");
                    scanf("%d", &idforcase7);
                    for (size_t i = 0; i < patientCount; i++)
                    {
                        if (patients[i].userInfo.id == idforcase7)
                        {
                            getPatientInfo(patients[i].userInfo.id);
                        }
                    }
                    break;
                case 8:
                    printDoctorPatients(authenticatedDoctor);
                    break;

                case 9:
                    displayChangeInfo();
                    scanf("%d", &DoctorPropertyChoice);

                    switch (DoctorPropertyChoice)
                    {
                    case 1:
                        // Set Lab Worker Name
                        printf("Enter new name: ");
                        scanf("%s", newNamefordoctor);
                        setLabWorkerName(authenticatedUser, newNamefordoctor);
                        printf("Your name updated successfully.\n");
                        break;
                    case 2:
                        // Set Lab Worker Surname
                        printf("Enter new surname: ");
                        scanf("%s", newSuramefordoctor);
                        setLabWorkerSurname(authenticatedUser, newSuramefordoctor);
                        printf("Your surname updated successfully.\n");
                        break;
                    case 3:
                        // Set Lab Worker Username
                        printf("Enter new username: ");
                        scanf("%s", newUseramefordoctor);
                        setLabWorkerUsername(authenticatedUser, newUseramefordoctor);
                        printf("Your username updated successfully.\n");
                        break;
                    case 4:
                        // Set Lab Worker Password
                        printf("Enter new password: ");
                        scanf("%s", newPasswordfordoctor);
                        setLabWorkerPassword(authenticatedUser, newPasswordfordoctor);
                        printf("Your password updated successfully.\n");
                        break; // Remove the extra break statement here
                    default:
                        printf("Invalid choice for Doctor property.\n");
                        break;
                    }

                    break; // Add this line to break from the DOCTOR case 10 loop
                case 10:
                    printf("Changing account...\n");
                    goto changeAccount;
                    break;
                case 0:
                    printf("Exiting the program.\n");
                    return 0; // Exit the program
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
                }
            }
        }
 jump:
        if (authenticatedUser->isAdmin)
        {

            while (1)
            {

                
                    displayMenuforAdmin();
                    int choiceforadmin;
                    printf("Enter your choice: ");
                    scanf("%d", &choiceforadmin);

                    switch (choiceforadmin)
                    {
                        char titleforcase1[50];
                        int idforcase1;
                        char nameforcase1[50];
                        char surnameforcase1[50];
                        char passwordforcase1[50];
                        char usernameforcase1[50];
                        char phoneforcase1[20];
                        char usernameforcase2[50];
                        int idforcase2;
                        char passwordforcase2[50];
                        char nameforcase2[50];
                        char surnameforcase2[50];
                        char phoneforcase2[20];
                        int deviceidtoadd;
                        int doctorIdcase4;
                        int labworkerIdcase5;
                        int deviceIdcase6;
                        int DoctorIdcase7;
                        int LabworkerIdcase8;
                        int PatientIdcase9;
                        int AdminPropertyChoice;

                    case 1:

                        // Kullanıcıdan veri al
                        printf("Title: ");
                        scanf("%s", titleforcase1);

                        printf("ID: ");
                        scanf("%d", &idforcase1);

                        printf("Name: ");
                        scanf("%s", nameforcase1);

                        printf("Surname: ");
                        scanf("%s", surnameforcase1);

                        printf("Password: ");
                        scanf("%s", passwordforcase1);

                        printf("Username: ");
                        scanf("%s", usernameforcase1);

                        printf("Phone: ");
                        scanf("%s", phoneforcase1);

                        createDoctor(titleforcase1, idforcase1, nameforcase1, surnameforcase1, passwordforcase1, usernameforcase1, phoneforcase1);
                        break;
                    case 2:

                        // Kullanıcıdan veri al
                        printf("Username: ");
                        scanf("%s", usernameforcase2);

                        printf("ID: ");
                        scanf("%ld", &idforcase2);

                        printf("Password: ");
                        scanf("%s", passwordforcase2);

                        printf("Name: ");
                        scanf("%s", nameforcase2);

                        printf("Surname: ");
                        scanf("%s", surnameforcase2);

                        printf("Phone: ");
                        scanf("%s", phoneforcase2);

                        createLabWorker(usernameforcase2, idforcase2, passwordforcase2, nameforcase2, surnameforcase2, phoneforcase2);
                        break;
                    case 3:
                        printf("Device Id: ");
                        scanf("%d", &deviceidtoadd);
                        for (size_t i = 0; i < Devicessize; i++)
                        {
                            if (devices[i].id == deviceidtoadd)
                            {
                                addDevice(&devices[i]);
                            }
                        }
                        break;
                    case 4:
                        printf("Doctor Id: ");
                        scanf("%d", &doctorIdcase4);

                        deleteDoctor(doctorIdcase4, authenticatedUser->id);
                        break;
                    case 5:
                        printf("Lab Worker Id: ");
                        scanf("%d", &labworkerIdcase5);
                        removeLabWorker(labworkerIdcase5, authenticatedUser->id);
                        break;
                    case 6:

                        printf("Device Id: ");
                        scanf("%d", &deviceIdcase6);
                        removeDeviceByAdmin(deviceIdcase6, authenticatedUser->id);
                        break;
                    case 7:
                        printf("Doctor Id: ");
                        scanf("%d", &DoctorIdcase7);
                        for (size_t i = 0; i < doctorsCount; i++)
                        {
                            if (doctors[i].userInfo.id == DoctorIdcase7)
                            {
                                addDoctortoDoctorsArray(&doctors[i]);
                            }
                        }
                        break;
                    case 8:
                        printf("Lab Worker Id: ");
                        scanf("%d", &LabworkerIdcase8);
                        for (size_t i = 0; i < labWorkerCount; i++)
                        {
                            if (labWorkers[i].userInfo.id == LabworkerIdcase8)
                            {
                                setLabWorkerAdminStatus(&labWorkers[i], authenticatedUser->id);
                            }
                        }
                        break;
                    case 9:
                        printf("Patients Id: ");
                        scanf("%d", &PatientIdcase9);
                        for (size_t i = 0; i < patientCount; i++)
                        {
                            if (patients[i].userInfo.id == PatientIdcase9)
                            {
                                removePatientFromList(&patients[i]);
                            }
                        }
                        break;
                    case 10:

                        writeDevicesToFile(devices);

                        break;
                    case 11:
                        displayChangeInfo();
                        scanf("%d", &AdminPropertyChoice);

                        switch (AdminPropertyChoice)
                        {
                        case 1:
                            // Set Lab Worker Name
                            printf("Enter new name: ");
                            char newNameforadmin[50];
                            scanf("%s", newNameforadmin);
                            setLabWorkerName(authenticatedUser, newNameforadmin);
                            printf("Your name updated successfully.\n");
                            break;
                        case 2:
                            // Set Lab Worker Surname
                            printf("Enter new surname: ");
                            char newSurnameforadmin[50];
                            scanf("%s", newSurnameforadmin);
                            setLabWorkerSurname(authenticatedUser, newSurnameforadmin);
                            printf("Your surname updated successfully.\n");

                            break;
                        case 3:
                            // Set Lab Worker Username
                            printf("Enter new username: ");
                            char newUsernameforadmin[50];
                            scanf("%s", newUsernameforadmin);
                            setLabWorkerUsername(authenticatedUser, newUsernameforadmin);
                            printf("Your username updated successfully.\n");

                            break;
                        case 4:
                            // Set Lab Worker Password
                            printf("Enter new password: ");
                            char newPasswordforadmin[50];
                            scanf("%s", newPasswordforadmin);
                            setLabWorkerPassword(authenticatedUser, newPasswordforadmin);
                            printf("Your password updated successfully.\n");
                            break;
                        }
                        break;
                    case 12:
                        printf("Changing account...\n");
                        goto changeAccount;
                        break;
                    case 0:
                        printf("Exiting the program.\n");
                        return 0;
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                    }
                
                
            }
        }printf("Not allowed to use as admin");
    }
    else
    {
        printf("Invalid inputs. Please check your information.\n");
    }
    return 0;
}
