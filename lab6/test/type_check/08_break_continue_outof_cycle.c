int main () {
    int a = 0;
    for (int i = 0; i < 8; i++)
    {
        a++;
        printf("%d\n", a);
        if (i > 4)
            break;
    }
    if (a < 4)
        continue;
    else
        break;
    return 0;
}