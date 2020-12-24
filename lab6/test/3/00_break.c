int main(){
    for(int i=0;i<10;i=i+1){
        printf("Test:%d\n",i);
        if(i>5){
            printf("Break\n");
            break;
        }
    }
    return 0;
}