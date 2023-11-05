struct Status
{
    string roleName;
    string password;
    int position;
    bool access;
};

Status UserAuth(string directory)
{
    Status status;
    const string ROLES[3] = {"MANAGER", "COORDINATOR", "TECHNITIAN"};
    //
    const int CHOICE = getChoice(optionsOfRole, 3);
    system("cls");
    subject();
    const string ROLE = ROLES[CHOICE - 1];
    string password;
    int hasAttempsCounter = 1;
    const int ATTEMPTS_MAX = 4;
    while (hasAttempsCounter < ATTEMPTS_MAX)
    {
        cout << "\n Y O U   H A V E (" << (ATTEMPTS_MAX - hasAttempsCounter) << ") A T T E M P T (S)\n";
        password = userInput("\n ENTER PASSWORD FOR THE HUB (" + ROLE + ") :  ", true);
        const string KEY_ROLE = formKeyValue("ROLE", ROLE);
        const string KEY_PASSWORD = formKeyValue("PASSWORD", password);
        const vector<string> USERS = manageFile("read", directory);
        for (string eachUser : USERS)
        {
            if (eachUser.find(KEY_ROLE) != -1 && eachUser.find(KEY_PASSWORD) != -1)
            {
                status.roleName = ROLE;
                status.password = password;
                status.position = CHOICE;
                status.access = true;
                return status;
            }
        }
        hasAttempsCounter += 1;
        cout << "\n\n I N C O R R E C T   P A S S W O R D\n";
    }
    status.roleName = "";
    status.password = "";
    status.position = 0;
    status.access = false;
    return status;
}
