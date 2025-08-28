#include <stdio.h>

int main() {

    int arr[10][10] = {0};  

    char ch;
    do {
        int r, c, val;
        printf("Enter row index (0 to 9): ");
        scanf("%d", &r);
        printf("Enter column index (0 to 9): ");
        scanf("%d", &c);
        printf("Enter value: ");
        scanf("%d", &val);

        if (r >= 0 && r < 10 && c >= 0 && c < 10) {
            arr[r][c] = val;
        } else {
            printf("Invalid position.\n");
        }

        printf("Do you want to insert another value? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');


    // Print array
    printf("\nFinal 2D Array:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}