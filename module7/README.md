# Cloud Services Billing System

## Problem Statement

Cloud service providers need a way to track customer resource usage and calculate bills accurately. This program manages customer accounts, records CPU, memory, storage, and network usage, and generates invoices based on usage rates.

## Design and Architecture Details

The project is written in C and uses the GNU Database Manager (GDBM) to store customer accounts persistently.

### Files

- `main.c`: Provides the menu and handles user input.
- `billing.c` and `billing.h`: Calculate service costs and display invoices.
- `database.c` and `database.h`: Implement database operations.
- `Makefile`: Compiles the program and links the GDBM and math libraries.

### Database and CRUD Operations

Each account stores an ID, customer name, service plan, CPU hours, memory GB-hours, storage GB, inbound traffic MB, and outbound traffic MB.

The program supports:
- Create: Add a customer account with a unique ID.
- Read: Retrieve an account and display its invoice.
- Update: Modify usage values for an existing account.
- Delete: Remove an account.
- List: Display all stored accounts.

GDBM stores each account using its ID as the database key. The database file is named `billing.db`, allowing records to persist after the program exits.

### Billing Rules

The program uses the following example rates:

| Service | Rate |
|---|---:|
| CPU usage | $0.05 per CPU-hour |
| Memory usage | $0.02 per GB-hour |
| Storage | $0.10 per whole GB |
| Outbound network traffic | $0.01 per MB |
| Inbound network traffic | Free |

Storage usage is rounded down to a whole number of GB before billing. Inbound network traffic is not charged. These rates are illustrative project values, not actual provider prices.

### Build and Run

Requirements: GCC, Make, and the GDBM development library.

Compile the program:

    make

Run the program:

    ./billing

Remove compiled files:

    make clean

## Pros and Cons of Your Solution

### Pros

- GDBM provides persistent storage between program runs.
- CRUD operations allow customer records to be managed.
- Billing is separated from database and menu logic.
- The invoice shows itemized costs and the total due.
- The Makefile simplifies compilation.

### Cons

- The program uses a terminal menu rather than a graphical interface.
- It does not include authentication or role-based access control.
- Billing rates are fixed in the source code.
- Usage data is entered manually rather than collected from real cloud services.
- The system does not support multiple currencies or payment processing.

## Demo Video

Add a publicly viewable demo video link here after recording a demonstration of at least five minutes.

## GitHub Repository

https://github.com/phoms005/inet3101-c-programming
