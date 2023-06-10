#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_ITEM_LENGTH 50

typedef struct item
{
    char name[MAX_ITEM_LENGTH];
    struct item *prev;
    struct item *next;
} Item;

typedef struct name
{
    char name[MAX_NAME_LENGTH];
    Item *head;
    Item *tail;
    struct name *prev;
    struct name *next;
} Name;

typedef struct board
{
    Name *head;
    Name *tail;
} Board;

// Function prototypes
void display(Board *board);
void load(Board *board);
void edit_item(Board *board);
void edit_board(Board *board);
void save_board(Board *board, char *filename);

int main()
{
    Board board = { NULL, NULL };
    char filename[MAX_NAME_LENGTH];


    Name *name1 = malloc(sizeof(Name));
    strcpy(name1->name, "Cian");
    name1->prev = NULL;
    name1->next = NULL;
    board.head = name1;
    board.tail = name1;

    Item *item1 = malloc(sizeof(Item));
    strcpy(item1->name, "firestick");
    item1->prev = NULL;
    item1->next = NULL;
    name1->head = item1;
    name1->tail = item1;

    Name *name2 = malloc(sizeof(Name));
    strcpy(name2->name, "Lloyd");
    name2->prev = name1;
    name2->next = NULL;
    name1->next = name2;
    board.tail = name2;

    Item *item2 = malloc(sizeof(Item));
    strcpy(item2->name, "xbox");
    item2->prev = NULL;
    item2->next = NULL;
    name2->head = item2;
    name2->tail = item2;

    Name *name3 = malloc(sizeof(Name));
    strcpy(name3->name, "Jamie");
    name3->prev = name2;
    name3->next = NULL;
    name2->next = name3;
    board.tail = name3;

    Item *item3a = malloc(sizeof(Item));
    strcpy(item3a->name, "psp");
    item3a->prev = NULL;
    item3a->next = NULL;
    name3->head = item3a;
    name3->tail = item3a;

    Item *item3b = malloc(sizeof(Item));
    strcpy(item3b->name, "wii");
    item3b->prev = item3a;
    item3b->next = NULL;
    item3a->next = item3b;
    name3->tail = item3b;

    Name *name4 = malloc(sizeof(Name));
    strcpy(name4->name, "Tom");
    name4->prev = name3;
    name4->next = NULL;
    name3->next = name4;
    board.tail = name4;

    Item *item4a = malloc(sizeof(Item));
    strcpy(item4a->name, "playstation");
    item4a->prev = NULL;
    item4a->next = NULL;
    name4->head = item4a;
    name4->tail = item4a;

    Item *item4b = malloc(sizeof(Item));
    strcpy(item4b->name, "nintendo");
    item4b->prev = item4a;
    item4b->next = NULL;
    item4a->next = item4b;
    name4->tail = item4b;


    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Display board\n");
        printf("2. Load board from a file\n");
        printf("3. Edit item on list\n");
        printf("4. Edit board\n");
        printf("5. Save board to a file\n");
        printf("6. Quit\n");
        printf("Enter your choice (1-6):\n");
        int choice;
        scanf("%d", &choice);



        switch (choice)
        {
            case 1:
                display(&board);
                break;
            case 2:
                load(&board);
                break;
            case 3:
                edit_item(&board);
                break;
            case 4:
                edit_board(&board);
                break;
            case 5:
                printf("Enter a file name:\n");
                scanf("%s", filename);
                save_board(&board, filename);
                break;
            case 6:
                printf("                                  ____                 \n"
                       "  ,----..     ,----..           ,'  , `.               \n"
                       " /   /   \\   /   /   \\       ,-+-,.' _ |         ,--,  \n"
                       "|   :     : |   :     :   ,-+-. ;   , ||       ,'_ /|  \n"
                       ".   |  ;. / .   |  ;. /  ,--.'|'   |  ;|  .--. |  | :  \n"
                       ".   ; /--`  .   ; /--`  |   |  ,', |  ':,'_ /| :  . |  \n"
                       ";   | ;  __ ;   | ;  __ |   | /  | |  |||  ' | |  . .  \n"
                       "|   : |.' .'|   : |.' .''   | :  | :  |,|  | ' |  | |  \n"
                       ".   | '_.' :.   | '_.' :;   . |  ; |--' :  | | :  ' ;  \n"
                       "'   ; : \\  |'   ; : \\  ||   : |  | ,    |  ; ' |  | '  \n"
                       "'   | '/  .''   | '/  .'|   : '  |/     :  | : ;  ; |  \n"
                       "|   :    /  |   :    /  ;   | |`-'      '  :  `--'   \\ \n"
                       " \\   \\ .'    \\   \\ .'   |   ;/          :  ,      .-./ \n"
                       "  `---`       `---`     '---'            `--`----'    ");


                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        if (choice == 6)
        {
            return 0;
        }
    }


}


