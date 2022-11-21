#include <stdio.h>
#include <string.h>
#include <malloc.h>

void Task1(){
    int l1, l2;
    char *str1, *str2;

    printf("Enter the length of the first string: ");
    scanf("%d", &l1);
    str1 = (char*)malloc((l1 + 1) * sizeof(char));
    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter the length of the second string: ");
    scanf("%d", &l2);
    str2 = (char*)malloc((l2 + 1) * sizeof(char));
    printf("Enter second string: ");
    scanf("%s", str2);

    strcat(str1, str2);
    printf("%s\n", str1);
};

void Task6(){
    int n;
    printf("Enter the length of the string: ");
    scanf("%d", &n);
    char *str2 = (char*)malloc((n + 1) * sizeof(char));
    printf("Enter string: ");
    scanf("%s", str2);

    int n1;
    printf("Enter the length of the copy string: ");
    scanf("%d", &n1);
    char *str1 = (char*)malloc((n1 + 1) * sizeof(char));

    strncpy(str1, str2, n1);
    str1[n1] = '\0';
    printf("%s\n", str1);
}

void Task8(){
    int n;
    printf("Enter the length of the string: ");
    scanf("%d", &n);
    char *str = (char*)malloc((n + 1) * sizeof(char));
    char c;
    scanf("%s", str);
    scanf("\n%c", &c);
    int i;
    for (int i = 0; i < n; i++){
        if (str[i] == c){
            printf("Found %c at position %d", c, i + 1);
            return;
        }
    } 
    printf("Not found %c", c);

}
void Task10(){
    int l1, l2;
    char *str1, *str2;

    printf("Enter the length of the first string: ");
    scanf("%d", &l1);
    str1 = (char*)malloc((l1 + 1) * sizeof(char));
    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter the length of the second string: ");
    scanf("%d", &l2);
    str2 = (char*)malloc((l2 + 1) * sizeof(char));
    printf("Enter second string: ");
    scanf("%s", str2);
    int i, j;
    for (i = 0; i < l1; i++){
        for (j = 0; j < l2; j++){
            if (str1[i] == str2[j]){
                printf("Found !");
                return;
            }
        }
    }
    printf("Not found");
}

void Task12(){
    int l1, l2;
    char *str1, *str2;

    printf("Enter the length of the first string: ");
    scanf("%d", &l1);
    str1 = (char*)malloc((l1 + 1) * sizeof(char));
    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter the length of the second string: ");
    scanf("%d", &l2);
    str2 = (char*)malloc((l2 + 1) * sizeof(char));
    printf("Enter second string: ");
    scanf("%s", str2);
    int i, j;
    int length = 0;
    int found;
    for (i = 0; i < l1; i++){
        found = 0;
        for (j = 0; j < l2; j++){
            if (str1[i] == str2[j]){
                found = 1;
                break;
            }
        }
        if (found == 0){
            length++;
        }
    }
    printf("%d", length);
}

int main(){
    int t;
    printf("Enter task number: ");
    scanf("%d", &t);
    switch (t)
    {
    case 1:
        Task1();
        break;
    case 6:
        Task6();
        break;
    case 8:
        Task8();
        break;
    case 10:
        Task10();
        break;
    case 12:
        Task12();
        break;
    default:
        break;
    }
    return 0;
}