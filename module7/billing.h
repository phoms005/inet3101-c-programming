#ifndef BILLING_H
#define BILLING_H

#include "database.h"

double calculate_server_cost(const Account *account);
double calculate_storage_cost(const Account *account);
double calculate_network_cost(const Account *account);
double calculate_total_cost(const Account *account);
void display_invoice(const Account *account);

#endif
