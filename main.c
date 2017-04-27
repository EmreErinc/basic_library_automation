#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insertBook(FILE *authorAndBook){
    int index[5][30]={0}, bookNumber, i, j, hash;
    char authorAndBookNames[10][30][30]={0};
    char authorName[20],bookName[30];

    printf("Enter 'Book Number' between 1-150 : ");
    scanf("%d",&bookNumber);

    while(bookNumber<1 || bookNumber>150){
        printf("Enter 'Book Number' between 1-150 : ");
        scanf("%d",&bookNumber);
    }

    hash = bookNumber % 30;

    /*Dosyada yazılı olan 'index'ler okundu*/
    authorAndBook = fopen("index.dat","r+");
    for(i=0;i<30;i++){
        fscanf(authorAndBook,"%d%d%d%d%d\n",&index[0][i],&index[1][i],&index[2][i],&index[3][i],&index[4][i]);
    }
    /*fclose(authorAndBook);*/

    /*Dosyadan 'Author Name' ve 'Book Name' ler okundu*/
    authorAndBook = fopen("books.dat","r+");
    for(i=0;i<30;i++){
        for(j=0;j<10;j++){
            strcpy(authorAndBookNames[j][i],"NULL");
        }
    }
    for(i=0;i<30;i++){
        fscanf(authorAndBook,"%s%s%s%s%s%s%s%s%s%s\n",&authorAndBookNames[0][i],&authorAndBookNames[1][i]
            ,&authorAndBookNames[2][i],&authorAndBookNames[3][i],&authorAndBookNames[4][i],&authorAndBookNames[5][i]
            ,&authorAndBookNames[6][i],&authorAndBookNames[7][i],&authorAndBookNames[8][i],&authorAndBookNames[9][i]);
    }

    printf("Enter 'Author Name', please use '-' between words : ");
    scanf("%s",authorName);
    printf("Enter 'Book Name',please use '-' between words : ");
    scanf("%s",bookName);

    /*Uygun yerlere 'index' numaraları ,'authorName' ve 'bookName' yazıldı */
    if(index[0][hash-1]==0){
        index[0][hash-1]=bookNumber;
        strcpy(authorAndBookNames[0][hash-1],authorName);
        strcpy(authorAndBookNames[1][hash-1],bookName);
    }
    else if(index[0][hash-1]!=0){
        for(j=1;j<5;j++){
            if(index[j][hash-1]==0){
                index[j][hash-1]=bookNumber;
                strcpy(authorAndBookNames[j+j][hash-1],authorName);
                strcpy(authorAndBookNames[j+j+1][hash-1],bookName);
                break;
            }
        }
    }

    /*index.dat dosyasına veriler yazıldı*/
    if((authorAndBook = fopen("index.dat","w+"))==NULL){
        printf("Book Source File could not be opened\n");
    }
    else{
        for(i=0;i<30;i++){
            for(j=0;j<5;j++){
                fprintf(authorAndBook,"%d\t",index[j][i]);
            }
            fprintf(authorAndBook,"\n");
        }
    }
    fclose(authorAndBook);

    /*books.dat dosyasına veriler yazıldı*/
    if((authorAndBook = fopen("books.dat","w+"))==NULL){
        printf("Book Source File could not be opened\n");
    }
    else{
        for(i=0;i<30;i++){
            for(j=0;j<10;j++){
                fprintf(authorAndBook,"%s\t",authorAndBookNames[j][i]);
            }
            fprintf(authorAndBook,"\n");
        }
        printf("Done!!\n\n");
    }
    fclose(authorAndBook);
}