void display(Board *board)
{
    if (board->head == NULL) {
        printf("Board is empty.\n");
        return;
    }

    Name *current_name = board->head;

    while (current_name != NULL) {
        printf("%s:\n", current_name->name);

        if (current_name->head == NULL) {
            printf("\tNo items for this name.\n");
        } else {
            Item *current_item = current_name->head;

            while (current_item != NULL) {
                printf("\t%s\n", current_item->name);
                current_item = current_item->next;
            }
        }

        current_name = current_name->next;
    }
}

void load(Board *board)
{
    printf("Enter the filename to load: ");
    char filename[100];
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s\n", filename);
        return;
    }

    // Clear the current board
    Name *current_name = board->head;
    while (current_name) {
        Item *current_item = current_name->head;
        while (current_item) {
            Item *next_item = current_item->next;
            free(current_item);
            current_item = next_item;
        }
        Name *next_name = current_name->next;
        free(current_name);
        current_name = next_name;
    }
    board->head = NULL;
    board->tail = NULL;

    // Read the file and create a new board
    Name *name = NULL;
    Item *item = NULL;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Trim whitespace from the end of the line
        char *end = buffer + strlen(buffer) - 1;
        while (end > buffer && isspace(*end)) {
            *end = '\0';
            end--;
        }

        // Ignore empty lines
        if (strlen(buffer) == 0) {
            continue;
        }

        // If the line starts with a tab, it's an item
        if (buffer[0] == '\t') {
            // Create a new item
            Item *new_item = malloc(sizeof(Item));
            strcpy(new_item->name, buffer + 1);
            new_item->prev = item;
            new_item->next = NULL;

            // Add the item to the current name
            item->next = new_item;
            item = new_item;
        } else {
            // Create a new name
            Name *new_name = malloc(sizeof(Name));
            strcpy(new_name->name, buffer);
            new_name->head = NULL;
            new_name->tail = NULL;
            new_name->prev = name;
            new_name->next = NULL;

            // Add the name to the board
            if (!board->head) {
                board->head = new_name;
            }
            if (board->tail) {
                board->tail->next = new_name;
            }
            board->tail = new_name;

            // Set the current name and item to the new ones
            name = new_name;
            item = NULL;
        }
    }

    fclose(file);

    printf("Board loaded from file %s\n", filename);
}

void edit_item(Board *board)
{
    char name[MAX_NAME_LENGTH];

    printf("Enter the name of the person whose item you want to edit:\n");
    fflush(stdin);
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    Name *current_name = board->head;
    while (current_name != NULL && strcmp(current_name->name, name) != 0)
    {
        current_name = current_name->next;
    }

    if (current_name == NULL)
    {
        printf("Person not found on the list.\n");
        return;
    }

    printf("Enter the name of the item you want to edit:\n");
    char item_name[MAX_ITEM_LENGTH];
    fgets(item_name, MAX_ITEM_LENGTH, stdin);
    item_name[strcspn(item_name, "\n")] = '\0';

    Item *current_item = current_name->head;
    while (current_item != NULL && strcmp(current_item->name, item_name) != 0)
    {
        current_item = current_item->next;
    }

    if (current_item == NULL)
    {
        printf("Item not found for this person.\n");
        return;
    }

    printf("Select the option you want to perform:\n");
    printf("1. Edit the name of the item\n");
    printf("2. Add a new item for this person\n");
    printf("3. Delete the item\n");
    printf("4. Return to main menu\n");
    int option;
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            printf("Enter the new name of the item:\n");
            fflush(stdin);
            fgets(current_item->name, MAX_ITEM_LENGTH, stdin);
            current_item->name[strcspn(current_item->name, "\n")] = '\0';
            break;
        case 2:
        {
            Item *new_item = malloc(sizeof(Item));
            printf("Enter the name of the new item:\n");
            fflush(stdin);
            fgets(new_item->name, MAX_ITEM_LENGTH, stdin);
            new_item->name[strcspn(new_item->name, "\n")] = '\0';
            new_item->prev = current_name->tail;
            new_item->next = NULL;

            if (current_name->tail != NULL)
            {
                current_name->tail->next = new_item;
            }
            else
            {
                current_name->head = new_item;
            }

            current_name->tail = new_item;
            break;
        }
        case 3:
            if (current_item->prev != NULL)
            {
                current_item->prev->next = current_item->next;
            }
            else
            {
                current_name->head = current_item->next;
            }

            if (current_item->next != NULL)
            {
                current_item->next->prev = current_item->prev;
            }
            else
            {
                current_name->tail = current_item->prev;
            }

            free(current_item);
            break;
        case 4:
            return;
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
}

