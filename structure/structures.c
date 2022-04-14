typedef struct {
    /*
    0 : log in
    1 : log out
    2 : create account
    3 : delete account
    */
    int action;
    char data[100]
} request;

#define PORT 2058

typedef struct {
    /*
    1 : log in
    2 : log out
    3 : display all users
    4 : create account
    5 : delete account
    6 : leave
    */
    int type;
    char username[100];
    char message[100];
} actions;

