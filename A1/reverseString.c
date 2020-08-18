#include <stdio.h>
#include <string.h>
void reverseString(char *stringPointer, int length){
    int start=0, end = length-1;
    //printf("%s", stringPointer);
    //printf("%d, %d", start, end);
    while(start < end){
        //interchanging them:
        //printf("%c, %c\n",stringPointer[start], stringPointer[end]);
        stringPointer[start] ^= stringPointer[end];
        //printf("%c, %c\n",stringPointer[start], stringPointer[end]);
        stringPointer[end] ^= stringPointer[start];
        //printf("%c, %c\n",stringPointer[start], stringPointer[end]);
        stringPointer[start] ^= stringPointer[end];

        start += 1;
        end -= 1;
    }
}


int main(){
    char str[20];
    //scanf("%s", str);
    fgets(str, 20,stdin);
    printf("%d\n", strlen(str));
    reverseString(str, strlen(str));

    printf("%s", str);
    return 0;}