int a[10][10];
int main(){
    for(int i=0;i<10;i=i+1){
        for(int j=0;j<10;j=j+1){
            a[i][j]=i*j+i+j;
        }
    }
    for(int i=0;i<10;i=i+1){
        for(int j=0;j<10;j=j+1){
            printf("%d\n",a[i][j]);
        }
    }
    return 0;
}