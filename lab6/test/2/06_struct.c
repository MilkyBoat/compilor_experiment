struct Node{
    int num;
    int id;
};
int main(){
    for(int i=0;i<10;i=i+1){
        struct Node s;
        s.num=i*2;
        s.id=i;
        printf("%d ",s.num);
        printf("%d\n",s.id);
    }
    return 0;
}