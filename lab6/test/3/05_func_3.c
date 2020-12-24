int fact(int n) {
  if (n == 0) {
    return 1;
  }
  int nn;
  nn = n-1;
  return (n * fact(nn));
}

int main() {
  int n;
  n = 4;
  printf("%d\n",fact(n));
  return 0;
}
