// #include <iostream>
// #include <string>
#include <stdlib.h>
// using namespace std;
//
// Struct Declarations.
struct Security
{
    string roleName;
    string password;
};
struct Data
{
    vector<string> innovators;
    int position;
    Security security;
};
// Function declarations.
void ZHub();
void Menu(Data &rawData);
void AddInnovator(Data &rawData);
void SearchInnovator(Data &rawData);
void EditInnovator(Data &rawData);
void DeleteInnovator(Data &rawData);
void DisplayInnovatorsByInnovationCategory(Data &rawData);
void ExitUser(vector<string> innovators);
void SaveRocords(vector<string> innovators, string directory);
void SearchAgin(Data &rawData);
string innovatorEdition(string oldDetails, string newValue, int choice);
//
// Function to extract (key:value) pairs from a specific structured string using regular expressions.
vector<pair<string, string>> keyValueInnovator(const string input)
{
    vector<pair<string, string>> keyValuePairs;
    // pattern or a way in which to use when extracting required data from a specified structured string.
    regex pattern("\"(\\w+)\":\\s*\"([^\"]*)\"");
    smatch matches;
    auto it = input.cbegin();
    while (regex_search(it, input.cend(), matches, pattern))
    {
        if (matches.size() == 3)
        {
            keyValuePairs.emplace_back(matches[1].str(), matches[2].str());
            it = matches.suffix().first;
        }
    }
    return keyValuePairs;
}
// Function to return an array of categories from innovations.
vector<string> availableCategories(vector<string> innovators)
{
    vector<string> nameOfCategories;
    for (string innovator : innovators)
    {
        const vector<pair<string, string>> KEY_VALUE_OF_INNOVATOR = keyValueInnovator(innovator);
        for (int i = 0; i < KEY_VALUE_OF_INNOVATOR.size(); i++)
        {
            if (!KEY_VALUE_OF_INNOVATOR[i].first.compare("INNOVATION_CATEGORY"))
            {
                // Anything below here is to make sure no same string is pushed/added into the nameOfCategories array.
                auto isContained = find(nameOfCategories.begin(), nameOfCategories.end(), KEY_VALUE_OF_INNOVATOR[i].second);
                if (isContained == nameOfCategories.end())
                    nameOfCategories.push_back(KEY_VALUE_OF_INNOVATOR[i].second);
            }
        }
    }
    return nameOfCategories;
}
// Independent function to display avalible categories options.
void categoriesOptions(vector<string> innovators)
{
    const vector<string> ARRAY_OF_CATEGORIES = availableCategories(innovators);
    cout << "\n D I S P L A Y   I N N O V A T O R  S   B Y   C A T E G O R Y \n";
    for (int i = 0; i < ARRAY_OF_CATEGORIES.size(); i++)
    {
        cout << "\n " + to_string(i + 1) + " - " + ARRAY_OF_CATEGORIES[i];
    }
    cout << "\n " + to_string(ARRAY_OF_CATEGORIES.size() + 1) + " - MAIN MENU";
}
// Function that loads innovators into the ZHub system from the required .txt file.
vector<string> ReloadRecords(string directory)
{
    vector<string> innovators = manageFile("read", directory);
    return innovators;
}
//
// Executioners: These are helper functions to execute the request of PERMISSIONAL Functions.
// Function to return name of innovation category.
string innovationCategoryChoice()
{
    const string CATEGORIES[5] = {"FoodTech", "WoodTech", "MetalTech", "IT", "Other"};
    const int CATEGORY_CHOICE = getChoice(innovationCategoriesOptions, 5);
    return CATEGORIES[CATEGORY_CHOICE - 1];
}
// Function to return status of patent.
string PatentStatus()
{
    const string PATENTS[3] = {"PATENED", "IN PROGRESS", "NOT REQUIRED"};
    const int PATENT_CHOICE = getChoice(patentsOptions, 3);
    return PATENTS[PATENT_CHOICE - 1];
}
// Function to display already filled input forms.
void showFilledForms(vector<string> valuesOfFilledForms)
{
    // Array of Input Forms Names(Labels).
    const string LABELS[9] = {
        "\n INNOVATION TITLE: ",
        "\n NRC No: ",
        "\n PASSPORT No: ",
        "\n FIRSTNAME: ",
        "\n LASTNAME: ",
        "\n AGE: ",
        "\n PATENT STATUS: ",
        "\n DATE SUBMITTED: ",
        "\n INNOVATION CATEGORY: "};
    system("cls");
    subject();
    // Loops through (valuesOfFilledForms) and displays them.
    cout << " FILLED FORMS: \n";
    for (int i = 0; i < valuesOfFilledForms.size(); i++)
    {
        cout << LABELS[i] + valuesOfFilledForms[i];
    }
    cout << "\n\n";
}
// Function to merge strings of details from the user input forms to a string of key:value pair object.
string innovatorStringObject(string value, string innovationTitle, int OPTION)
{
    string NRC_OR_PASSPORT_VALUES[2];
    if (OPTION == 1)
    {
        NRC_OR_PASSPORT_VALUES[0] = value;
        NRC_OR_PASSPORT_VALUES[1] = "NULL";
    }
    else
    {
        NRC_OR_PASSPORT_VALUES[0] = "NULL";
        NRC_OR_PASSPORT_VALUES[1] = value;
    }
    //
    vector<string> filledForms;
    //
    const string NRC = upperCase(formKeyValue("NRC_No", NRC_OR_PASSPORT_VALUES[0]));
    const string PASSPORT = upperCase(formKeyValue("PASSPORT_No", NRC_OR_PASSPORT_VALUES[1]));
    const string INNOVATION_TITLE = formKeyValue("TITLE_OF_INNOVATION", innovationTitle);
    filledForms.push_back(innovationTitle);
    filledForms.push_back(NRC_OR_PASSPORT_VALUES[0]);
    filledForms.push_back(NRC_OR_PASSPORT_VALUES[1]);
    showFilledForms(filledForms);
    //
    const string FIRSTNAME_VALUE = userInput(" ENTER FIRSTNAME:   ");
    filledForms.push_back(FIRSTNAME_VALUE);
    showFilledForms(filledForms);
    //
    const string LASTNAME_VALUE = userInput(" ENTER LASTNAME:   ");
    filledForms.push_back(LASTNAME_VALUE);
    showFilledForms(filledForms);
    //
    const string AGE_VALUE = userInput(" ENTER AGE:   ");
    filledForms.push_back(AGE_VALUE);
    showFilledForms(filledForms);
    //
    const string PATENT_VALUE = PatentStatus();
    filledForms.push_back(PATENT_VALUE);
    showFilledForms(filledForms);
    //
    const string DATE_VALUE = currentDate();
    filledForms.push_back(DATE_VALUE);
    const string CATEGORY_VALUE = innovationCategoryChoice();
    filledForms.push_back(CATEGORY_VALUE);
    showFilledForms(filledForms);
    //
    const string FIRSTNAME = formKeyValue("FIRSTNAME", FIRSTNAME_VALUE);
    const string LASTNAME = formKeyValue("LASTNAME", LASTNAME_VALUE);
    const string AGE = formKeyValue("AGE", AGE_VALUE);
    const string DATE = formKeyValue("DATE_SUBMITTED", DATE_VALUE);
    const string PATENT = formKeyValue("PATENT_STATUS", PATENT_VALUE);
    const string CATEGORY = formKeyValue("INNOVATION_CATEGORY", CATEGORY_VALUE);
    cout << endl;
    // String of innovator to add to a .txt file.
    const string INNOVATOR = "{" + NRC + "," + PASSPORT + "," + FIRSTNAME + "," + LASTNAME + "," + AGE + "," + INNOVATION_TITLE + "," + DATE + "," + PATENT + "," + CATEGORY + "}";
    return INNOVATOR;
}
// Function to execute and modify what to modify based on an innovator request.
string innovatorEdition(string oldDetails, string newValue, int choice)
{
    string choices[8] = {
        "NRC_NO",
        "PASSPORT_NO",
        "FIRSTNAME",
        "LASTNAME",
        "AGE",
        "TITLE_OF_INNOVATION",
        "PATENT_STATUS",
        "INNOVATION_CATEGORY"};
    const string KEY = upperCase(choices[choice - 1]);
    vector<pair<string, string>> innovator = keyValueInnovator(oldDetails);
    // String to store edited innovator.
    string edited;
    for (int i = 0; i < innovator.size(); i++)
    {
        // When not false do this.
        if (!KEY.compare(innovator[i].first))
            // Reassigns the old value with the new value based on the requested demand using the choice given.
            innovator[i].second = newValue;
        const string key_value = formKeyValue(innovator[i].first, innovator[i].second);
        // Appends (key:value) pair to one another.
        if (i <= 0)
        {
            // Appends or Concatenates only the first key:value to a variable responsible holding editd innovator.
            edited += key_value;
        }
        else
        {
            // Appends or Concatenates every key:value after the first key:value to a variable responsible holding editd innovator.
            edited += "," + key_value;
        }
        // Appends (key:value) pair to one another.
    }
    // wraps up the whole modified innovator string inside a string of cury brackets.
    const string EDITED_DETAILS = "{" + edited + "}";
    return EDITED_DETAILS;
}
// Function to replace the oldInnovator with the EditedInnovator.
void PushEdited(string oldInnovator, string editedInnovator, vector<string> &innovators)
{
    vector<string> modifiedRecord;
    for (string eachInnovator : innovators)
    {
        if (eachInnovator.compare(oldInnovator))
            modifiedRecord.push_back(eachInnovator);
        else
            modifiedRecord.push_back(editedInnovator);
    }
    innovators = modifiedRecord;
}
// Function for searching and returning an array of innovator having a specefic (key) string.
vector<string> SearchByKey(string key, vector<string> innovators)
{
    vector<string> CONTAINING_KEY;
    for (string innovator : innovators)
    {
        if (innovator.find(key) != -1)
            CONTAINING_KEY.push_back(innovator);
    }
    return CONTAINING_KEY;
}
// Function that displays the searched available innovator.
void DisplayInnovator(string innovator)
{
    cout << "\n I N N O V A T O R \n";
    vector<pair<string, string>> pair = keyValueInnovator(innovator);
    for (int i = 0; i < pair.size(); i++)
    {
        cout << "\n " + pair[i].first + ": " + pair[i].second;
    }
    cout << "\n";
}
// Function to execute the removal of an innovator from the record of innovators.
void RemoveInnovator(string innovator, vector<string> &innovators)
{
    vector<string> restOfTheInnovators;
    for (string eachInnovator : innovators)
        if (eachInnovator.compare(innovator))
            restOfTheInnovators.push_back(eachInnovator);
    innovators = restOfTheInnovators;
}
//  Function for validating the innovator to be added by checking if aleady in the system with the provided NRC (OR) PASSPOR (AND) INNOVATION TITLE.
bool isAlreadyInPlace(string NRCorPASSPORT, string innovationTitle, vector<string> innovators)
{
    for (string innovator : innovators)
        if ((innovator.find(NRCorPASSPORT) != -1) && (innovator.find(innovationTitle) != -1))
            return true;
    return false;
}
// Function to execute the request of searching and returns  the results.
vector<string> searcher(int choice, vector<string> innovators)
{
    vector<string> searched;
    // Asks for NRC or PASSPORT No and TITLE of Innovation.
    const string LABELS[2] = {"NRC No:  ", "PASSPORT No:  "};
    const string INPUT_KEYS[2] = {"NRC_NO", "PASSPORT_NO"};
    const string NRC_OR_PASSPORT_VALUE = userInput("\n ENTER " + LABELS[choice - 1]);
    const string GET_TITLE = userInput(" ENTER INNOVATION TITLE:  ");
    // Then forms two keys to be used for searching through.
    const string NRC_OR_PASSPORT_KEY_VALUE = formKeyValue(INPUT_KEYS[choice - 1], NRC_OR_PASSPORT_VALUE);
    const string INNOVATION_TITLE = formKeyValue("TITLE_OF_INNOVATION", GET_TITLE);
    // And now searches through using those two keys.
    for (string eachInnovator : innovators)
    {
        if ((eachInnovator.find(NRC_OR_PASSPORT_KEY_VALUE) != -1) && (eachInnovator.find(INNOVATION_TITLE) != -1))
            searched.push_back(eachInnovator);
    }
    // Returns the results.
    return searched;
}
// Function to execute the final security confirmation process in order to allow the user complete their permission.
bool confirmActionWithPassword(Security values)
{
    cout << "\n P A S S W O R D   R E Q U I R E D   T O   C O M P L E T E   T H I S   P E R M I S S I O N \n";
    string password;
    int hasAttempsCounter = 1;
    const int ATTEMPTS_MAX = 3;
    while (hasAttempsCounter < ATTEMPTS_MAX)
    {
        cout << "\n Y O U   H A V E (" << (ATTEMPTS_MAX - hasAttempsCounter) << ") A T T E M P T (S)\n";
        password = userInput("\n P A S S W O R D   F O R   T H E   H U B  " + values.roleName + ": ", true);
        if (!values.password.compare(password))
            return true;
        hasAttempsCounter += 1;
        cout << "\n I N C O R R E C T   P A S S W O R D\n";
    }
    return false;
}
//
// Functions to allow the user to perform current permissions again without having to go to the main menu.
//
void SearchAgain(Data &rawData)
{
    if (getChoice(search_again_options, 2) == 1)
        SearchInnovator(rawData);
    else
        Menu(rawData);
}
//
void AddAgain(Data &rawData)
{
    if (getChoice(add_again_options, 2) == 1)
        AddInnovator(rawData);
    else
        Menu(rawData);
}
//
void EditAgin(Data &rawData)
{
    if (getChoice(edit_again_options, 2) == 1)
        EditInnovator(rawData);
    else
        Menu(rawData);
}
//
void DeleteAgain(Data &rawData)
{
    if (getChoice(delete_again_options, 2) == 1)
        DeleteInnovator(rawData);
    else
        Menu(rawData);
}
//
void DisplayAgain(Data &rawData)
{
    if (getChoice(display_again_options, 2) == 1)
        DisplayInnovatorsByInnovationCategory(rawData);
    else
        Menu(rawData);
}
//
//
// USER MENU PERMISSIONS HANDLERS
//
//
//

