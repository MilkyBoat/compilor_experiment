/*
* 10+'0' may error or transform
* 10 +"0" must error
*/
int main(){
    int a;
    a=10+'0';
    a=10+"0";
    return 0;
}