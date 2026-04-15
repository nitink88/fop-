#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int acc_no;
    char name[30];
    int pin;
    char type;
    float balance;
} Account;

int checkpointExists = 0;

int readInt() {
    int x;
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. Enter number: ");
    }
    return x;
}

float readFloat() {
    float x;
    while (scanf("%f", &x) != 1) {
        while (getchar() != '\n');
        printf("Invalid amount. Enter again: ");
    }
    return x;
}

void initFiles() {
    FILE *fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        fp = fopen("accounts.dat", "wb");
        if (fp) fclose(fp);
    } else {
        fclose(fp);
    }
}

int generateAccountNumber() {
    FILE *fp = fopen("accounts.dat", "rb");
    int max_acc = 1000;
    Account acc;
    
    if (fp != NULL) {
        while (fread(&acc, sizeof(Account), 1, fp) == 1) {
            if (acc.acc_no > max_acc) {
                max_acc = acc.acc_no;
            }
        }
        fclose(fp);
    }
    
    return max_acc + 1;
}

void createAccount() {
    Account acc;
    FILE *fp;
    
    printf("\n========== CREATE NEW ACCOUNT ==========\n");
    
    acc.acc_no = generateAccountNumber();
    printf("Auto-generated Account Number: %d\n", acc.acc_no);
    
    printf("Enter Name: ");
    scanf(" %29[^\n]", acc.name);
    
    printf("Enter PIN (4 digits): ");
    acc.pin = readInt();
    
    printf("Account Type (S-Savings / C-Current): ");
    scanf(" %c", &acc.type);
    
    printf("Initial Deposit (Min 1000): ");
    acc.balance = readFloat();
    
    if (acc.balance < 1000) {
        printf("Error: Minimum balance must be 1000\n");
        return;
    }
    
    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("Error: Cannot open file\n");
        return;
    }
    
    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    
    printf("\nAccount created successfully!\n");
    printf("Your Account Number: %d\n", acc.acc_no);
}

int login(int *acc_no) {
    int attempts = 3;
    int input_acc, input_pin;
    FILE *fp;
    Account acc;
    int found = 0;
    
    printf("\n========== LOGIN ==========\n");
    printf("Enter Account Number: ");
    input_acc = readInt();
    
    while (attempts > 0) {
        printf("Enter PIN: ");
        input_pin = readInt();
        
        fp = fopen("accounts.dat", "rb");
        if (fp == NULL) {
            printf("Error: Cannot open file\n");
            return 0;
        }
        
        found = 0;
        while (fread(&acc, sizeof(Account), 1, fp) == 1) {
            if (acc.acc_no == input_acc) {
                found = 1;
                if (acc.pin == input_pin) {
                    fclose(fp);
                    *acc_no = input_acc;
                    printf("Login successful! Welcome %s\n", acc.name);
                    return 1;
                }
                break;
            }
        }
        fclose(fp);
        
        if (!found) {
            printf("Account not found\n");
            return 0;
        }
        
        attempts--;
        if (attempts > 0) {
            printf("Wrong PIN. %d attempt(s) remaining\n", attempts);
        }
    }
    
    printf("Login failed. Too many attempts.\n");
    return 0;
}

void backupDatabase() {
    FILE *src = fopen("accounts.dat", "rb");
    FILE *dest = fopen("undo.dat", "wb");
    char ch;
    
    if (!src || !dest) {
        if (src) fclose(src);
        if (dest) fclose(dest);
        return;
    }
    
    while (fread(&ch, 1, 1, src)) {
        fwrite(&ch, 1, 1, dest);
    }
    
    fclose(src);
    fclose(dest);
    
    checkpointExists = 1;
}

void restoreDatabase() {
    if (!checkpointExists) {
        printf("No committed transaction to rollback\n");
        return;
    }
    checkpointExists = 0;
    
    FILE *test = fopen("undo.dat", "rb");
    if (!test) {
        printf("No transaction available to recover\n");
        return;
    }
    fclose(test);
    
    FILE *src = fopen("undo.dat", "rb");
    FILE *dest = fopen("accounts.dat", "wb");
    char ch;
    
    if (!src || !dest) {
        if (src) fclose(src);
        if (dest) fclose(dest);
        printf("Recovery failed\n");
        return;
    }
    
    while (fread(&ch, 1, 1, src)) {
        fwrite(&ch, 1, 1, dest);
    }
    
    fclose(src);
    fclose(dest);
    
    remove("undo.dat");
    printf("Recovery complete: database restored to last consistent state\n");
}

