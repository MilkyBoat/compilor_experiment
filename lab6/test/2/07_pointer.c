int main(){
    int *point;
    for(int i=0;i<10;i=i+1){
        int a=i+10;
        point=&a;
        printf("%d\n",*point);
    }
    return 0;
}