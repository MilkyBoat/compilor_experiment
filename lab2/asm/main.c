#include <stdio.h>
int x = 1;
int n = 0;
int mult(int a, int b){
    return a * b;
}
void main(){
    scanf("%d", &n);
    while(n>0){
        x = mult(x, n);
        n--;
    }
    printf("%d\n", x);
}
