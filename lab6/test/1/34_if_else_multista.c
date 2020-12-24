int main(){
    int a=10;
    if(a>9){
        a=a-10;
        a=a%6;
    }else{
        a=2;
        a=a-30;
    }
    printf("Test:%d\n",a);
    return 0;
}