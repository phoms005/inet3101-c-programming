#include "billing.h"
#include <stdio.h>
#include <math.h>

#define CPU_RATE             0.05
#define MEMORY_RATE          0.02
#define STORAGE_RATE         0.10
#define OUTBOUND_NETWORK_RATE 0.01

double calculate_server_cost(const Account *account) {
    return (account->cpu_hours * CPU_RATE) +
           (account->memory_gb_hours * MEMORY_RATE);
}

double calculate_storage_cost(const Account *account) {
    /* Bill only whole GB, rounding down as specified. */
    return floor(account->storage_gb) * STORAGE_RATE;
}

double calculate_network_cost(const Account *account) {
    /* Inbound traffic is free; only outbound traffic is billed. */
    return account->outbound_mb * OUTBOUND_NETWORK_RATE;
}

double calculate_total_cost(const Account *account) {
    return calculate_server_cost(account) +
           calculate_storage_cost(account) +
           calculate_network_cost(account);
}

void display_invoice(const Account *account) {
    printf("\n========== CLOUD SERVICES INVOICE ==========\n");
    printf("Account ID:       %d\n", account->id);
    printf("Customer:         %s\n", account->name);
    printf("Plan:             %s\n", account->plan);
    printf("--------------------------------------------\n");
    printf("CPU usage:        %.2f hours\n", account->cpu_hours);
    printf("Memory usage:     %.2f GB-hours\n", account->memory_gb_hours);
    printf("Storage usage:    %.2f GB (billed: %.0f GB)\n",
           account->storage_gb, floor(account->storage_gb));
    printf("Inbound traffic:  %.2f MB (free)\n", account->inbound_mb);
    printf("Outbound traffic: %.2f MB\n", account->outbound_mb);
    printf("--------------------------------------------\n");
    printf("Server cost:      $%.2f\n", calculate_server_cost(account));
    printf("Storage cost:     $%.2f\n", calculate_storage_cost(account));
    printf("Network cost:     $%.2f\n", calculate_network_cost(account));
    printf("TOTAL DUE:        $%.2f\n", calculate_total_cost(account));
    printf("============================================\n");
}