void deposit(int acc_no) {
    FILE *fp_acc = fopen("accounts.dat", "rb");
    FILE *fp_temp = fopen("temp.dat", "wb");
    Account acc;
    int found = 0;
    float amount;
    char confirm;
    int backedUp = 0;
    
    if (fp_acc == NULL || fp_temp == NULL) {
        if (fp_acc) fclose(fp_acc);
        if (fp_temp) fclose(fp_temp);
        printf("Error opening files\n");
        return;
    }
    
    printf("\n========== DEPOSIT ==========\n");
    printf("Enter amount to deposit: ");
    amount = readFloat();
    
    if (amount <= 0) {
        printf("Invalid amount\n");
        fclose(fp_acc);
        fclose(fp_temp);
        remove("temp.dat");
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp_acc) == 1) {
        if (acc.acc_no == acc_no) {
            if (!backedUp) {
                fclose(fp_acc);
                fclose(fp_temp);
                backupDatabase();
                fp_acc = fopen("accounts.dat", "rb");
                fp_temp = fopen("temp.dat", "wb");
                backedUp = 1;
                continue;
            }
            found = 1;
            printf("Current Balance: %.2f\n", acc.balance);
            acc.balance += amount;
            printf("New Balance: %.2f\n", acc.balance);
            printf("Confirm transaction? (y/n): ");
            scanf(" %c", &confirm);
            
            if (confirm != 'y' && confirm != 'Y') {
                fclose(fp_acc);
                fclose(fp_temp);
                remove("temp.dat");
                restoreDatabase();
                printf("Transaction cancelled\n");
                return;
            }
        }
        fwrite(&acc, sizeof(Account), 1, fp_temp);
    }
    
    fclose(fp_acc);
    fclose(fp_temp);
    
    if (!found) {
        remove("temp.dat");
        if (backedUp) restoreDatabase();
        printf("Account not found\n");
        return;
    }
    remove("accounts.dat");
    if (rename("temp.dat", "accounts.dat") != 0) {
        printf("Critical file update error. Attempting recovery...\n");
        restoreDatabase();
        return;
    }
    
    remove("undo.dat");
    checkpointExists = 0;
    printf("Transaction committed successfully\n");
    time_t t = time(NULL);
    printf("Committed at: %s", ctime(&t));
    printf("Deposit successful!\n");
}

void withdraw(int acc_no) {
    FILE *fp_acc = fopen("accounts.dat", "rb");
    FILE *fp_temp = fopen("temp.dat", "wb");
    Account acc;
    int found = 0;
    float amount;
    char confirm;
    int backedUp = 0;
    
    if (fp_acc == NULL || fp_temp == NULL) {
        if (fp_acc) fclose(fp_acc);
        if (fp_temp) fclose(fp_temp);
        printf("Error opening files\n");
        return;
    }
    
    printf("\n========== WITHDRAW ==========\n");
    printf("Enter amount to withdraw: ");
    amount = readFloat();
    
    if (amount <= 0) {
        printf("Invalid amount\n");
        fclose(fp_acc);
        fclose(fp_temp);
        remove("temp.dat");
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp_acc) == 1) {
        if (acc.acc_no == acc_no) {
            if (!backedUp) {
                fclose(fp_acc);
                fclose(fp_temp);
                backupDatabase();
                fp_acc = fopen("accounts.dat", "rb");
                fp_temp = fopen("temp.dat", "wb");
                backedUp = 1;
                continue;
            }
            found = 1;
            printf("Current Balance: %.2f\n", acc.balance);
            
            if (acc.balance - amount < 1000) {
                printf("Error: Minimum balance of 1000 must be maintained\n");
                fclose(fp_acc);
                fclose(fp_temp);
                remove("temp.dat");
                restoreDatabase();
                return;
            }
            
            acc.balance -= amount;
            printf("New Balance: %.2f\n", acc.balance);
            printf("Confirm transaction? (y/n): ");
            scanf(" %c", &confirm);
            
            if (confirm != 'y' && confirm != 'Y') {
                fclose(fp_acc);
                fclose(fp_temp);
                remove("temp.dat");
                restoreDatabase();
                printf("Transaction cancelled\n");
                return;
            }
        }
        fwrite(&acc, sizeof(Account), 1, fp_temp);
    }
    
    fclose(fp_acc);
    fclose(fp_temp);
    
    if (!found) {
        remove("temp.dat");
        if (backedUp) restoreDatabase();
        printf("Account not found\n");
        return;
    }
    
    remove("accounts.dat");
    if (rename("temp.dat", "accounts.dat") != 0){
 
        printf("Critical file update error. Attempting recovery...\n");
        restoreDatabase();
        return;
    }
    
    remove("undo.dat");
    checkpointExists = 0;
    printf("Transaction committed successfully\n");
    time_t t = time(NULL);
    printf("Committed at: %s", ctime(&t));
    printf("Withdrawal successful!\n");
}

