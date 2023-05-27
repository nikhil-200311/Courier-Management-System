#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Courier {
    char sender_name[MAX_SIZE];
    char receiver_name[MAX_SIZE];
    char tracking_id[MAX_SIZE];
    char sender_phone[MAX_SIZE];
    char receiver_phone[MAX_SIZE];
    float weight;
    float cost;
};

void write_to_file(struct Courier* couriers, int n) {
    FILE* fp;
    fp = fopen("couriers.txt", "w");
    fprintf(fp, "%-20s%-20s%-20s%-20s%-20s%-10s%-10s\n", "Sender Name", "Receiver Name", "Tracking ID", "Sender Phone", "Receiver Phone", "Weight", "Cost");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%-20s%-20s%-20s%-20s%-20s%-10.2f%-10.2f\n", couriers[i].sender_name, couriers[i].receiver_name, couriers[i].tracking_id, couriers[i].sender_phone, couriers[i].receiver_phone, couriers[i].weight, couriers[i].cost);
    }
    fclose(fp);
}

void insert_courier(struct Courier* couriers, int* n) {
    printf("Enter the sender name: ");
    scanf("%s", couriers[*n].sender_name);
    printf("Enter the receiver name: ");
    scanf("%s", couriers[*n].receiver_name);
    printf("Enter the tracking ID: ");
    scanf("%s", couriers[*n].tracking_id);
    printf("Enter the sender phone number: ");
    scanf("%s", couriers[*n].sender_phone);
    printf("Enter the receiver phone number: ");
    scanf("%s", couriers[*n].receiver_phone);
    printf("Enter the weight (kg): ");
    scanf("%f", &couriers[*n].weight);
    printf("Enter the cost: ");
    scanf("%f", &couriers[*n].cost);
    (*n)++;
}

void display_couriers(struct Courier* couriers, int n) {
    printf("%-20s%-20s%-20s%-20s%-20s%-10s%-10s\n", "Sender Name", "Receiver Name", "Tracking ID", "Sender Phone", "Receiver Phone", "Weight", "Cost");
    for (int i = 0; i < n; i++) {
        printf("%-20s%-20s%-20s%-20s%-20s%-10.2f%-10.2f\n", couriers[i].sender_name, couriers[i].receiver_name, couriers[i].tracking_id, couriers[i].sender_phone, couriers[i].receiver_phone, couriers[i].weight, couriers[i].cost);
    }
}

void search_courier(struct Courier* couriers, int n) {
    char tracking_id[MAX_SIZE];
    printf("Enter the tracking ID to search: ");
    scanf("%s", tracking_id);
    for (int i = 0; i < n; i++) {
        if (strcmp(couriers[i].tracking_id, tracking_id) == 0) {
            printf("%-20s%-20s%-20s%-20s%-20s%-10s%-10s\n", "Sender Name", "Receiver Name", "Tracking ID", "Sender Phone", "Receiver Phone", "Weight", "Cost");
            printf("%-20s%-20s%-20s%-20s%-20s%-10.2f%-10.2f\n", couriers[i].sender_name, couriers[i].receiver_name, couriers[i].tracking_id, couriers[i].sender_phone, couriers[i].receiver_phone, couriers[i].weight, couriers[i].cost);
            return;
        }
    }
    printf("No courier found with the given tracking ID.\n");
}

void delete_courier(struct Courier* couriers, int* n) {
    char tracking_id[MAX_SIZE];
    printf("Enter the tracking ID to delete: ");
    scanf("%s", tracking_id);
    for (int i = 0; i < *n; i++) {
        if (strcmp(couriers[i].tracking_id, tracking_id) == 0) {
            for (int j = i; j < *n - 1; j++) {
                couriers[j] = couriers[j+1];
            }
            (*n)--;
            write_to_file(couriers, *n);
            printf("Courier with tracking ID %s is deleted.\n", tracking_id);
            return;
        }
    }
    printf("No courier found with the given tracking ID.\n");
}

void update_courier(struct Courier* couriers, int n) {
    char tracking_id[MAX_SIZE];
    printf("Enter the tracking ID to update: ");
    scanf("%s", tracking_id);
    for (int i = 0; i < n; i++) {
    if (strcmp(couriers[i].tracking_id, tracking_id) == 0) {
        printf("Enter the updated sender name: ");
        scanf("%s", couriers[i].sender_name);
        printf("Enter the updated receiver name: ");
        scanf("%s", couriers[i].receiver_name);
        printf("Enter the updated sender phone number: ");
        scanf("%s", couriers[i].sender_phone);
        printf("Enter the updated receiver phone number: ");
        scanf("%s", couriers[i].receiver_phone);
        printf("Enter the updated weight (kg): ");
        scanf("%f", &couriers[i].weight);
        printf("Enter the updated cost: ");
        scanf("%f", &couriers[i].cost);
        write_to_file(couriers, n);
        printf("Courier information is updated.\n");
        return;
    }
    }
    printf("No courier found with the given tracking ID.\n");
}

void sort_couriers(struct Courier* couriers, int n) {
    // Bubble sort based on tracking id
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(couriers[j].tracking_id, couriers[j+1].tracking_id) > 0) {
                struct Courier temp = couriers[j];
                couriers[j] = couriers[j+1];
                couriers[j+1] = temp;
        }
    }
    }
    printf("Couriers are sorted based on tracking ID.\n");
}

int main() {
    int n = 0;
    struct Courier couriers[MAX_SIZE];

    FILE* fp;
    fp = fopen("couriers.txt", "r");
    if (fp != NULL) {
        char header[MAX_SIZE];
        fscanf(fp, "%s", header); // read the header line
        while (!feof(fp)) {
            fscanf(fp, "%s %s %s %s %s %f %f\n", couriers[n].sender_name, couriers[n].receiver_name, couriers[n].tracking_id, couriers[n].sender_phone, couriers[n].receiver_phone, &couriers[n].weight, &couriers[n].cost);
            n++;
        }
        fclose(fp);
    }

    int choice;
    do {
        printf("\nCourier Management System\n");
        printf("1. Insert courier\n");
        printf("2. Display all couriers\n");
        printf("3. Search courier\n");
        printf("4. Delete courier\n");
        printf("5. Update courier\n");
        printf("6. Sort couriers\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insert_courier(couriers, &n);
                write_to_file(couriers, n);
                break;
            case 2:
                display_couriers(couriers, n);
                break;
            case 3:
                search_courier(couriers, n);
                break;
            case 4:
                delete_courier(couriers, &n);
                break;
            case 5:
                update_courier(couriers, n);
                break;
            case 6:
                sort_couriers(couriers, n);
                write_to_file(couriers, n);
                break;
            case 7:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}


