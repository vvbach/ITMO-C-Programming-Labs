#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Task1(){
    char str[255];
    printf("Enter string: ");
    scanf("%s", str);
    int i;
    int digit = 0;
    int lower_case = 0;
    int upper_case = 0;
    for (i = 0; i < strlen(str); i++){
        if (str[i] >= '0' && str[i] <= '9'){
            digit++;
        } 
        
        else if (str[i] >= 'a' && str[i] <= 'z'){
            lower_case++;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z'){
            upper_case++;
        }
    }
    printf("Number of digits: %d\n", digit);
    printf("Number of uppercase letters: %d\n", upper_case);
    printf("Number of lowercase letters: %d\n", lower_case);
    
}

void Task3(){
    char n;
    scanf("%c", &n);
    char* word[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    if (n >= '0' && n <= '9'){
        printf("%s", word[n - '0']);
    }
    else {
        printf("Not a digit");
    }
}

int main(){
    Task3();
    return 0;
}