int main () {
    int a;
    int b;
    int c;
    a = 1;
    b = 4;
    c = 28;
    int t;
    if (c + a != b) {
        t = c % -b;
        printf("%d\n",t);
    }
    if (b - c == a) {
        t = c%b+b;
        printf("%d\n",t);
    }
    return 0;
}