// Function to handle the permission of searching an innovator.
void SearchInnovator(Data &rawData)
{
    system("cls");
    subject();
    cout << "\n S E A R C H   F O R   I N N O V A T O R \n";
    const int OPTION = getChoice(NRC_OR_PASSPORT_options, 3);
    if (OPTION >= 1 && OPTION <= 2)
    {
        system("cls");
        subject();
        const vector<string> RESULTS = searcher(OPTION, rawData.innovators);
        system("cls");
        subject();
        if (RESULTS.size() >= 1)
        {
            DisplayInnovator(RESULTS[0]);
            SearchAgain(rawData);
        }
        else
        {
            system("cls");
            subject();
            cout << "\n N O   I N N O V A T O R   W A S   F O U N D \n";
            SearchAgain(rawData);
        }
    }
    else
        Menu(rawData);
}
// Function to handle the permission of adding an innovator.
void AddInnovator(Data &rawData)
{
    system("cls");
    subject();
    cout << "\n A D D I N G   I N N O V A T O R \n";
    const int CHOICE = getChoice(NRC_OR_PASSPORT_options, 3);
    if (CHOICE >= 1 && CHOICE <= 2)
    {
        system("cls");
        subject();
        // A: Anything here is to make sure the innovator to be added in is not alreading existing in the system with
        // the provided NRC (OR) PASSPORT (AND) INNOVATOPN TITLE
        const string INPUT_KEYS[2] = {"NRC_NO", "PASSPORT_NO"};
        const string LABELS[2] = {"NRC No:  ", "PASSPORT No:  "};
        const string NRC_OR_PASSPORT_VALUE = userInput("\n ENTER " + LABELS[CHOICE - 1]);
        const string NRC_OR_PASSPORT_KEY_VALUE = formKeyValue(INPUT_KEYS[CHOICE - 1], NRC_OR_PASSPORT_VALUE);
        //
        const string GET_TITLE = userInput(" ENTER INNOVATION TITLE:  ");
        const string INNOVATION_TITLE = formKeyValue("TITLE_OF_INNOVATION", GET_TITLE);
        //
        const bool RESULTS = isAlreadyInPlace(NRC_OR_PASSPORT_KEY_VALUE, INNOVATION_TITLE, rawData.innovators);
        // A: Ends here
        // B: Here it continue based on weither the RESULTS are true or false
        if (RESULTS)
        {
            system("cls");
            subject();
            // If aleady in place it notifies the user
            cout << "\n\n T H E  (" << INPUT_KEYS[CHOICE - 1] + ": " + NRC_OR_PASSPORT_VALUE << ")  I S   A L R E A D Y   H A V I N G   A N   I N N O V A T I O N   B Y   T H E   T I T L E:   " + GET_TITLE + "\n";
            AddAgain(rawData);
        }
        else
        {
            // Else continue asking for innovator credentials.
            const string INNOVATOR = innovatorStringObject(NRC_OR_PASSPORT_VALUE, GET_TITLE, CHOICE);
            // Comfirms if the user needs to perform such a permission.
            if (getChoice(comfirm_options, 2) == 1)
            {
                system("cls");
                subject();
                const bool confirmation = confirmActionWithPassword(rawData.security);
                if (confirmation)
                {
                    rawData.innovators.push_back(INNOVATOR);
                    system("cls");
                    subject();
                    cout
                        << "\n I N N O V A T O R   S U C C E S S F U L L Y   A D D E D\n";
                    AddAgain(rawData);
                }
                else
                {
                    system("cls");
                    subject();
                    cout << "\n I N N O V A T O R   N O T   A D D E D\n";
                    AddAgain(rawData);
                }
            }
            else
            {
                system("cls");
                subject();
                cout << "\n I N N O V A T O R   N O T   A D D E D\n";
                AddAgain(rawData);
            }
            // B: Ends here.
        }
    }
    else
        Menu(rawData);
}
// Function to handle the permission of editing an innovator.
void EditInnovator(Data &rawData)
{
    system("cls");
    subject();
    if (getChoice(search_to_edit_options, 2) == 1)
    {
        system("cls");
        subject();
        const int CHOICE = getChoice(NRC_OR_PASSPORT_options, 3);
        if (CHOICE >= 1 && CHOICE <= 2)
        {
            system("cls");
            subject();
            // Here it asks for the innovator to edit and returns that innovator.
            const vector<string> INNOVATOR_TO_EDIT = searcher(CHOICE, rawData.innovators);
            system("cls");
            subject();
            if (INNOVATOR_TO_EDIT.size() == 1)
            {
                DisplayInnovator(INNOVATOR_TO_EDIT[0]);
                // Asks for what to be edited and returns a chosen choice.
                const int EDIT_CHOICE = getChoice(options_to_edit, 9);
                if (EDIT_CHOICE >= 1 && EDIT_CHOICE <= 8)
                {
                    string newInfo;
                    // Gets the new required information based on the requested choice of edit.
                    if (EDIT_CHOICE == 7)
                    {
                        // When editing PATENT STATUS.
                        newInfo = PatentStatus();
                    }
                    else if (EDIT_CHOICE == 8)
                    {
                        // When editing INNOVATION CATEGORY.
                        newInfo = innovationCategoryChoice();
                    }
                    else
                    {
                        // Anything else
                        newInfo = userInput(selected_option_to_edit(EDIT_CHOICE));
                    }

                    cout << endl;
                    // And returns edited innovator
                    const string EDITED_INNOVATOR = innovatorEdition(INNOVATOR_TO_EDIT[0], newInfo, EDIT_CHOICE);
                    cout << EDITED_INNOVATOR;
                    system("cls");
                    subject();
                    if (getChoice(comfirm_options, 2) == 1)
                    {
                        system("cls");
                        subject();
                        const bool confirmation = confirmActionWithPassword(rawData.security);
                        if (confirmation)
                        {
                            PushEdited(INNOVATOR_TO_EDIT[0], EDITED_INNOVATOR, rawData.innovators);
                            system("cls");
                            subject();
                            cout << "\n I N N O V A T O R   S U C C E S S F U L L Y   E D I T E D\n";
                            EditAgin(rawData);
                        }
                        else
                        {
                            system("cls");
                            subject();
                            cout << "\n I N N O V A T O R   N O T   E D I T E D\n";
                            EditAgin(rawData);
                        }
                    }
                    else
                    {
                        system("cls");
                        subject();
                        cout << "\n P R O C C E S S   C A N C E L E D \n";
                        EditAgin(rawData);
                    }
                }
                else
                    Menu(rawData);
            }
            else
            {
                system("cls");
                subject();
                cout << "\n N O   I N N O V A T O R   W A S   F O U N D \n";
                EditAgin(rawData);
            }
        }
        else
            Menu(rawData);
    }
    else
        Menu(rawData);
}
// Function to handle the permission of deleting an innovator.
void DeleteInnovator(Data &rawData)
{
    system("cls");
    subject();
    if (getChoice(delete_innovator_option, 2) == 1)
    {
        system("cls");
        subject();
        const int CHOICE = getChoice(NRC_OR_PASSPORT_options, 3);
        if (CHOICE >= 1 && CHOICE <= 2)
        {
            system("cls");
            subject();
            const vector<string> INNOVATOR_TO_DELETE = searcher(CHOICE, rawData.innovators);

            if (INNOVATOR_TO_DELETE.size() == 1)
            {
                system("cls");
                subject();
                DisplayInnovator(INNOVATOR_TO_DELETE[0]);
                if (getChoice(comfirm_options, 2) == 1)
                {
                    system("cls");
                    subject();
                    const bool confirmation = confirmActionWithPassword(rawData.security);
                    if (confirmation)
                    {
                        RemoveInnovator(INNOVATOR_TO_DELETE[0], rawData.innovators);
                        system("cls");
                        subject();
                        cout << "\n I N N O V A T O R   S U C C E S S F U L L Y   D E L E T E D \n";
                        DeleteAgain(rawData);
                    }
                    else
                    {
                        system("cls");
                        subject();
                        cout << "\n I N N O V A T O R   N O T   D E L E T E D\n";
                        DeleteAgain(rawData);
                    }
                }
                else
                {
                    system("cls");
                    subject();
                    cout << "\n P R O C C E S S   C A N C E L E D \n";
                    DeleteAgain(rawData);
                }
            }
            else
            {
                system("cls");
                subject();
                cout << "\n N O   I N N O V A T O R   W A S   F O U N D \n";
                DeleteAgain(rawData);
            }
        }
        else
            Menu(rawData);
    }
    else
        Menu(rawData);
}
// Function to display innovators by their innovation category.
void DisplayInnovatorsByInnovationCategory(Data &rawData)
{
    system("cls");
    subject();
    const vector<string> ARRAY_OF_CATEGORIES = availableCategories(rawData.innovators);
    const int CATEGORY_CHOICE = getCategoryChoice(categoriesOptions, ARRAY_OF_CATEGORIES.size() + 1, rawData.innovators);
    // Stays in the category choice choosen.
    if (CATEGORY_CHOICE >= 1 && (CATEGORY_CHOICE <= ARRAY_OF_CATEGORIES.size()))
    {
        const string SEARCH_KEY = formKeyValue("innovation_category", ARRAY_OF_CATEGORIES[CATEGORY_CHOICE - 1]);
        const vector<string> INNOVATORS_WITH_SEARCH_KEY = SearchByKey(SEARCH_KEY, rawData.innovators);
        system("cls");
        subject();
        // When the innovators with the requested category are available
        if (INNOVATORS_WITH_SEARCH_KEY.size() != 0)
        {
            for (string innovator : INNOVATORS_WITH_SEARCH_KEY)
            {
                DisplayInnovator(innovator);
            }
            cout << endl;
            DisplayAgain(rawData);
        }
        else
            DisplayAgain(rawData);
    }
    else
        Menu(rawData);
}
// Function that saves innovators records to the required .txt file.
void SaveRocords(vector<string> innovators, string directory)
{
    manageFile("empty", directory);
    for (string innovator : innovators)
    {
        manageFile("write", directory, innovator);
    }
}
// This function exits the user out of the system by first saving modifications made back the innovation .txt file.
// Then the user gets exited.
void ExitUser(vector<string> innovators)
{
    const string INNOVATORS_DIRECTORY = "./TextFiles/INNOVATORS.TXT";
    // Saves records.
    SaveRocords(innovators, INNOVATORS_DIRECTORY);
    // Returns to the first stage og the system.
    ZHub();
}
// Function to set user permissions as menu options based on the user.
void Menu(Data &rawData)
{
    system("cls");
    // When the user is the MANAGER (OR) COORDINATOR.
    if (rawData.position >= 1 && rawData.position <= 2)
    {
        // system("cls");
        const int CHOICE = getChoice(main_user_permissions_options, 6);
        if (CHOICE >= 1 && CHOICE <= 5)
            if (CHOICE == 1)
                AddInnovator(rawData);
            else if (CHOICE == 2)
                DeleteInnovator(rawData);
            else if (CHOICE == 3)
                SearchInnovator(rawData);
            else if (CHOICE == 4)
                EditInnovator(rawData);
            else
                DisplayInnovatorsByInnovationCategory(rawData);
        else
            ExitUser(rawData.innovators);
    }
    // When the user is the TECHNITIAN.
    else
    {
        if (getChoice(sub_user_permissions_options, 2) == 1)
            SearchInnovator(rawData);
        else
            ExitUser(rawData.innovators);
    }
}
// This function initates all the required process for ZHub functionality.
void ZHub()
{
    system("cls");
    subject();
    // Directory location of a .txt file containg eligible users.
    const string USERS_DIRECTORY = "./TextFiles/USERS.TXT";
    // User Authentication function involked so as to authorise the user before getting access to the ZHub.
    const Status STATUS = UserAuth(USERS_DIRECTORY);

    // When the STATUS access is true; access is granted.
    if (STATUS.access)
    {
        const string INNOVATORS_DIRECTORY = "./TextFiles/INNOVATORS.TXT";
        Data rawData;
        // Data struct to hold: Innovators, position and security data of the user granted access.
        rawData.position = STATUS.position;
        rawData.innovators = ReloadRecords(INNOVATORS_DIRECTORY);
        rawData.security.roleName = STATUS.roleName;
        rawData.security.password = STATUS.password;
        // Displays the menu based on the user permissions.
        Menu(rawData);
    }
    // Otherwise no access to be granted.
    else
    {
        // Start over agin;
        ZHub();
    }
}
