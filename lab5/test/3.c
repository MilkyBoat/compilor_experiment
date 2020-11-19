/* I'm level 3 test, With no runtime */
int s = 0;
int f(int x, int y) {
    s += x*x + y*y;
    return s;
}
void main(){
    int i=0;
    int a=1, b=1;
    int line;
    scanf("%d", &line);
    if(line > 10000) line = 10000;
    while(true) {
        if(f(a++, b++)<line) {
            printf("sum is: %d\n", s);
        } else {
            printf("result is:%d\n", s);
            break;
        }
    }
}