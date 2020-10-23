//Created by Viktoryia Tomason
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//number conversion function
void convert(char *string, char *digit) { 
    while(*string!='\0') {
        //search for the desired character and translation into the appropriate number
         if((*string >= 'a' && *string <= 'c') ||
           (*string >= 'A' && *string <= 'C')) {
            *digit='2';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'd' && *string <= 'f')
        || (*string >= 'D' && *string <= 'F')) {
            *digit='3';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'g' && *string<='i') 
        || (*string>='G' && *string<='I')) {
            *digit='4';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'j' && *string <= 'l')
        || (*string >= 'J' && *string <= 'L')) {
            *digit='5';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'm' && *string <= 'o')
        || (*string >= 'M' && *string <= 'O')) {
            *digit='6';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'p' && *string <= 's')
        || (*string >= 'P' && *string <= 'S')) {
            *digit='7';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 't' && *string <= 'v')
        || (*string >= 'T' && *string <= 'V')) {
            *digit='8';
            digit++;
            string++;
            continue;
        }
        else if((*string >= 'w' && *string <= 'z')
        || (*string >= 'W' && *string <= 'Z')) {
            *digit='9';
            digit++;
            string++;
            continue;
        }
        else if(*string == '+') {
            *digit='0';
            digit++;
            string++;
            continue;
        }
        else {
        //wriggling spaces
            string++;
        }
    }
  *digit='\0';
}


int main(int argc, char *argv[]) { 
    char name[100];
    char converted[100];
    char *point = argv[1];
    char number[100];
    bool flag = false; 
    bool found = false; 
    if(argc > 2) {
        printf("Invalid argc");
        return -1;
    }
    else if(argc == 1) {
        flag = true;
    }
    
    while(!feof(stdin)) {
        //reading a string
        fgets(name, 100, stdin);
        *(name + strlen(name)-1) = '\0';
        //reading a line
        fgets(number, 100, stdin);
        *(number + strlen(number)-1) = '\0';
        
        //list in correct format
        if(flag) {
            printf("%s, %s\n", name, number);
            continue;
        }

        convert(name, converted); 

        if (strstr(converted, point)) {
            printf("%s, %s\n", name, number);
            found = true;
        }
        else if (strstr(number, point)) {
            printf("%s, %s\n", name, number);
            found = true;
        }
        else {
            strcat(converted,number);
        int value=0;
        //cycle to search for Broken character sequences
        for(int n=0;n<strlen(point);n++)
            for(int i = 0; i<strlen(converted); i++)
            {
                if (point[n]==converted[i]) 
                {
                    n++;
                    value++;
                }
            }
        }
          if(value>=strlen(point))
            {
                printf("%s, %s\n", name, number);
                found=true;
            }   
        }
    }

    if(!found) {
        printf("Not found\n");
    }

    return 0;
}
