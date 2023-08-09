# Billing System v1.0

This is a billing system application developed in C, designed to facilitate effortless transactions and inventory management. The application allows users to perform various tasks such as creating sales bills, adding inventory items, managing stocks, and checking inventory details. The data in saved into data file inside another folder such that the data is saved even after termination of program.

There is a pre_data_pack folder containing a inventory.data file which consists of list of items in inventory which can we moved in data_files folder for operation.

## Contributors

- Rohan Shrestha, BCT-A2 (ACE079BCT048)

## Features

- User authentication and login functionality.
- Sales bill creation with product details, quantities, and total prices.
- Adding new inventory items with product details.
- Managing stocks by editing properties of existing inventory items.
- Viewing available inventory items and their details.

## Getting Started

1. Clone this repository to your local machine.
2. Compile the source code using a C compiler (e.g., GCC).
3. Run the compiled executable to launch the billing system.

```bash
gcc billing_system.c -o billing_system.exe
billing_system.exe
```

## Usage

1. Upon launching the application, follow the on-screen instructions to log in or create a new user account.
2. Once logged in, select from the available options using the numeric keys (1 to 5) to navigate through the application's functions.
3. Create sales bills, add new inventory items, manage existing inventory stocks, and view inventory details.
4. Follow the prompts and enter required details as prompted for each action.

## Dependencies

- Windows OS
- C compiler (e.g., GCC)