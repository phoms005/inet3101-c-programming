#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GDBM_FILE db = NULL;

int db_open(const char *filename) {
    db = gdbm_open((char *)filename, 0, GDBM_WRCREAT, 0644, NULL);

    if (db == NULL) {
        fprintf(stderr, "Database error: %s\n", gdbm_strerror(gdbm_errno));
        return 0;
    }

    return 1;
}

void db_close(void) {
    if (db != NULL) {
        gdbm_close(db);
        db = NULL;
    }
}

int db_add(Account *account) {
    datum key, value;

    key.dptr = (char *)&account->id;
    key.dsize = sizeof(account->id);
    value.dptr = (char *)account;
    value.dsize = sizeof(Account);

    return gdbm_store(db, key, value, GDBM_INSERT) == 0;
}

int db_get(int id, Account *account) {
    datum key, value;

    key.dptr = (char *)&id;
    key.dsize = sizeof(id);
    value = gdbm_fetch(db, key);

    if (value.dptr == NULL)
        return 0;

    if (value.dsize != sizeof(Account)) {
        free(value.dptr);
        return 0;
    }

    memcpy(account, value.dptr, sizeof(Account));
    free(value.dptr);
    return 1;
}

int db_update(Account *account) {
    datum key, value;

    key.dptr = (char *)&account->id;
    key.dsize = sizeof(account->id);
    value.dptr = (char *)account;
    value.dsize = sizeof(Account);

    return gdbm_store(db, key, value, GDBM_REPLACE) == 0;
}

int db_delete(int id) {
    datum key;

    key.dptr = (char *)&id;
    key.dsize = sizeof(id);

    return gdbm_delete(db, key) == 0;
}

int db_list(void) {
    datum key = gdbm_firstkey(db);
    int count = 0;

    while (key.dptr != NULL) {
        datum value = gdbm_fetch(db, key);

        if (value.dptr != NULL) {
            if (value.dsize == sizeof(Account)) {
                Account account;
                memcpy(&account, value.dptr, sizeof(Account));

                printf("ID: %d | Name: %s | Plan: %s\n",
                       account.id, account.name, account.plan);
                count++;
            }
            free(value.dptr);
        }

        datum next = gdbm_nextkey(db, key);
        free(key.dptr);
        key = next;
    }

    return count;
}
