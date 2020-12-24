int main(){
    for(int i=0;i<10;i=i+1){
        printf("%d\n",i);
        if(i<5){
            printf("Continue\n");
            continue;
        }
        break;
    }
    return 0;
}