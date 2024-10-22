#include "chessboard.h"
#include "board_io.h"
#include "localization.h"
#include "check.c"
#include "mode.h"

int main() {
    set_localization();

    while (1) {
        system("cls");

        printf("+---------------------------------------------------------------+\n");
        printf("|                          GoBang Game                          |\n");
        printf("|          Developed by Chen Yumeng (2023K8009929028)           |\n");
        // printf("|          See https://github.com/Chen-Yuanmeng/GoBang          |\n");
        printf("+---------------------------------------------------------------+\n\n");

        printf("Please choose from the four modes below:\n\n");
        printf("\t1. Man-man combat\n");
        printf("\t2. Man-machine combat (man first)\n");
        printf("\t3. Man-machine combat (machine first)\n");
        printf("\t4. Machine-machine combat (Just watch!)\n");
        printf("\t----OR----------------------------------------\n");
        printf("\t5. Type 5 to exit :)\n\n");
        printf("Please enter your option (1/2/3/4/5) below and press enter:\n");

        int opt;

        scanf_s("%d", &opt);

        switch (opt) {
        case 1:
            man_man(); break;
        case 2:
            man_machine(); break;
        case 3:
            machine_man(); break;
        case 4:
            machine_machine(); break;
        case 5:
            return 0;
        default:
            printf("Please enter one digit 1 / 2 / 3 / 4 / 5.\nPress any key to re-enter.");
            system("pause > nul");
            break;
        }
    }

}

