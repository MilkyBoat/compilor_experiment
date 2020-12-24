int main () {
    int a;
    int b;
    a = -2;
    b = 1;
    a = a - -b + -(a + b) % -(a - b);
    printf("%d\n",a);
    return 0;
}