void transfer(int from_acc) {
    FILE *fp_acc = fopen("accounts.dat", "rb");
    FILE *fp_temp = fopen("temp.dat", "wb");
    Account acc;
    int to_acc;
    float amount;
    int from_found = 0, to_found = 0;
    Account from_account, to_account;
    char confirm;
    
    printf("\n========== TRANSFER FUNDS ==========\n");
    printf("Enter recipient account number: ");
    to_acc = readInt();
    
    if (to_acc == from_acc) {
        printf("Cannot transfer to same account\n");
        if (fp_acc) fclose(fp_acc);
        if (fp_temp) fclose(fp_temp);
        return;
    }
    
    if (fp_acc == NULL || fp_temp == NULL) {
        if (fp_acc) fclose(fp_acc);
        if (fp_temp) fclose(fp_temp);
        printf("Error opening files\n");
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp_acc) == 1) {
        if (acc.acc_no == from_acc) {
            from_found = 1;
            from_account = acc;
        }
        if (acc.acc_no == to_acc) {
            to_found = 1;
            to_account = acc;
        }
    }
    fclose(fp_acc);
    fclose(fp_temp);
    
    if (!from_found || !to_found) {
        printf("One or both accounts not found\n");
        return;
    }
    
    printf("Your Balance: %.2f\n", from_account.balance);
    printf("Enter amount to transfer: ");
    amount = readFloat();
    
    if (amount <= 0) {
        printf("Invalid amount\n");
        return;
    }
    
    if (from_account.balance - amount < 1000) {
        printf("Error: Minimum balance of 1000 must be maintained\n");
        return;
    }
    
    backupDatabase();
    
    from_account.balance -= amount;
    to_account.balance += amount;
    
    printf("\nTransfer Summary:\n");
    printf("From Account %d: %.2f (New Balance)\n", from_acc, from_account.balance);
    printf("To Account %d: %.2f (New Balance)\n", to_acc, to_account.balance);
    printf("Confirm transaction? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm != 'y' && confirm != 'Y') {
        restoreDatabase();
        printf("Transaction cancelled. Balance unchanged.\n");
        return;
    }
    
    fp_acc = fopen("accounts.dat", "rb");
    fp_temp = fopen("temp.dat", "wb");
    
    if (fp_acc == NULL || fp_temp == NULL) {
        if (fp_acc) fclose(fp_acc);
        if (fp_temp) fclose(fp_temp);
        printf("Error opening files\n");
        restoreDatabase();
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp_acc) == 1) {
        if (acc.acc_no == from_acc) {
            fwrite(&from_account, sizeof(Account), 1, fp_temp);
        } else if (acc.acc_no == to_acc) {
            fwrite(&to_account, sizeof(Account), 1, fp_temp);
        } else {
            fwrite(&acc, sizeof(Account), 1, fp_temp);
        }
    }
    
    fclose(fp_acc);
    fclose(fp_temp);
    remove("accounts.dat");
    if (rename("temp.dat", "accounts.dat") != 0) {
        printf("Critical file update error. Attempting recovery...\n");
        restoreDatabase();
        return;
    }
    
    remove("undo.dat");
    checkpointExists = 0;
    printf("Transaction committed successfully\n");
    time_t t = time(NULL);
    printf("Committed at: %s", ctime(&t));
    printf("Transfer successful!\n");
}

void showAccount(int acc_no) {
    FILE *fp = fopen("accounts.dat", "rb");
    Account acc;
    int found = 0;
    
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    printf("\n========== ACCOUNT DETAILS ==========\n");
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.acc_no == acc_no) {
            printf("Account Number: %d\n", acc.acc_no);
            printf("Name: %s\n", acc.name);
            printf("Account Type: %c\n", acc.type);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("Account not found\n");
    }
}

void menu(int acc_no) {
    int choice;
    
    while (1) {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Transfer\n");
        printf("4. View Account Details\n");
        printf("5. System Recovery (Undo Last Operation)\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        choice = readInt();
        
        switch (choice) {
            case 1:
                deposit(acc_no);
                break;
            case 2:
                withdraw(acc_no);
                break;
            case 3:
                transfer(acc_no);
                break;
            case 4:
                showAccount(acc_no);
                break;
            case 5:
                restoreDatabase();
                break;
            case 6:
                remove("undo.dat");
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

int main() {
    int choice, acc_no;
    
    initFiles();
    
    FILE *u = fopen("undo.dat", "rb");
    if (u) {
        checkpointExists = 1;
        printf("Previous incomplete transaction detected.\n");
        printf("Recover database? (y/n): ");
        char c;
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y') restoreDatabase();
        fclose(u);
    }
    
    printf("========================================\n");
    printf("  TRANSACTION-SAFE BANK ACCOUNT SYSTEM\n");
    printf("     (Rollback Recovery Model)\n");
    printf("========================================\n");
    
    while (1) {
        printf("\n1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        choice = readInt();
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                if (login(&acc_no)) {
                    menu(acc_no);
                }
                break;
            case 3:
                printf("Thank you for using our bank!\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}