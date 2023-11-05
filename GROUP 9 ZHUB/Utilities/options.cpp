using namespace std;
//
void subject()
{
    cout << " Z - H U B   I N N O V A T I O N S \n\n";
}
void optionsOfRole()
{
    cout << "\n Z - H U B   U S E R S";
    cout << "\n\n L O G I N   A S   T H E    H U B:  ";
    cout << "\n\n 1 - MANAGER";
    cout << "\n 2 - COORDINATOR";
    cout << "\n 3 - TECHNITIAN";
}
void main_user_permissions_options()
{
    cout << "\n M A I N   M E N U\n";
    cout << "\n 1 - ADD INNOVATOR";
    cout << "\n 2 - DELETE INNOVATOR RECORD";
    cout << "\n 3 - SEARCH FOR INNOVATOR";
    cout << "\n 4 - EDIT INNOVATOR RECORD";
    cout << "\n 5 - DISPLAY INNOVATOR BY INNOVATION CATEGORY";
    cout << "\n 6 - EXIT";
}
void sub_user_permissions_options()
{
    cout << "\n M A I N   M E N U\n";
    cout << "\n 1 - SEARCH FOR INNOVATOR";
    cout << "\n 2 - EXIT";
}

void NRC_OR_PASSPORT_options()
{
    cout << "\n T A K E   A C T I O N   W I T H ";
    cout << "\n 1 - NRC No";
    cout << "\n 2 - PASSPORT No";
    cout << "\n 3 - MAIN MENU";
}
void search_again_options()
{
    cout << "\n 1 - SEARCH AGAIN ";
    cout << "\n 2 - MAIN MENU ";
}
void delete_again_options()
{
    cout << "\n 1 - DELETE AGAIN ";
    cout << "\n 2 - MAIN MENU ";
}
void add_again_options()
{
    cout << "\n 1 - ADD AGAIN ";
    cout << "\n 2 - MAIN MENU ";
}
void edit_again_options()
{
    cout << "\n 1 - EDIT AGAIN ";
    cout << "\n 2 - MAIN MENU ";
}
void display_again_options()
{
    cout << "\n 1 - DISPLAY AGAIN ";
    cout << "\n 2 - MAIN MENU ";
}
void search_to_edit_options()
{
    cout << "\n E D I T   I N N O V A T O R";
    cout << "\n 1 - SEARCH INNOVATOR TO EDIT ";
    cout << "\n 2 - MAIN MENU ";
}
void delete_innovator_option()
{
    // subject();
    cout << "\n D E L E T E   I N N O V A T O R";
    cout << "\n 1 - SEARCH INNOVATOR TO DELETE ";
    cout << "\n 2 - MAIN MENU ";
}
void options_to_edit()
{
    cout << "\n W H A T   D O   Y O U   W A N T   T O   E D I T";
    cout << "\n 1 - NRC No.";
    cout << "\n 2 - PASSPORT No.";
    cout << "\n 3 - FIRSTNAME. ";
    cout << "\n 4 - LASTNAME. ";
    cout << "\n 5 - AGE. ";
    cout << "\n 6 - TITLE OF INNOVATION. ";
    cout << "\n 7 - PATENT STATUS. ";
    cout << "\n 8 - INNOVATION CATEGORY. ";
    cout << "\n 9 - MAIN MENU ";
}
string selected_option_to_edit(int option)
{
    const string OPTIONS[8] = {
        " ENTER NEW NRC No:   ",
        " ENTER NEW PASSPORT No:   ",
        " ENTER NEW FIRSTNAME:   ",
        " ENTER NEW LASNAME:   ",
        " ENTER NEW AGE:   ",
        " ENTER NEW TITLE OF INNOVATION:   ",
        " ENTER NEW PATTENT STATUS:   ",
        " ENTER NEW INNOVATION CATEGORY:   ",
    };
    return "\n" + OPTIONS[option - 1];
}
void comfirm_options()
{
    cout << "\n ARE YOU SURE YOU WANT TO TAKE THIS ACTION?";
    cout << "\n 1 - SURE YES ";
    cout << "\n 2 - SURE NO ";
}
void patentsOptions()
{
    cout << "\n CHOOSE PATENT STATUS: ";
    cout << "\n 1 - PATENED ";
    cout << "\n 2 - IN PROGRESS ";
    cout << "\n 3 - NOT REQUIRED ";
}

void innovationCategoriesOptions()
{
    cout << "\n CHOOSE INNOVATION CATEGORY: ";
    cout << "\n 1 - FoodTech ";
    cout << "\n 2 - WoodTech ";
    cout << "\n 3 - MetalTech ";
    cout << "\n 4 - IT ";
    cout << "\n 5 - Other ";
}