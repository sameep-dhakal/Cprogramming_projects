#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 *This function displays the available application functions.
*/
void showAppFunctions();

/**
 *This struct represents user credentials with a name and password.
*/
struct creds{
    char name[20];
    char pass[20];
};

/**
 *This struct represents a product with its name, rate, product ID, and available stock.
*/
struct product{
    char name[30];
    float rate;
    long int productId;
    int inStock;
};

/**
 * This struct represents a product bill item that includes a product, quantity, and total price.
 * The billItem represents another structure consisting name, rate, product ID, and available stock.
*/
struct productBill{
    struct product billItem;
    int quantity;
    float totalPrice;
};


/**
 * Get the file path of the current module.
 *
 * @return A dynamically allocated character pointer holding the file path. The caller is responsible for freeing the memory.
*/
char* getFilePath(){
    char* filePath = (char*)malloc(MAX_PATH * sizeof(char));
    GetModuleFileName(NULL, filePath, MAX_PATH);

    // Extract the directory path
    char *lastBackslash = strrchr(filePath, '\\');
    if (lastBackslash != NULL) {
        *lastBackslash = '\0'; // making it a string
    }

    return filePath;
}

/**
 *Get the path to the data files directory.
 *
 * @return A dynamically allocated character pointer holding the data files directory path.
*/
char* getDataFilesPath(){
    char* filePath = getFilePath();
    char* directoryPath = strcat(filePath,"\\data_files");
    mkdir(directoryPath);
    return directoryPath;
}

/**
 * Perform pre-data file creation tasks.
 * This function creates empty binary files for credentials, inventory, and bills.
 * If the files already exist, this function will not modify their contents except for bill.dat.
*/
void preDataFileCreation(){
    FILE *credentials, *inventory, *bill;
    credentials = fopen(strcat(getDataFilesPath(),"\\credentials.dat"), "ab");
    inventory = fopen(strcat(getDataFilesPath(),"\\inventory.dat"),"ab");

    bill = fopen(strcat(getDataFilesPath(),"\\bill.dat"),"wb");

    fclose(credentials);
    fclose(inventory);
    fclose(bill);
}

/**
 * Print the loading circle animation to indicate progress.
 * The animation consists of a rotating circle with four frames: '|', '/', '-', '\'.
 * The function takes an integer frame number as input and prints the corresponding frame.
 * The carriage return (\r) is used to overwrite the previous frame and display the current frame in the same line.
 *
 * @param frame The frame number to display. It should be in the range [0, numFrames - 1].
 * If the frame number is out of range, the animation will loop.

*/
void printLoadingCircle(int frame) {
    // Character set for the loading circle animation
    char circleChars[] = {'|', '/', '-', '\\'};
    int numFrames = sizeof(circleChars) / sizeof(circleChars[0]);

    int index = frame % numFrames;

    printf("\r%c Loading... ", circleChars[index]);
    fflush(stdout);
}

/**
 *Display a text animation by printing characters with a small delay between each character.
 * The function takes a character pointer (string) as input and prints the characters one by one with a short delay.
 * This creates a text animation effect.
 *
 * @param str The input string to be animated.
*/
void textAnimation(char* str){
    int i=0;

    while(str[i] != '\0'){
        printf("%c",str[i]);
        i++;
        Sleep(10);
    }
}

/**
 * Display a message to prompt the user to press any key to continue.
 * The method waits for the user to press any key and then proceeds to display the application functions menu.
*/
void holdScreen(){
    textAnimation("\nPress any key to continue to options...\n");
    getch();
    showAppFunctions();
}

/**
 * Display a loading circle animation to indicate progress.
 * The animation consists of a rotating circle with four frames: '|', '/', '-', '\'.
 * The animation will loop until it reaches a total of 50 frames.
*/
void LoadingAnimation(){
    int frame = 0;
    int i;
    while (1) {
        printLoadingCircle(frame);
        Sleep(100); // Adjust the delay to control the animation speed
        frame++;
        if(frame == 30) break;
    }

    // creates an clear screen effect
    for(i=0;i<25;i++){
        printf("\n");
    }
}

/**
 * Display a welcome message for the users with a text animation effect.
 * The function animates the welcome message and then slides up the text.
*/
void welcomeMessage(){
    char welcomeString[] = "Welcome to the our Billing System v1.0. \nAll rights reserved. 2023 Rohan Shrestha Billing System. \nUnauthorized duplication or distribution is prohibited. \n\nThank you for choosing our system.";
    int j=0;
    // individual charac print display
    textAnimation(welcomeString);

    // slide up animation
    while(j<30){
        printf("\n");
        Sleep(50);
        j++;
    }
}

