#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Apartment
{
    char ownerName[30];
    char area[50];
    int rent;
    int floor;
    int rooms;
    int bathrooms;
    int balconies;
    char contact[30];
    char additionalInfo[500];
};


int adminLogin();
int userLogin();
void addApartment();
void viewAllApartments();
void searchApartments();
void editApartment();
void deleteApartment();

int main()
{
    int mainChoice;

    while (1)
    {
        printf("ASROY - Dhaka Apartment Renting Management \n\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);
        getchar();

        if (mainChoice == 1)
        {
            if (adminLogin())
            {
                int adminChoice;
                printf("\nWelcome Admin!\n");

                while (1)
                {
                    printf("\n ADMIN MENU \n");
                    printf("------------\n");
                    printf("1. View All Apartments\n");
                    printf("2. Edit Any Apartment\n");
                    printf("3. Delete Any Apartment\n");
                    printf("4. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);
                    getchar();

                    if (adminChoice == 1) viewAllApartments();
                    else if (adminChoice == 2) editApartment();
                    else if (adminChoice == 3) deleteApartment();
                    else if (adminChoice == 4) break;
                    else printf("\nInvalid choice!\n");
                }
            }

            else
            {
                printf("\nLogin Failed! \n");
            }

        }



        else if (mainChoice == 2)
        {
            if (userLogin())
            {
                int userChoice;
               printf("\nWelcome Dear User!\n");

                while (1)
                {
                    printf("\n USER MENU \n");
                    printf("-----------\n");
                    printf("1. Add New Apartment\n");
                    printf("2. View All Apartments\n");
                    printf("3. Search Apartments\n");
                    printf("4. Edit My Listing\n");
                    printf("5. Delete My Listing\n");
                    printf("6. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &userChoice);
                    getchar();

                    if (userChoice == 1) addApartment();
                    else if (userChoice == 2) viewAllApartments();
                    else if (userChoice == 3) searchApartments();
                    else if (userChoice == 4) editApartment();
                    else if (userChoice == 5) deleteApartment();
                    else if (userChoice == 6) break;
                    else printf("\nInvalid choice!\n");
                }
            }

            else
            {
                printf("\n Login Failed! \n\n");
            }
        }

        else if (mainChoice == 3)
        {
            printf("\n Thank you! Goodbye! \n");
            break;
        }

        else
        {
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

int adminLogin()
{
    char username[20], password[20];

    printf("\n[Admin Login]\n");
    printf("-------------\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    getchar();

    if (strcmp(username, "admin") == 0 && strcmp(password, "7979") == 0)
    {

        return 1;
    }
    return 0;
}

int userLogin()
{
    char username[20], password[20];

    printf("\n[User Login] \n");
    printf("------------\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    getchar();

    if (strcmp(username, "user") == 0 && strcmp(password, "9595") == 0)
    {
        return 1;
    }

    return 0;
}

void addApartment()
{
    struct Apartment apt;
    FILE *file;

    printf("\nAdd New Apartment \n");
    printf("-----------------\n");

    printf("Owner Name: ");
    scanf(" %[^\n]", apt.ownerName);
    getchar();

    printf("Area/Address: ");
    scanf(" %[^\n]", apt.area);
    getchar();

    printf("Monthly Rent (Taka): ");
    scanf("%d", &apt.rent);
    getchar();

    printf("Floor Number: ");
    scanf("%d", &apt.floor);
    getchar();

    printf("Number of Rooms: ");
    scanf("%d", &apt.rooms);
    getchar();

    printf("Number of Bathrooms: ");
    scanf("%d", &apt.bathrooms);
    getchar();

    printf("Number of Balconies: ");
    scanf("%d", &apt.balconies);
    getchar();

    printf("Contact Number: ");
    scanf(" %[^\n]", apt.contact);
    getchar();

    printf("Additional Information: ");
    scanf(" %[^\n]", apt.additionalInfo);
    getchar();

    file = fopen("apartments.dat", "ab");
    if (file == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(&apt, sizeof(struct Apartment), 1, file);
    fclose(file);

    printf("\nApartment Added Successfully! \n");
}

void viewAllApartments()
{
    struct Apartment apt;
    FILE *file;
    int count = 0;

    file = fopen("apartments.dat", "rb");
    if (file == NULL)
    {
        printf("\nNo apartments found.\n");
        return;
    }


    printf("\nALL APARTMENTS\n");
    printf("----------------\n");

    while (!feof(file))
    {
        if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
        {
            count++;
            printf("\n--- Apartment #%d ---\n", count);
            printf("Owner: %s\n", apt.ownerName);
            printf("Area: %s\n", apt.area);
            printf("Rent: %d Taka/month\n", apt.rent);
            printf("Floor: %d\n", apt.floor);
            printf("Rooms: %d\n", apt.rooms);
            printf("Bathrooms: %d\n", apt.bathrooms);
            printf("Balconies: %d\n", apt.balconies);
            printf("Contact: %s\n", apt.contact);
            printf("Additional Info: %s\n", apt.additionalInfo);

        }
    }

    fclose(file);

    if (count == 0) printf("\nNo apartments available.\n");
    else printf("\nTotal Apartments: %d\n", count);
}

void searchApartments()
{
    struct Apartment apt;
    FILE *file;
    int searchChoice, count = 0;

    printf("\n Search Apartments \n");
    printf("-------------------\n");
    printf("1. Search by Area\n");
    printf("2. Search by Maximum Rent\n");
    printf("3. Search by Number of Rooms\n");
    printf("4. Search by Floor\n");
    printf("Enter search type: ");
    scanf("%d", &searchChoice);
    getchar();

    file = fopen("apartments.dat", "rb");

    if (file == NULL)
    {
        printf("\nNo apartments found.\n");
        return;
    }

    if (searchChoice == 1)
    {
        char searchArea[50];
        printf("Enter area: ");
        scanf(" %[^\n]", searchArea);
        getchar();

        printf("\nSearch Results\n");
        while (!feof(file))
        {
            if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
            {
                if (strstr(apt.area, searchArea) != NULL)
                {
                    count++;
                    printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
                    printf("    Floor: %d | Rooms: %d | Bathrooms: %d | Balconies: %d\n",
                           apt.floor, apt.rooms, apt.bathrooms, apt.balconies);
                    printf("    Contact: %s\n", apt.contact);
                    printf("    Info: %s\n", apt.additionalInfo);
                }
            }
        }
    }


    else if (searchChoice == 2)
    {
        int maxRent;
        printf("Enter maximum rent: ");
        scanf("%d", &maxRent);
        getchar();

        printf("\nResults (Rent <= %d)\n", maxRent);

        while (!feof(file))
        {
            if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
            {
                if (apt.rent <= maxRent)
                {
                    count++;
                    printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
                    printf("    Floor: %d | Rooms: %d | Bathrooms: %d | Balconies: %d\n",
                           apt.floor, apt.rooms, apt.bathrooms, apt.balconies);
                    printf("    Contact: %s\n", apt.contact);
                }
            }
        }
    }

    else if (searchChoice == 3)
    {
        int numRooms;
        printf("Enter number of rooms: ");
        scanf("%d", &numRooms);
        getchar();

        printf("\n--- Results (%d Rooms) ---\n", numRooms);

        while (!feof(file))
        {
            if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
            {
                if (apt.rooms == numRooms)
                {
                    count++;
                    printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
                    printf("    Floor: %d | Rooms: %d | Bathrooms: %d | Balconies: %d\n",
                           apt.floor, apt.rooms, apt.bathrooms, apt.balconies);
                    printf("    Contact: %s\n", apt.contact);
                }
            }
        }
    }

    else if (searchChoice == 4)
    {
        int floorNum;
        printf("Enter floor number: ");
        scanf("%d", &floorNum);
        getchar();

        printf("\n Results (Floor %d) \n", floorNum);
        while (!feof(file))
        {
            if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
            {
                if (apt.floor == floorNum)
                {
                    count++;
                    printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
                    printf("    Floor: %d | Rooms: %d | Bathrooms: %d | Balconies: %d\n",
                           apt.floor, apt.rooms, apt.bathrooms, apt.balconies);
                    printf("    Contact: %s\n", apt.contact);
                }
            }
        }
    }

    else
    {
        printf("\nInvalid option!\n");
        fclose(file);
        return;
    }

    fclose(file);
    if (count == 0) printf("\nNo matches found.\n");
    else printf("\nTotal matches: %d\n", count);
}

void editApartment()
{
    struct Apartment apt, apartments[100];
    FILE *file, *temp;
    char searchArea[50];
    int recordNum = 0, selectedRecord, editChoice, count = 0, positions[100];

    printf("\nEdit Apartment \n");
    printf("----------------\n");
    printf("Enter area to search: ");
    scanf(" %[^\n]", searchArea);
    getchar();

    file = fopen("apartments.dat", "rb");
    if (file == NULL)
    {
        printf("\nNo apartments found!\n");
        return;
    }

    printf("\nMatching Apartments \n");
    while (!feof(file))
    {
        recordNum++;

        if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
        {
            if (strstr(apt.area, searchArea) != NULL)
            {
                apartments[count] = apt;
                positions[count] = recordNum;
                count++;
                printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
            }
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("\nNo matches found.\n");
        return;
    }

    printf("\nEnter number to edit (1-%d): ", count);
    scanf("%d", &selectedRecord);
    getchar();

    if (selectedRecord < 1 || selectedRecord > count)
    {
        printf("\nInvalid selection!\n");
        return;
    }

    printf("\nSelect Field to Edit\n");
    printf("1. Owner Name\n2. Area/Address\n3. Rent\n4. Floor\n");
    printf("5. Rooms\n6. Bathrooms\n7. Balconies\n8. Contact\n");
    printf("9. Additional Info\n10. Edit All Fields\n");
    printf("Enter choice: ");
    scanf("%d", &editChoice);
    getchar();

    struct Apartment *selected = &apartments[selectedRecord - 1];

    if (editChoice == 1 || editChoice == 10)
    {
        printf("New Owner Name: ");
        scanf(" %[^\n]", selected->ownerName);
        getchar();
    }
    if (editChoice == 2 || editChoice == 10)
    {
        printf("New Area: ");
        scanf(" %[^\n]", selected->area);
        getchar();
    }
    if (editChoice == 3 || editChoice == 10)
    {
        printf("New Rent: ");
        scanf("%d", &selected->rent);
        getchar();
    }
    if (editChoice == 4 || editChoice == 10)
    {
        printf("New Floor: ");
        scanf("%d", &selected->floor);
        getchar();
    }
    if (editChoice == 5 || editChoice == 10)
    {
        printf("New Rooms: ");
        scanf("%d", &selected->rooms);
        getchar();
    }
    if (editChoice == 6 || editChoice == 10)
    {
        printf("New Bathrooms: ");
        scanf("%d", &selected->bathrooms);
        getchar();
    }
    if (editChoice == 7 || editChoice == 10)
    {
        printf("New Balconies: ");
        scanf("%d", &selected->balconies);
        getchar();
    }
    if (editChoice == 8 || editChoice == 10)
    {
        printf("New Contact: ");
        scanf(" %[^\n]", selected->contact);
        getchar();
    }
    if (editChoice == 9 || editChoice == 10)
    {
        printf("New Additional Info: ");
        scanf(" %[^\n]", selected->additionalInfo);
        getchar();
    }

    file = fopen("apartments.dat", "rb");
    temp = fopen("temp.dat", "wb");

    recordNum = 0;
    while (!feof(file))
    {
        if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
        {
            recordNum++;

            if (recordNum == positions[selectedRecord - 1])
            {
                fwrite(selected, sizeof(struct Apartment), 1, temp);
            }

            else
            {
                fwrite(&apt, sizeof(struct Apartment), 1, temp);
            }

        }
    }

    fclose(file);
    fclose(temp);
    remove("apartments.dat");
    rename("temp.dat", "apartments.dat");

    printf("\nUpdated Successfully!\n");
}

void deleteApartment()
{
    struct Apartment apt, apartments[100];
    FILE *file, *temp;
    char searchArea[50];
    int recordNum = 0, selectedRecord, count = 0, positions[100];

    printf("\nDelete Apartment\n");
    printf("------------------\n");
    printf("Enter area to search: ");
    scanf(" %[^\n]", searchArea);
    getchar();

    file = fopen("apartments.dat", "rb");
    if (file == NULL)
    {
        printf("\nNo apartments found!\n");
        return;
    }

    printf("\nMatching Apartments \n");

    while (!feof(file))
    {
        recordNum++;

        if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
        {
            if (strstr(apt.area, searchArea) != NULL)
            {
                apartments[count] = apt;
                positions[count] = recordNum;
                count++;
                printf("\n[%d] %s - %s - %d Taka\n", count, apt.ownerName, apt.area, apt.rent);
            }
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("\nNo matches found.\n");
        return;
    }

    printf("\nEnter number to delete (1-%d): ", count);
    scanf("%d", &selectedRecord);
    getchar();

    if (selectedRecord < 1 || selectedRecord > count)
    {
        printf("\nInvalid selection!\n");
        return;
    }

    char confirm;
    printf("Confirm delete? (y/n): ");
    scanf("%c", &confirm);
    getchar();

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("\nCancelled.\n");
        return;
    }

    file = fopen("apartments.dat", "rb");
    temp = fopen("temp.dat", "wb");

    recordNum = 0;
    while (!feof(file))
    {
        if (fread(&apt, sizeof(struct Apartment), 1, file) == 1)
        {
            recordNum++;

            if (recordNum != positions[selectedRecord - 1])
            {
                fwrite(&apt, sizeof(struct Apartment), 1, temp);
            }
        }
    }

    fclose(file);
    fclose(temp);
    remove("apartments.dat");
    rename("temp.dat", "apartments.dat");

    printf("\nDeleted Successfully!\n");
}
