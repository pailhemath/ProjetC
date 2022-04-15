struct request
{
    /*
    0 : log in
    1 : log out
    2 : create account
    3 : delete account
    */
    int action;
    char data[100]; //Data sent with request
};