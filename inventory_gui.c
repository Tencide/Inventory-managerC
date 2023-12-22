#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Define a structure to represent an inventory item
struct InventoryItem {
    char name[50];
    int quantity;
};

// Function to update the inventory
void updateInventory(FILE *file, struct InventoryItem *item, int restock) {
    int quantity;
    char action[20];
    
    strcpy(action, (restock ? "restock" : "update"));
    
    printf("Enter the quantity of %s to %s: ", item->name, action);
    scanf("%d", &quantity);

    if (quantity > 0) {
        // Update the item quantity
        if (restock) {
            item->quantity += quantity;
        } else {
            if (item->quantity < quantity) {
                printf("Not enough items in inventory. Inventory not updated.\n");
                return;
            }
            item->quantity -= quantity;
        }

        // Move the file cursor to the beginning of the file
        fseek(file, 0, SEEK_SET);

        // Write the updated quantities to the file
        fprintf(file, "Carmel Vanilla coffee: %d\nColumbia coffee: %d\n"
                      "English black tea: %d\nStarbucks coffee: %d\n"
                      "Apple cider: %d\nHot cocoa: %d\nPumpkin spice: %d\n",
                inventory[0].quantity, inventory[1].quantity, inventory[2].quantity,
                inventory[3].quantity, inventory[4].quantity, inventory[5].quantity, inventory[6].quantity);

        // Move the file cursor back to the beginning after writing
        rewind(file);

        printf("Inventory %s. There are now %d %s left.\n", action, item->quantity, item->name);
    } else {
        printf("Invalid quantity entered. Inventory not %s.\n", action);
    }
}

// Function to add a new item to the inventory
void addNewItem(FILE *file) {
    struct InventoryItem newItem;

    printf("Enter the name of the new item: ");
    scanf("%s", newItem.name);

    printf("Enter the initial quantity of %s: ", newItem.name);
    scanf("%d", &newItem.quantity);

    // Move the file cursor to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Write the new item and its initial quantity to the file
    fprintf(file, "%s: %d\n", newItem.name, newItem.quantity);

    // Move the file cursor back to the beginning after writing
    rewind(file);

    printf("New item '%s' added to the inventory with an initial quantity of %d.\n", newItem.name, newItem.quantity);
}

// Function to display the simplified menu
void displayMenu() {
    printf("Inventory Menu:\n");
    printf("A. Carmel Vanilla coffee\n");
    printf("B. Columbia coffee\n");
    printf("C. English black tea\n");
    printf("D. Starbucks coffee\n");
    printf("E. Apple cider\n");
    printf("F. Hot cocoa\n");
    printf("G. Pumpkin spice\n");
    printf("H. Add new item\n");
    printf("Q. Quit\n");
}

int main() {
    FILE *file = fopen("inventory.txt", "r+");

    if (file == NULL) {
        printf("Error opening file for reading and updating.\n");
        return 1;
    }

    struct InventoryItem inventory[7];  // Array to store inventory items

    // Read the initial values from the file
    fscanf(file, "Carmel Vanilla coffee: %d\nColumbia coffee: %d\n"
                 "English black tea: %d\nStarbucks coffee: %d\n"
                 "Apple cider: %d\nHot cocoa: %d\nPumpkin spice: %d\n",
           &inventory[0].quantity, &inventory[1].quantity, &inventory[2].quantity,
           &inventory[3].quantity, &inventory[4].quantity, &inventory[5].quantity, &inventory[6].quantity);

    printf("Initial Inventory:\nCarmel Vanilla coffee: %d\nColumbia coffee: %d\n"
           "English black tea: %d\nStarbucks coffee: %d\n"
           "Apple cider: %d\nHot cocoa: %d\nPumpkin spice: %d\n",
           inventory[0].quantity, inventory[1].quantity, inventory[2].quantity,
           inventory[3].quantity, inventory[4].quantity, inventory[5].quantity, inventory[6].quantity);

    char updateChoice;
    do {
        displayMenu();
        printf("Do you want to (U)pdate, (R)estock, (A)dd new item, or (Q)uit: ");
        scanf(" %c", &updateChoice);

        switch (toupper(updateChoice)) {
            case 'U':
                displayMenu();
                printf("Enter the letter of the item you want to update: ");
                scanf(" %c", &updateChoice);
                switch (toupper(updateChoice)) {
                    case 'A':
                        updateInventory(file, &inventory[0], 0);
                        break;
                    case 'B':
                        updateInventory(file, &inventory[1], 0);
                        break;
                    // ... similar cases for other items
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 'R':
                displayMenu();
                printf("Enter the letter of the item you want to restock: ");
                scanf(" %c", &updateChoice);
                switch (toupper(updateChoice)) {
                    case 'A':
                        updateInventory(file, &inventory[0], 1);
                        break;
                    case 'B':
                        updateInventory(file, &inventory[1], 1);
                        break;
                    // ... similar cases for other items
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 'A':
                addNewItem(file);
                break;
            case 'Q':
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (updateChoice != 'Q' && updateChoice != 'q');

    fclose(file);

    return 0;
}
