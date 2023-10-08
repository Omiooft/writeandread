#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "writeandread.h"
float verr = 1.0;
typedef struct {
    char ModeInput[2];
    char FileInput[500];
    char StringInput[255]; 
} createInput;

createInput user;
char globalBuffer[255];

void confirmFileName() {
    int yOrN;
    do {
        println("Input or create file directory(DR)");
        scanf("%s", user.FileInput);
        printf("You entered %s. Confirm? 1 for Y / 2 for N\n", user.FileInput);
        scanf("%d", &yOrN);
    } while (yOrN != 1);
}

void getMode() {
    int yOrN;
    println("\"w\" for writing/creating, and \"r\" for reading");
    scanf("%s", user.ModeInput);
    if (strcmp(user.ModeInput, "w") == 0 || strcmp(user.ModeInput, "a") == 0) {
        println("This will overwrite current data! \n[00]Start, [99]Exit");
        scanf("%d",&yOrN);
        if (yOrN!=99){
        println("Add your text below! (WARNING: THIS WILL OVERWRITE, CLOSE WINDOW TO EXIT!)");
        scanf(" %[^\n]", user.StringInput); 
        }
    }
}
int menuChoice;
void starterScreen() {
    printLogo();
    scanf("%d", &menuChoice);
}
void exitTime(char textt[] ,char text[]){
    printf("%s\n", textt);
    Sleep(4000);
    printf("%s\n", text);
    Sleep(1000);
}
int main() {
    starterScreen();
    if (menuChoice == 01)
    {
        printf("version %.1f\nexiting in 5 seconds..\n", verr);
        exitTime("starting countdown", "Bye!");
    }
    
    if (menuChoice == 00) {
        confirmFileName();
        getMode();

        FILE *pF = fopen(user.FileInput, user.ModeInput);
    if (pF == NULL) {
        fprintf(stderr, "Error opening file: %s\n", user.FileInput);
        return 1;
    }

    if (strcmp(user.ModeInput, "w") == 0 || strcmp(user.ModeInput, "a") == 0) {
        fprintf(pF, "%s", user.StringInput);
    }

    rewind(pF);

    while (fgets(globalBuffer, sizeof(globalBuffer), pF) != NULL) {
        printf("%s", globalBuffer);
    }

    fclose(pF);
}
else
{
    exitTime("Exiting in 5 seconds","Bye!");
}
return 0;
}
