

#include <stdbool.h>
#ifndef USERS_H
#define USERS_H

typedef enum AccountType
{
    PATIENT,
    DOCTOR,
    LABMAN

} AccountType;

typedef  struct User
{
    char *name;
    char *surname;
    char *username;
    char *password;
    char *phone;
    int id;
    bool isAdmin;
    AccountType type;
}User;
extern struct User users[100];
extern int numberOfUsers;
extern int capacity;

const char* accountTypeToString(AccountType type);
struct Patient *verifyPatient(const char *inputUsername, const char *inputPassword);






#endif