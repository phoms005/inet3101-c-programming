#include "database.h"
#include "billing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DB_FILE "billing.db"

static void clear_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static int read_int(const char *prompt, int *value) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        clear_input();
        printf("Invalid number.\n");
        return 0;
    }
    clear_input();
    return 1;
}

static int read_double(const char *prompt, double *value) {
    printf("%s", prompt);
    if (scanf("%lf", value) != 1) {
        clear_input();
        printf("Invalid number.\n");
        return 0;
    }
    clear_input();

    if (*value < 0) {
        printf("Usage cannot be negative.\n");
        return 0;
    }
    return 1;
}

static int read_text(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        printf("This field cannot be empty.\n");
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && strlen(buffer) == size - 1) {
        clear_input();
    }

    return 1;
}

static void add_account(void) {
    Account account = {0};

    if (!read_int("Account ID: ", &account.id) || account.id <= 0) {
        printf("Account ID must be a positive integer.\n");
        return;
    }

    if (!read_text("Customer name: ", account.name, sizeof(account.name)) ||
        !read_text("Plan (Basic/Pro/Enterprise): ",
                   account.plan, sizeof(account.plan)))
        return;

    if (!read_double("CPU hours: ", &account.cpu_hours) ||
        !read_double("Memory GB-hours: ", &account.memory_gb_hours) ||
        !read_double("Storage GB: ", &account.storage_gb) ||
        !read_double("Inbound traffic MB: ", &account.inbound_mb) ||
        !read_double("Outbound traffic MB: ", &account.outbound_mb))
        return;

    if (db_add(&account))
        printf("Account added successfully.\n");
    else
        printf("Could not add account. The ID may already exist.\n");
}

static void view_account(void) {
    int id;
    Account account;

    if (!read_int("Account ID to view: ", &id))
        return;

    if (db_get(id, &account))
        display_invoice(&account);
    else
        printf("Account not found.\n");
}

static void update_account(void) {
    int id;
    Account account;

    if (!read_int("Account ID to update: ", &id))
        return;

    if (!db_get(id, &account)) {
        printf("Account not found.\n");
        return;
    }

    printf("Updating usage for %s (ID %d).\n", account.name, account.id);

    if (!read_double("New CPU hours: ", &account.cpu_hours) ||
        !read_double("New memory GB-hours: ", &account.memory_gb_hours) ||
        !read_double("New storage GB: ", &account.storage_gb) ||
        !read_double("New inbound traffic MB: ", &account.inbound_mb) ||
        !read_double("New outbound traffic MB: ", &account.outbound_mb))
        return;

    if (db_update(&account))
        printf("Account updated successfully.\n");
    else
        printf("Account update failed.\n");
}

static void delete_account(void) {
    int id;

    if (!read_int("Account ID to delete: ", &id))
        return;

    if (db_delete(id))
        printf("Account deleted successfully.\n");
    else
        printf("Account not found or could not be deleted.\n");
}

int main(void) {
    int choice;

    if (!db_open(DB_FILE)) {
        fprintf(stderr, "Could not open billing database.\n");
        return 1;
    }

    do {
        printf("\n====== CLOUD SERVICES BILLING ======\n");
        printf("1. Add customer account\n");
        printf("2. View account and invoice\n");
        printf("3. Update account usage\n");
        printf("4. Delete customer account\n");
        printf("5. List all accounts\n");
        printf("6. Exit\n");

        if (!read_int("Choose an option: ", &choice))
            continue;

        switch (choice) {
            case 1:
                add_account();
                break;
            case 2:
                view_account();
                break;
            case 3:
                update_account();
                break;
            case 4:
                delete_account();
                break;
            case 5:
                printf("\nAccounts in database: %d\n", db_list());
                break;
            case 6:
                printf("Exiting billing system.\n");
                break;
            default:
                printf("Invalid option. Choose 1-6.\n");
        }
    } while (choice != 6);

    db_close();
    return 0;
}
