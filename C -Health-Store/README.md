# Medical Storage Management System

![Healthcare Management](https://img.shields.io/badge/domain-healthcare-informational) 
![C Program](https://img.shields.io/badge/language-C-blue) 
![CLI Application](https://img.shields.io/badge/interface-CLI-success)

## Overview

A comprehensive C program for managing medical inventory, suppliers, and medicines in healthcare facilities. This system provides complete CRUD (Create, Read, Update, Delete) functionality for both suppliers and medicines, with relational tracking between them.

## Features

- **Supplier Management**:
  - Add new medical suppliers
  - View all suppliers
  - Search suppliers by ID
  - Update supplier details
  - Delete supplier records

- **Medicine Management**:
  - Add new medicines with supplier association
  - View complete medicine inventory
  - Search medicines by ID
  - Update medicine details (quantity, price, expiry)
  - Remove medicines from inventory

- **Data Relationships**:
  - Link medicines to their suppliers
  - Validate supplier existence before medicine addition
  - Display supplier information with related medicines

## Technical Specifications

### Data Structures
```c
typedef struct {
    int id;
    char name[NAME_LENGTH];
    char contact[15];
    char address[100];
} Supplier;

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int supplierId;
    int quantity;
    float price;
    char expiryDate[11];  // YYYY-MM-DD format
} Medicine;
```
## System Limits
- Maximum suppliers: 50

- Maximum medicines: 100

- Name field length: 50 characters

- Expiry date format: YYYY-MM-DD
## Installation & Usage  
- Requirements
   - GCC compiler

   - Standard C libraries (stdio.h, string.h, stdlib.h, ctype.h)
