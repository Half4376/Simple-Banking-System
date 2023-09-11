#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct accountInfo {
    char phone[50];
    char accountNumber[50];
    char password[50];
    float balance;
};

void registerUser(struct accountInfo user, FILE *filePointer, char filename[50]) {
    system("CLS");

    printf("Enter your account number:\t");
    scanf("%s", user.accountNumber);

    printf("\nEnter your phone number:\t");
    scanf("%s", user.phone);

    printf("\nEnter your new password:\t");
    scanf("%s", user.password);

    user.balance = 0;

    strcpy(filename, user.phone);
    filePointer = fopen(strcat(filename, ".dat"), "w");
    fwrite(&user, sizeof(struct accountInfo), 1, filePointer);
    if(fwrite != 0) {
        printf("\n\nAccount succesfully registered");
    } else {
        printf("\n\nSomething went wrong please try again");
    }

    fclose(filePointer);
}

void loginUser(struct accountInfo user, FILE *filePointer, 
    char filename[50], char loginPhone[50], char loginPassword[50]) {
    system("CLS");

    printf("\nPhone number:\t");
    scanf("%s", loginPhone);

    printf("Password:\t");
    scanf("%s", loginPassword);

    strcpy(filename, loginPhone);
    filePointer = fopen(strcat(filename, ".dat"), "r");
    if (filePointer == NULL) {
        printf("\nAccount number not registered");
    } 

    fread(&user, sizeof(struct accountInfo), 1, filePointer);
    fclose(filePointer);

    if(!strcmp(loginPassword, user.password)) {
        userMenu(user, filePointer, filename, loginPhone, loginPassword);
    } else {
        printf("\nInvalid password");
    }
}

void userMenu(struct accountInfo user, FILE *filePointer, 
    char filename[50], char loginPhone[50], char loginPassword[50]) {
    
    int menuChoice;
    char cont = 'y';
    float amount;
    struct accountInfo otherUser;

    while(cont == 'y') {
        system("CLS");

        printf("\n\nPress 1 for balance inquiry");
        printf("\nPress 2 for depositing cash");
        printf("\nPress 3 for cash withdrawl");
        printf("\nPress 4 for online transfer");
        printf("\nPress 5 for password change");
        printf("\n\nYour choice:\t");
        scanf("%d", &menuChoice);

        switch (menuChoice)
        {
        case 1:
            printf("\nYour current balance is $%.2f", user.balance);
            break;
        case 2:
            printf("\nEnter the amount:\t");
            scanf("%f", &amount);
            user.balance += amount;
            filePointer = fopen(filename, "w");
            fwrite(&user, sizeof(struct accountInfo), 1 ,filePointer);

            if(fwrite != NULL) {
                printf("\nSuccessfully deposited");
            }

            fclose(filePointer);
            break;
        case 3:
            printf("\nEnter the amount:\t");
            scanf("%f", &amount);
            user.balance -= amount;
            filePointer = fopen(filename, "w");
            fwrite(&user, sizeof(struct accountInfo), 1, filePointer);
            fclose(filePointer);
            break;
        
        case 4:
            printf("\nPlease enter the phone number to transfer the balance:\t");
            scanf("%s", loginPhone);
            printf("\nPlease enter the amount to transfer:\t");
            scanf("%f", &amount);
            strcpy(filename, loginPhone);

            filePointer = fopen(strcat(filename,".dat"), "r");
            if(filePointer == NULL) {
                printf("\nAccount number not registered");
            } else {
                fread(&otherUser, sizeof(struct accountInfo), 1, filePointer);
            }

            fclose(filePointer);

            if(amount > user.balance) {
                printf("\nInsufficient balance");
                break;
            }

            filePointer = fopen(filename, "w");
            otherUser.balance += amount;
            fwrite(&otherUser, sizeof(struct accountInfo), 1, filePointer);

            fclose(filePointer);

            if(fwrite != NULL) {
                printf("\nYou have successfully transfered $%.2f to %s", amount, loginPhone);
                strcpy(filename, user.phone);

                filePointer = fopen(strcat(filename,".dat"), "w");
                user.balance -= amount;
                fwrite(&user, sizeof(struct accountInfo), 1, filePointer);
                fclose(filePointer);
            }
            break;
        case 5:
            printf("\nPlease enter your new password:\t");
            scanf("%s", loginPassword);
            filePointer = fopen(filename, "w");

            strcpy(user.password, loginPassword);
            fwrite(&user, sizeof(struct accountInfo), 1, filePointer);

            if(fwrite != NULL) {
                printf("\nPassword succesfully changed");
            }
            break;        
        default:
            printf("\nInvalid option.");
            break;
        }

        printf("\n\nDo you want to continue the transaction [y/n]\t");
        scanf("%s", &cont);

    }

    printf("\n\nHave a good day!!");
}

int main(void) {
    struct accountInfo user;
    int choice;
    FILE *filePointer;
    char filename[50], loginPhone[50], loginPassword[50];
    
    printf("\nHow may we help you?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d", &choice);

    if(choice == 1) {
        registerUser(user, filePointer, filename);
    };

    if(choice == 2) {
        loginUser(user, filePointer, filename, loginPhone, loginPassword);
    };

    return 0;
};