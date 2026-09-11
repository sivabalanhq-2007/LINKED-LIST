#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_FRIENDS 5

// List of friends mapped to array indices
const char *FRIEND_NAMES[TOTAL_FRIENDS] = {"Arjun", "Priya", "Kavin", "Meena", "Sanjay"};

// Structure for a shopping item
struct Item
{
    int itemId;
    char friendName[30];
    char itemName[40];
    char brand[30];
    int quantity;
    float price;
};

// Singly linked list node
struct Node
{
    struct Item item;
    struct Node *next;
};

// Array of Linked List Heads: each index represents one friend's list
struct Node *friendLists[TOTAL_FRIENDS] = {NULL, NULL, NULL, NULL, NULL};

// Helper: Maps friend's name to their array index (0 to 4)
int getFriendIndex(const char *name)
{
    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        if (strcasecmp(FRIEND_NAMES[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 1. Add / Insert Item into a specific friend's linked list
void insertItem()
{
    char friend[30];
    printf("Enter Friend Name (Arjun/Priya/Kavin/Meena/Sanjay): ");
    scanf("%s", friend);

    int index = getFriendIndex(friend);
    if (index == -1)
    {
        printf("Invalid friend name! Item not added.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newNode->item.friendName, FRIEND_NAMES[index]);

    printf("Enter Item ID: ");
    scanf("%d", &newNode->item.itemId);

    printf("Enter Item Name: ");
    scanf(" %[^\n]s", newNode->item.itemName);

    printf("Enter Brand: ");
    scanf("%s", newNode->item.brand);

    printf("Enter Quantity: ");
    scanf("%d", &newNode->item.quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &newNode->item.price);

    newNode->next = NULL;

    // Append to friend's dedicated linked list
    if (friendLists[index] == NULL)
    {
        friendLists[index] = newNode;
    }
    else
    {
        struct Node *temp = friendLists[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Item added to %s's list successfully!\n", FRIEND_NAMES[index]);
}

// 2. Delete / Cancel Item across all linked lists
void deleteItem()
{
    int id;
    printf("Enter Item ID to remove/cancel: ");
    scanf("%d", &id);

    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        struct Node *temp = friendLists[i];
        struct Node *prev = NULL;

        while (temp != NULL && temp->item.itemId != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL)
        {
            if (prev == NULL)
            {
                friendLists[i] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);
            printf("Item ID %d removed from %s's list successfully!\n", id, FRIEND_NAMES[i]);
            return;
        }
    }

    printf("Item ID %d not found in any shopping list.\n", id);
}

// 3. Update / Replace Item across all linked lists
void updateItem()
{
    int id;
    printf("Enter Item ID to update/replace: ");
    scanf("%d", &id);

    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        struct Node *temp = friendLists[i];

        while (temp != NULL)
        {
            if (temp->item.itemId == id)
            {
                printf("Enter New Item Name: ");
                scanf(" %[^\n]s", temp->item.itemName);

                printf("Enter New Brand: ");
                scanf("%s", temp->item.brand);

                printf("Enter New Quantity: ");
                scanf("%d", &temp->item.quantity);

                printf("Enter New Price: ");
                scanf("%f", &temp->item.price);

                printf("Item updated successfully for %s!\n", FRIEND_NAMES[i]);
                return;
            }
            temp = temp->next;
        }
    }

    printf("Item ID %d not found in any shopping list.\n", id);
}

// 4. Search Item across the array of linked lists
void searchItem()
{
    int id;
    printf("Enter Item ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        struct Node *temp = friendLists[i];

        while (temp != NULL)
        {
            if (temp->item.itemId == id)
            {
                printf("\n--- Item Details ---\n");
                printf("ID:       %d\n", temp->item.itemId);
                printf("Friend:   %s (List Index: %d)\n", temp->item.friendName, i);
                printf("Item:     %s\n", temp->item.itemName);
                printf("Brand:    %s\n", temp->item.brand);
                printf("Quantity: %d\n", temp->item.quantity);
                printf("Price:    Rs. %.2f\n", temp->item.price);
                printf("Total:    Rs. %.2f\n", temp->item.quantity * temp->item.price);
                return;
            }
            temp = temp->next;
        }
    }

    printf("Item ID %d not found.\n", id);
}

// 5. Display All Lists grouped by array index
void displayItems()
{
    int totalItems = 0;

    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        printf("\n========================================================================\n");
        printf("Bucket [%d] - Shopping List for: %s\n", i, FRIEND_NAMES[i]);
        printf("------------------------------------------------------------------------\n");

        struct Node *temp = friendLists[i];
        if (temp == NULL)
        {
            printf("  (No items in this list)\n");
            continue;
        }

        printf("%-6s %-25s %-12s %-6s %-10s\n", "ID", "Item", "Brand", "Qty", "Price");
        printf("------------------------------------------------------------------------\n");

        while (temp != NULL)
        {
            printf("%-6d %-25s %-12s %-6d Rs. %-8.2f\n",
                   temp->item.itemId,
                   temp->item.itemName,
                   temp->item.brand,
                   temp->item.quantity,
                   temp->item.price);
            temp = temp->next;
            totalItems++;
        }
    }

    if (totalItems == 0)
    {
        printf("\nAll shopping lists are currently empty.\n");
    }
}

// 6. Final Consolidated Billing with 30% Festival Discount
void generateBill()
{
    float subTotal = 0.0f;
    int itemCount = 0;

    printf("\n================ CONSOLIDATED BILLING SUMMARY ================\n");
    printf("%-10s %-25s %-6s %-12s %-12s\n", "Friend", "Item Name", "Qty", "Unit Price", "Total Cost");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < TOTAL_FRIENDS; i++)
    {
        struct Node *temp = friendLists[i];

        while (temp != NULL)
        {
            float cost = temp->item.quantity * temp->item.price;
            subTotal += cost;
            itemCount++;

            printf("%-10s %-25s %-6d Rs. %-9.2f Rs. %-9.2f\n",
                   temp->item.friendName,
                   temp->item.itemName,
                   temp->item.quantity,
                   temp->item.price,
                   cost);

            temp = temp->next;
        }
    }

    if (itemCount == 0)
    {
        printf("No items available to generate bill.\n");
        return;
    }

    float festivalDiscount = subTotal * 0.30f;
    float finalPayable = subTotal - festivalDiscount;

    printf("--------------------------------------------------------------\n");
    printf("Sub-Total:                                             Rs. %.2f\n", subTotal);
    printf("Festival Bonanza Discount (30%%):                      -Rs. %.2f\n", festivalDiscount);
    printf("Total Amount to Pay:                                   Rs. %.2f\n", finalPayable);
    printf("==============================================================\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Galaxy Mega Mall - Festival Shopping (Linked List Array) =====\n");
        printf("1. Add Item to Shopping List\n");
        printf("2. Cancel / Remove Item\n");
        printf("3. Update / Replace Item\n");
        printf("4. Search Item\n");
        printf("5. Display All Lists (By Friend)\n");
        printf("6. Generate Consolidated Bill & Apply Discount\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            break;
        }

        switch (choice)
        {
            case 1:
                insertItem();
                break;
            case 2:
                deleteItem();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                searchItem();
                break;
            case 5:
                displayItems();
                break;
            case 6:
                generateBill();
                break;
            case 7:
                printf("Shopping completed. Exiting system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}