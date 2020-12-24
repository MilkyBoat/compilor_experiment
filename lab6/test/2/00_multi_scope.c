int a=10;
int main(){
    int a;
    a=1;
    for(int i=0;i<10;i=i+1){
        int a=i*10+i%3;
        printf("Test %d %d\n",i,a);
    }
    printf("Test %d\n",a);
    return 0;
}