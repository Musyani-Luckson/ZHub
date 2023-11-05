// #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
// Text based interface
#include <conio.h>
// Typos for numeric
#include <limits>
// For time
#include <chrono>
//
using namespace std;
// Function to validate an integer if it is within the requird range.
bool isValidInt(int integer, int min, int max)
{
    if (integer >= min && integer <= max)
        return true;
    else
        return false;
}
// Function to get a valid requird user choice from the options provided.
int getChoice(void (*function)(), int max)
{
    // Choice set to zer0 so that the while loop, gets executed.
    int choice = 0;
    // Makes sure the choice is not outside the required range.
    while (!isValidInt(choice, 1, max))
    {
        function();
        // Calls the function do display the valid options to make a choice from.
        cout << "\n ENTER YOUR CHOICE:   ";
        cin >> choice;
        // When the input is not an int data type it clears the error.
        cin.clear();
        // Then displays the options again.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}
// Function to get a valid requird user choice from the options provided.
int getCategoryChoice(
    void (*function)(vector<string>), int max, const vector<string> useThis = vector<string>())
{
    // Choice set to zer0 so that the while loop, gets executed.
    int choice = 0;
    // Makes sure the choice is not outside the required range.
    while (!isValidInt(choice, 1, max))
    {
        function(useThis);
        // Calls the function do display the valid options to make a choice from.
        cout << "\n ENTER YOUR CHOICE:   ";
        cin >> choice;
        // When the input is not an int data type it clears the error.
        cin.clear();
        // Then displays the options again.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}
// Function to change a string to UPPER Or lower CASE.
string upperCase(string charecter, bool convert = true)
{
    if (convert)
        for (char &converted : charecter)
            converted = std::toupper(converted);
    else
        for (char &converted : charecter)
            converted = tolower(converted);
    return charecter;
}
// Function for getting value from the user input form.
string userInput(string label, bool isPassword = false)
{
    // A: If not entering the password.
    cout << label;
    if (!isPassword)
    {
        string value = "";
        getline(cin, value);
        return upperCase(value);
    }
    // B: When entering the password.
    else
    {
        // Define an array to store the password with the max of 24.
        char password[24];
        char ch;
        int i = 0;
        while (1)
        {
            // Read a character without displaying it.
            ch = _getch();
            // Checks for if the key (ENTER) has been pressed.
            if (ch == 13)
                break;
            else if (ch == 8)
            { // Checks for backspace in order to erase the current previous typed charecter.
                if (i > 0)
                {
                    i--;
                    // Move the cursor back and erase the character.
                    cout << "\b \b";
                }
            }
            else
            {
                password[i] = ch;
                i++;
                // Replaces the current typed charecter on the user interface(front end) with "*".
                cout << '*';
            }
        }
        // Null-terminate the password string.
        password[i] = '\0';
        return password;
    }
}
// Function to merge two strings and form a ("key":"value") pair string.
string formKeyValue(string key, string value)
{
    const string FORMED = "\"" + upperCase(key) + "\":\"" + value + "\"";
    return FORMED;
}
// Function for managing file operations (read/get, write/add, find/search/contains, empty/clear)
vector<string> manageFile(string method, string fileName, string content = "")
{
    string action = upperCase(method);
    vector<string> values;
    // For adding the content to be contained inside the .txt file
    if (!action.compare("ADD") || !action.compare("WRITE"))
    {
        fstream FILE;
        FILE.open(fileName, ios::app);
        if (FILE.is_open())
        {
            FILE << content << endl;
            FILE.close();
        }
        return values;
    }
    else if (!action.compare("GET") || !action.compare("READ"))
    {
        // For getting the contained items in a .txt file
        fstream FILE;
        FILE.open(fileName, ios::in);
        if (FILE.is_open())
        {
            string eachLine;
            while (getline(FILE, eachLine))
            {
                values.push_back(eachLine);
            }
            FILE.close();
        }
        return values;
    }
    else if (action == "FIND" || action == "SEARCH" || action == "CONTAINS")
    {
        // Used for finding a specific text inside a .txt file
        vector<string> items = manageFile("get", fileName);
        for (string item : items)
        {
            if (item.find(content) != -1)
            {
                values.push_back(item);
            }
        }
        return values;
    }
    else if (action == "EMPTY" || action == "CLEAR")
    {
        // When needs to wipe the whole .txt file to none content contained
        fstream FILE;
        FILE.open(fileName, ios::out | ios::trunc);
        if (FILE.is_open())
        {
            FILE.close();
        }
        return values;
    }
    else
    {
        // Returns an empty array
        return values;
    }
}
// Function to form a string current date and return it as a string.
string currentDate()
{
    // get the current time
    auto now = chrono::system_clock::now();
    // converts the current time in seconds from 1900 to whem called.
    time_t time = chrono::system_clock::to_time_t(now);
    tm *timeInfo = localtime(&time);
    int curentYear = (timeInfo->tm_year + 1900);
    int curentMonth = (timeInfo->tm_mon + 1);
    int curentDate = (timeInfo->tm_mday);
    return to_string(curentDate) + "/" + to_string(curentMonth) + "/" + to_string(curentYear);
}