void edit_board(Board *board)
{
    // List menu
    printf("Select the option you want to perform:\n");
    printf("1.Edit the name of a list\n");
    printf("2.Add a new list\n");
    printf("3.Delete a list\n");
    printf("4.Return to main menu\n");

    int option;
    scanf("%d", &option);

    switch (option)
    {
        case 1:

            printf("Enter the name of the list to edit:\n");
            char current_name[MAX_NAME_LENGTH];

            fflush(stdin);
            fgets(current_name, MAX_NAME_LENGTH, stdin);
            current_name[strcspn(current_name, "\n")] = '\0';  // remove newline character
            // Find the list with the given name
            Name *name = board->head;
            while (name != NULL)
            {
                if (strcmp(name->name, current_name) == 0)
                {
                    printf("Enter a new name for list %s :\n", current_name);
                    char new_name[MAX_NAME_LENGTH];

                    fflush(stdin);
                    fgets(new_name, MAX_NAME_LENGTH, stdin);
                    new_name[strcspn(new_name, "\n")] = '\0';  // remove newline character
                    strcpy(name->name, new_name);
                    printf("List name updated\n");
                    return;
                }
                name = name->next;
            }
            printf("can't find list\n");
            break;

        case 2:

            printf("Enter the name of the new list:\n");
            char new_name[MAX_NAME_LENGTH];
            fflush(stdin);
            fgets(new_name, MAX_NAME_LENGTH, stdin);
            new_name[strcspn(new_name, "\n")] = '\0';  // remove newline character
            Name *new_list = malloc(sizeof(Name));
            strcpy(new_list->name, new_name);
            new_list->prev = board->tail;
            new_list->next = NULL;
            if (board->tail != NULL)
            {
                board->tail->next = new_list;
            }
            else
            {
                board->head = new_list;
            }

            board->tail = new_list;

            printf("List added\n");
            break;

        case 3:

            printf("Enter the name of the list to delete: \n");
            fflush(stdin);
            char delete_name[MAX_NAME_LENGTH];
            fgets(delete_name, MAX_NAME_LENGTH, stdin);
            delete_name[strcspn(delete_name, "\n")] = '\0';  // remove newline character

            // Find the list with the given name
            Name *delete_list = board->head;
            while (delete_list != NULL)
            {
                if (strcmp(delete_list->name, delete_name) == 0)
                {
                    // Remove the list from the board and free memory
                    if (delete_list->prev != NULL)
                    {
                        delete_list->prev->next = delete_list->next;
                    }
                    else
                    {
                        board->head = delete_list->next;
                    }

                    if (delete_list->next != NULL)
                    {
                        delete_list->next->prev = delete_list->prev;
                    }
                    else
                    {
                        board->tail = delete_list->prev;
                    }

                    Item *item = delete_list->head;
                    while (item != NULL)
                    {
                        Item *next_item = item->next;
                        free(item);
                        item = next_item;
                    }

                    free(delete_list);
                    printf("List deleted\n");
                    return;
                }

                delete_list = delete_list->next;
            }
            printf("Can't find the list\n");
            break;
        case 4:
            // Return to the main menu
            return;
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
}

void save_board(Board *board, char *filename)
{
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open file");
        return;
    }
    // Go through the list of the given names and items and write them to the file
    Name *current_name = board->head;
    while (current_name != NULL)
    {
        fprintf(file, "%s:\n", current_name->name);

        Item *current_item = current_name->head;
        while (current_item != NULL)
        {
            fprintf(file, "%s\n", current_item->name);
            current_item = current_item->next;
        }

        current_name = current_name->next;
    }
    // close file
    fclose(file);

    printf("successfully saved to file %s\n", filename);
}

