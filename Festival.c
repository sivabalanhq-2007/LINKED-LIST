#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct Node *head = NULL;

// 1. Add / Insert Item (Handles additions like Priya's silk shawl)
void insertItem()
{
    struct Node *newNode, *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter Item ID: ");
    scanf("%d", &newNode->item.itemId);

    printf("Enter Friend Name (Arjun/Priya/Kavin/Meena/Sanjay): ");
    scanf("%s", newNode->item.friendName);

    printf("Enter Item Name: ");
    scanf(" %[^\n]s", newNode->item.itemName);

    printf("Enter Brand: ");
    scanf("%s", newNode->item.brand);

    printf("Enter Quantity: ");
    scanf("%d", &newNode->item.quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &newNode->item.price);

    newNode->next = NULL;

    // First node
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        // Traverse to the last node
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("Item added to shopping list successfully!\n");
}

// 2. Delete / Cancel Item (e.g., Arjun cancelling Wrist Watch)
void deleteItem()
{
    struct Node *temp = head;
    struct Node *prev = NULL;
    int id;

    printf("Enter Item ID to remove/cancel: ");
    scanf("%d", &id);

    while (temp != NULL && temp->item.itemId != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Item ID not found.\n");
        return;
    }

    // Deleting head node
    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    free(temp);
    printf("Item cancelled/removed successfully!\n");
}

// 3. Update / Replace Item (e.g., Kavin replacing Speaker or Sanjay choosing alternative TV)
void updateItem()
{
    struct Node *temp = head;
    int id;

    printf("Enter Item ID to update/replace: ");
    scanf("%d", &id);

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

            printf("Item updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Item ID not found.\n");
}

// 4. Search Item
void searchItem()
{
    struct Node *temp = head;
    int id;

    printf("Enter Item ID to search: ");
    scanf("%d", &id);

    while (temp != NULL)
    {
        if (temp->item.itemId == id)
        {
            printf("\n--- Item Details ---\n");
            printf("ID: %d\n", temp->item.itemId);
            printf("Friend: %s\n", temp->item.friendName);
            printf("Item: %s\n", temp->item.itemName);
            printf("Brand: %s\n", temp->item.brand);
            printf("Quantity: %d\n", temp->item.quantity);
            printf("Price: Rs. %.2f\n", temp->item.price);
            printf("Total: Rs. %.2f\n", temp->item.quantity * temp->item.price);
            return;
        }
        temp = temp->next;
    }

    printf("Item not found.\n");
}

// 5. Display All Items in Shopping List
void displayItems()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("Shopping list is empty.\n");
        return;
    }

    printf("\n%-6s %-10s %-25s %-12s %-6s %-10s\n", "ID", "Friend", "Item", "Brand", "Qty", "Price");
    printf("------------------------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-6d %-10s %-25s %-12s %-6d Rs. %-8.2f\n",
               temp->item.itemId,
               temp->item.friendName,
               temp->item.itemName,
               temp->item.brand,
               temp->item.quantity,
               temp->item.price);

        temp = temp->next;
    }
}

// 6. Deduplication & Final Billing with 30% Festival Discount
void generateBill()
{
    struct Node *temp = head;
    float subTotal = 0.0f;
    float festivalDiscount, finalPayable;

    if (head == NULL)
    {
        printf("No items to bill.\n");
        return;
    }

    printf("\n================ BILLING SUMMARY ================\n");
    printf("%-25s %-8s %-12s %-12s\n", "Item Name", "Qty", "Unit Price", "Total Cost");
    printf("-------------------------------------------------\n");

    while (temp != NULL)
    {
        float cost = temp->item.quantity * temp->item.price;
        subTotal += cost;

        printf("%-25s %-8d Rs. %-9.2f Rs. %-9.2f\n",
               temp->item.itemName,
               temp->item.quantity,
               temp->item.price,
               cost);

        temp = temp->next;
    }

    // 30% Festival Shopping Bonanza coupon calculation
    festivalDiscount = subTotal * 0.30f;
    finalPayable = subTotal - festivalDiscount;

    printf("-------------------------------------------------\n");
    printf("Sub-Total:                             Rs. %.2f\n", subTotal);
    printf("Festival Bonanza Discount (30%%):      -Rs. %.2f\n", festivalDiscount);
    printf("Total Amount to Pay:                   Rs. %.2f\n", finalPayable);
    printf("=================================================\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Galaxy Mega Mall - Festival Shopping =====\n");
        printf("1. Add Item to Shopping List\n");
        printf("2. Cancel / Remove Item\n");
        printf("3. Update / Replace Item\n");
        printf("4. Search Item\n");
        printf("5. Display Shopping List\n");
        printf("6. Generate Consolidated Bill & Apply Discount\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

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