#include<stdbool.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Transaction {
    char transferId[10];
    char receivingId[10];
    double amount;
    char type[10];
    char message[50];
    struct Date transactionDate;
};

struct AccountInfo {
    char userId[20];
    float balance;
    bool status; // true = open, false = locked
    struct Transaction transactionHistory[100];
    int transactionCount;
};

struct User {
    char userId[11];
    char name[20];
    struct Date dateOfBirth;
    bool gender; // 0 = female, 1 = male
    char phone[11];
    char userPhone[11];
    char email[30];
    struct AccountInfo account;
};