/**
 * Sign in an existing user or create a new user account.
 * The function prompts the user to enter their username and password.
 * If the user already exists and the password matches, they are signed in.
 * If the user does not exist, a new account is created.
 *
 * @return 1 if the user is signed in or a new account is created successfully, 0 otherwise.
*/
int signInUser(){
    struct creds user;
    char* filePath = strcat(getDataFilesPath(), "\\credentials.dat");
    struct creds temp;
    int found = 0;

    textAnimation("\nEffortless Billing, Seamless Transactions.\n");

    printf("\nLOG IN\n");
    printf("Username: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0'; // Remove trailing newline character

    printf("Password: ");
    fgets(user.pass, sizeof(user.pass), stdin);
    user.pass[strcspn(user.pass, "\n")] = '\0'; // Remove trailing newline character

    // checking if user exists
    FILE *credentials;
    credentials = fopen(filePath, "ab+");
    if (credentials == NULL) {
        fprintf(stderr, "\nError opening file.\n\n");
        exit(-1);
    }

    while (fread(&temp, sizeof(temp), 1, credentials) == 1) {
        if (strcmp(temp.name, user.name) == 0) {
            found = 1;
            break;
        }
    }

    // if exists and password matches give access
    if (found) {
        if(strcmp(temp.pass, user.pass)==0){
            printf("Welcome back, %s!\n", user.name);
            fclose(credentials);
            return 1;
        }else{
            printf("\nIncorrect password for existing account! Please try again or create a new one.");
            fclose(credentials);
            return 0;
        }
    } else {
        fwrite(&user, sizeof(user), 1, credentials);
        printf("%s has been added to the database successfully.\nLog in Again\n", user.name);
        fclose(credentials);
        return 0;
    }
}

/**
 * Retrieve product details from a file based on the product ID and update the productBill pointer.
 *
 * @param path The file path where the product details are stored.
 * @param bill A pointer to the productBill struct that needs to be updated with the retrieved details.
 *
 * @return 1 if the product details are successfully retrieved and updated, 0 otherwise.
*/
int retrieveItemDetails(char path[],struct productBill *bill){
    FILE *file;
    file = fopen(path, "r+b");
    struct product tempBill;

    while (fread(&tempBill, sizeof(tempBill), 1, file) == 1) {// reading file
        if(tempBill.productId == bill->billItem.productId){// finding specific product
            bill->billItem = tempBill;

            if(bill->quantity>tempBill.inStock || bill->quantity<1){
                printf("Insufficient Stock. In stock: %d\n", tempBill.inStock);
                rewind(file);
                return 0;
            }

            tempBill.inStock -= bill->quantity;// managing the stock in file
            fseek(file, -sizeof(tempBill), SEEK_CUR);// finding file position
            fwrite(&tempBill, sizeof(tempBill), 1, file);// writing in same postion
            rewind(file);
            return 1;
        }
    }
}

/**
 * Print the items in a bill along with the final total price.
 *
 * @param file The file pointer to the file containing productBill records.
*/
void printBillItems(FILE *file) {
    int serialNumber = 1;
    float finalPrice = 0;
    struct productBill bill;

    printf("\n%-4s%-30s%-10s%-15s%-8s\n", "S.N.", "Name", "Rate", "Quantity", "Price");
    printf("---------------------------------------------------------------\n");

    while (fread(&bill, sizeof(bill), 1, file) == 1) {
        printf("%-4d%-30s%-10.2f%-15d%-8.2f\n", serialNumber, bill.billItem.name, bill.billItem.rate, bill.quantity, bill.totalPrice);
        serialNumber++;
        finalPrice += bill.totalPrice;
    }

    printf("---------------------------------------------------------------\n");
    printf("%-59s%.2f\n", "TOTAL PRICE:", finalPrice);
    printf("\n");
    textAnimation("Thank You For Choosing Us\nAll items are unrefundable.");
}

/**
 * Check if a given product ID exists in the file.
 *
 * @param file The file pointer to the file containing product details.
 * @param productID The product ID to check for existence.
 *
 * @return 1 if the product ID does not exist in the file, 0 if it already exists.
 */
int checkProductIdExists(FILE *file,long int productID){
    struct product newProduct;
    while(fread(&newProduct,sizeof(newProduct),1,file)==1){
        if(newProduct.productId == productID){
            rewind(file);
            return 0;
        };
    }
    rewind(file);
    return 1;
}

/**
 * Record and print the sales bill for the purchased products.
 *
 */
void salesBill() {
    struct productBill bill;
    char* filePathInventory = strcat(getDataFilesPath(), "\\inventory.dat");
    char* filePathBill = strcat(getDataFilesPath(), "\\bill.dat");
    char ch;
    FILE* inventory, * receipt;

    inventory = fopen(filePathInventory, "a+b");
    receipt = fopen(filePathBill, "w+b");

    if (inventory == NULL) {
        perror("Error opening file.");
        exit(-1); // terminate program with error code -1
    }

    textAnimation("\nProvide the following details for the product bill");

    do {
        while (1) { // accepts product id which exists in file
            printf("\nProduct ID: ");
            scanf("%ld", &bill.billItem.productId);
            if (checkProductIdExists(inventory, bill.billItem.productId) == 0) break;
            else {
                printf("\nProduct Doesn't Exist. Enter a valid Product ID!");
            }
        }

        printf("Enter quantity: ");
        scanf("%d", &bill.quantity);

        // Retrieve item details and check if the product exists before calculating the total price
        if (retrieveItemDetails(filePathInventory,&bill)) {
            bill.totalPrice = bill.quantity * bill.billItem.rate;
            fwrite(&bill, sizeof(bill), 1, receipt);
        } else {
            printf("Error: Unable to retrieve item details. Please try again.\n");
        }

        printf("Add more items (y/n): ");
        ch = getche();
    } while (ch == 'y' || ch == 'Y');

    fclose(receipt);
    fclose(inventory);

    receipt = fopen(filePathBill, "r+b");

    printBillItems(receipt);

    fclose(receipt);

    holdScreen();
}

/**
 * Get product details from the user and write them to the specified file.
 * The function prompts the user to enter product details, such as name, rate, product ID, and stock quantity.
 * The details are then stored in the file specified by the 'file' parameter using the 'fwrite()' function.
 *
 * @param file The pointer to the file where the product details will be written.
*/
void getProductDetails(FILE *file) {
    struct product newProduct;

    textAnimation("\nEnter product details:\n");

    while(1){
        printf("\nProduct ID: ");
        scanf("%ld", &newProduct.productId);
        if(checkProductIdExists(file, newProduct.productId)) break;
        else{
            printf("\nProduct Already Exists. Enter a new Product ID!");
        }
    }

    fflush(stdin);
    printf("Name(Make use of underscore(_) for spaces): ");
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0'; // Remove trailing newline character


    printf("Rate: ");
    scanf("%f", &newProduct.rate); // Read the product rate

    printf("In Stock: ");
    scanf("%d", &newProduct.inStock); // Read the stock quantity

    // Write the product details to the file
    fwrite(&newProduct,sizeof(newProduct),1,file);
}

/**
 * Add products to the inventory.
 * The function allows the user to input product details such as name, rate, product ID, and stock quantity.
 * The product details are written to the "inventory.dat" file.
 * After adding a product, the user is asked if they want to add another product (Y/N).
*/
void addInventory(){
    struct product newProduct;
    char* filePath = strcat(getDataFilesPath(), "\\inventory.dat");
    char ch;

    FILE *inventory;
    inventory = fopen(filePath,"a+b");

    if(inventory == NULL){
        perror("Error opening file.");
        exit(-1);// terminate program with error code -1
    }

    do {
        getProductDetails(inventory);

        printf("Do you want to add another product? (Y/N): ");
        scanf(" %c", &ch);
    } while (ch == 'Y' || ch == 'y');

    // Close the file after use
    fclose(inventory);
    holdScreen();
}

/**
 * Manage the properties of items in the inventory.
 * This function allows the user to edit the properties of a product in the inventory, such as name, rate, and stock quantity.
 * The user is prompted to enter the product ID of the item to be edited.
 * If the product ID exists, the user can choose which property to edit.
 * The updated product details are then written back to the "inventory.dat" file.
 */
void manageInventory() {
    struct product product;
    char* filePath = strcat(getDataFilesPath(), "\\inventory.dat");
    int ch;
    char choice;
    long int productID;
    int newStock;

    FILE* inventory;
    inventory = fopen(filePath, "r+b");

    if (inventory == NULL) {
        perror("Error opening file.");
        exit(-1); // terminate program with error code -1
    }

    textAnimation("\nHere you can manage the edit the properties of the Items in inventory:\n");

    while (1) { // accepts only product id which exists in file
        printf("\nProduct ID: ");
        scanf("%ld", &productID);
        if (checkProductIdExists(inventory, productID) == 0) break;
        else {
            printf("\nProduct Doesn't Exist. Enter a valid Product ID!");
        }
    }

    while (fread(&product, sizeof(product), 1, inventory) == 1) {
        if (product.productId == productID) {
             printf("\n%s\t%2f\t%ld\t%d\n", product.name, product.rate, product.productId, product.inStock);
            do{
                textAnimation("\nEnter what do you want to edit of this product:\n1)Name\n2)Rate\n3)Stocks\n4)Exit\n->");
                while(1){// only exits when options from 1 to 4 is entered
                    ch = getch() - '0';
                    if (ch >= 1 && ch <= 4) {
                        break; // Exit the loop if the option is valid
                    } else {
                        printf("\nInvalid Option. Please choose a valid option (1 to 4): ");
                    }
                }
                switch(ch){
                    case 1:
                        fflush(stdin);
                        printf("Enter the new name of product: ");
                        fgets(product.name, sizeof(product.name), stdin);
                        product.name[strcspn(product.name, "\n")] = '\0'; // Remove trailing newline character

                        break;
                    case 2:
                        printf("Enter new rate of product: ");
                        scanf("%f",&product.rate);
                        break;
                    case 3:
                        printf("Enter the amount of stocks for this product: ");
                        scanf("%d", &product.inStock);
                        break;
                    case 4:
                        break;
                }
                printf("\nDo you want to edit more properties? [y/n] : ");
                choice = getche();
            }while(choice == 'y' || choice == 'Y');

            // finding and editing
            fseek(inventory, -sizeof(product), SEEK_CUR);
            fwrite(&product, sizeof(product), 1, inventory);
            printf("\nProduct Update Successful!");
            break;
        }
    }
    fclose(inventory);
    holdScreen();
}

/**
 * Display the items available in the inventory.
 * The function reads the product details from the "inventory.dat" file and prints them in a tabular format.
 * Each product's Serial Number (S.N.), Name, Rate, Product ID, and In Stock quantity are displayed.
*/
void checkInventory(){
    int serialNumber = 1;
    struct product product;
    char* filePath = strcat(getDataFilesPath(), "\\inventory.dat");

    FILE *inventory;
    inventory = fopen(filePath,"rb");

    textAnimation("\nItems available in inventory:\n");

    printf("%-4s%-30s%-10s%-15s%-8s\n", "S.N.", "Name", "Rate", "Product ID", "In Stock");
    printf("---------------------------------------------------------------\n");

    // Read and print the product details from the file
    while (fread(&product, sizeof(product), 1, inventory) == 1) {
        printf("%-4d%-30s%-10.2f%-15ld%-8d\n", serialNumber, product.name, product.rate, product.productId, product.inStock);
        serialNumber++;
    }
    fclose(inventory);
    holdScreen();
}

/**
 * Display the exit text
*/
void exitMessage(){
    textAnimation("\nThank You For Using Our Software.");
    getch();
}

/**
 * Display the application functions menu and execute the selected option.
 * The function presents a menu with available options and performs actions based on the user's choice.
 * The available options are: Sales Bill, Add Inventory, Manage Stocks, See Inventory, and Exit.
*/
void showAppFunctions(){
    textAnimation("\n\nPlease select one of the following options\n1) Sales Bill\n2) Add Inventory\n3) Manage Stocks\n4) See Inventory\n5) Exit");
    int ch;

    while(1){// only exits when options from 1 to 5 is entered
        ch = getch() - '0';
        if (ch >= 1 && ch <= 5) {
            break; // Exit the loop if the option is valid
        } else {
            printf("\nInvalid Option. Please choose a valid option (1 to 5): ");
        }
    }
    // respective function for respective number
    switch(ch){
        case 1:
            salesBill();
            break;
        case 2:
            addInventory();
            break;
        case 3:
            manageInventory();
            break;
        case 4:
            checkInventory();
            break;
        case 5:
            exitMessage();
            break;
        default:
            printf("Invalid Option");
            break;
    }
}

/**
 * Main function to run the billing system application.
 * This function performs the following steps:
 * 1. Creates a directory for all data files using preDataFileCreation().
 * 2. Displays a loading animation using LoadingAnimation().
 * 3. Greets the user with a welcome message using welcomeMessage().
 * 4. Prompts the user to sign in or create a new account using signInUser().
 * 5. Displays the application functions menu and executes the selected option using showAppFunctions().
 * 6. Returns 0 to indicate successful execution of the program.
 */
int main() {
    int status=0;

    preDataFileCreation();// creates a directory for all data files

    LoadingAnimation();// loading animation

    welcomeMessage(); // greets the user

    // until the user logs in with correct information loop continues
    while(1){
        status = signInUser();
        if(status == 1) break;
    }

    showAppFunctions();// launching funtions according to user

    return 0;
}