void searchAuthorOrBook(FILE *authorAndBook){
    int i,j=0,control=0;
    char searchText[30],willSearchText[30];
    printf("Enter 'Author Name' or 'Book Name' that you will search : ");
    scanf("%s",searchText);
    authorAndBook=fopen("books.dat","r+");
    while(!feof(authorAndBook)){
        fscanf(authorAndBook,"%s",willSearchText);
        for(i=0;i<30;i++){
            if(searchText[i]==willSearchText[i]){
                control++;
            }
        }
        if(control==30){
            printf("Record has been found..\n");
            j=1;
        }
    }
    if(j==0){
        printf("Record has not been found..\n");
    }
}

int searching(FILE *authorAndBook){
    int search,s,index[5][30],i,j=0,op,control=0;
    char authorAndBookNames[10][30];

    /*Dosyalardaki değerler dizilere atandı*/
    authorAndBook=fopen("index.dat","r+");
    for(i=0;i<30;i++){
        fscanf(authorAndBook,"%d%d%d%d%d\n",&index[0][i],&index[1][i],&index[2][i],&index[3][i],&index[4][i]);
    }
    /*fclose(authorAndBook);*/
    authorAndBook=fopen("books.dat","r+");
    for(i=0;i<30;i++){
        fscanf(authorAndBook,"%s%s%s%s%s%s%s%s%s%s\n",&authorAndBookNames[0][i],&authorAndBookNames[1][i]
            ,&authorAndBookNames[2][i],&authorAndBookNames[3][i],&authorAndBookNames[4][i],&authorAndBookNames[5][i]
            ,&authorAndBookNames[6][i],&authorAndBookNames[7][i],&authorAndBookNames[8][i],&authorAndBookNames[9][i]);
    }

    printf("\t1-Search by 'Book Number'\n\t2-Search by 'Author Name' or 'Book Name'\nSelect your operation : ");
    scanf("%d",&op);

    switch(op){
    case 1:
        printf("Enter 'Book Number' that you will search : ");
        scanf("%d",&search);
        s=search;
        search=search%30;
        for(i=0;i<5;s++){
            if(index[i][search-1]==s){
                printf("Record has been found..\n");
                printf("Book Number\tAuthor Name\tBook Name\n");
                printf("%d\t\t%s\t%s\n\n",s,authorAndBookNames[i+i][search-1],authorAndBookNames[i+i+1][search-1]);
                break;
            }
            else{
                printf("Record has not been found..\n\n");
                break;
            }
        }
        break;
    case 2:
        searchAuthorOrBook(authorAndBook);
        break;
    default:
        printf("Wrong selection!!");
        break;
    }
    fclose(authorAndBook);
}

int listing(FILE *authorAndBook){
    int i,j;
    char authorAndBookNames[10][30][30];
    authorAndBook=fopen("books.dat","r+");
    for(i=0;i<30;i++){
        fscanf(authorAndBook,"%s%s%s%s%s%s%s%s%s%s\n",&authorAndBookNames[0][i],&authorAndBookNames[1][i]
            ,&authorAndBookNames[2][i],&authorAndBookNames[3][i],&authorAndBookNames[4][i],&authorAndBookNames[5][i]
            ,&authorAndBookNames[6][i],&authorAndBookNames[7][i],&authorAndBookNames[8][i],&authorAndBookNames[9][i]);
    }
    printf("List of books..\n");
    for(i=0;i<30;i++){
        printf("%2d  ",i+1);
        for(j=1;j<10;j=j+2){
            printf("%15s",authorAndBookNames[j][i]);
        }
        printf("\n");
    }
}

int main()
{
    FILE *authorAndBook;
    int operation;
    do{
        printf("(1) - Insert a book\n");
        printf("(2) - Search a book\n");
        printf("(3) - List all the bookshelf\n");
        printf("(4) - Exit\n");
        printf("Please select your operation : ");
        scanf("%d",&operation);

        switch(operation){
        case 1:
            insertBook(authorAndBook);
            break;
        case 2:
            searching(authorAndBook);
            break;
        case 3:
            listing(authorAndBook);
            break;
        case 4:
            exit(0);
            break;
        }
    }
    while(operation!=4);
    return 0;
}
