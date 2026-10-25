#ifndef DATABASE_H
#define DATABASE_H

#include <gdbm.h>

#define NAME_LEN 100
#define PLAN_LEN 30

typedef struct {
    int id;
    char name[NAME_LEN];
    char plan[PLAN_LEN];
    double cpu_hours;
    double memory_gb_hours;
    double storage_gb;
    double inbound_mb;
    double outbound_mb;
} Account;

int db_open(const char *filename);
void db_close(void);
int db_add(Account *account);
int db_get(int id, Account *account);
int db_update(Account *account);
int db_delete(int id);
int db_list(void);

#endif
