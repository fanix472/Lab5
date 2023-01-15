#include <stdio.h>
#include <stdlib.h>
#include  <Windows.h>

int write_to_bin(FILE *fPointer,int x1,int x2,int N,int delta);
void read_from_bin(FILE *fPointer,unsigned int n,int x1,int x2);
int write_to_txt(FILE *fPointer,int x1,int x2,int N,int delta);
void read_from_txt(FILE *fPointer,unsigned int n,int x1,int x2);
void save_result_to_array(FILE *fPointer,int n);

int main() {

    SetConsoleCP (65001);
    SetConsoleOutputCP (65001);

    int x1,x2;
    unsigned int N,delta,n;
    char group[10];
    char name[25];

    FILE *fInput;
    FILE *fReadTxt, *fWriteTxt;
    FILE *fReadBin, *fWriteBin;

    fInput = fopen("../input.txt","r");
    if(fInput == NULL) {
        printf("Не вдається відкрити файл!\n");
        return 0;
    }
    fscanf(fInput,"%d%d%u%u%s%s",&x1,&x2,&N,&delta,&group,&name);
    fclose(fInput);

    if(N==0){N = delta;}

    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %u\n",N);
    printf("крок = %u\n",delta);
    printf("група = %s\n",group);
    printf("група = %s\n",name);

    fWriteTxt = fopen("../result.txt","w");
    n = write_to_txt(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteTxt);

    fReadTxt  = fopen("../result.txt","r");
    read_from_txt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("../result.bin","wb");
    n = write_to_bin(fWriteBin,x1,x2,N,delta);
    fclose(fWriteBin);

    fReadBin  = fopen("../result.bin","rb");
    read_from_bin(fReadBin,n,x1,x2);
    fclose(fReadBin);

    fReadTxt  = fopen("../result.txt","r");
    save_result_to_array(fReadTxt,n);
    fclose(fReadTxt);

    return 0;
}

//=============================================================================================//

void read_from_txt(FILE *fPointer,unsigned int n,int x1,int x2) {

    int x,y;
    printf("TXT FILE (result.txt):\n");
    printf("Початок: %d\nКінець: %d\nКіл-ть кроків: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    for(int i = 1; i < n+1;i++) {
        fscanf(fPointer,"%d",&x);
        fscanf(fPointer,"%d",&y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
}

//=============================================================================================//

int write_to_txt(FILE *fPointer,int x1,int x2,int N,int delta) {

    int y,n = 0;
    for(int i = 0; i<=N; i++) {
        n++;
        y=x1*x1;
        fprintf(fPointer,"%d %d\n",x1,y);
        if(x1>=x2) {
            return n;
        }
        x1+=delta;
    }
    return n;
}

//=============================================================================================//

void read_from_bin(FILE *fPointer,unsigned int n,int x1,int x2) {

    int x,y;
    printf("BIN FILE (result.bin) : \n");
    printf("Початок: %d\nКінець: %d\nКіл-ть кроків: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    for(int i = 1; i < n+1;i++) {
        fread(&x,sizeof(int),1,fPointer);
        fread(&y,sizeof(int),1,fPointer);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
}

//=============================================================================================//

int write_to_bin(FILE *fPointer,int x1,int x2,int N,int delta) {

    int y,n = 0;
    for(int i = 0; i<=N; i++) {
        n++;
        y=x1*x1;
        fwrite(&x1,sizeof(int),1,fPointer);
        fwrite(&y,sizeof(int),1,fPointer);
        if(x1>=x2) {
            break;
        }
        x1+=delta;
    }
    return n;
}

//=============================================================================================//

void save_result_to_array(FILE *fPointer,int n) {

    int i,j,k;
    int **arr = (int **)malloc(n*sizeof(int*));

    for( i = 0; i < n; i++) {
        arr[i] = (int *)malloc(2*sizeof(int));
    }

    printf("Вміст массиву:\n");
    for(i = 0;i<n;i++) {
        for(j = 0;j<2;j++) {
            fscanf(fPointer,"%d",&k);
            arr[i][j] = k;
        }
    }

    for(i = 0;i<n;i++) {
        for(j = 0;j<1;j++) {
            printf("x: %d \ty: %d\n",arr[i][j],arr[i][j+1]);
        }
    }

    for(i = 0; i < n; i++) {
        free(arr[i]);
    }

    free(arr);
}

//=============================================================================================//