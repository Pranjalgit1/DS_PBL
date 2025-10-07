#include "spellchecker.h"

//function to find the minimum between insert , delete , replace
int min(int a,int b,int c){
    int m = a < b ? a : b ;
    return m < c ? m : c;
}

int editdistance(char *s1,char *s2)
{
    int m,n,i,j;
    m=strlen(s1);
    n=strlen(s2);

    int table[m+1][n+1];

    //initializing first row and first column
    for(i=0;i<=m;i++)
    table[i][0]=i;
    for(j=0;j<=n;j++)
    table[0][j]=j;

    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
            table[i][j]=table[i-1][j-1];
            else{
                table[i][j]=1+min(
                    table[i-1][j],
                    table[i][j-1],
                    table[i-1][j-1]
                );
            }
        }
    }
    return table[m][n];
}

void run_spellchecker(char *input, const char *dict_file) {
    FILE *fp=NULL;
    fp=fopen(dict_file,"r");

    if(fp==NULL){
        printf("words cannot be loaded\n");
        return;
    }

    dictionary *d=malloc(3000*sizeof(dictionary));
    int count=0;
    char *word=NULL;
    size_t len=0;
    ssize_t read;

    while((read=getline(&word,&len,fp))!=EOF){
        //removing newline 
        word[strcspn(word,"\n")]=0;
        
        //splitting
        char *wordn=NULL,*meaning=NULL;
        wordn=strtok(word,"|");
        meaning=strtok(NULL,"|");
        
        //storing separately
        if(wordn && meaning){
            strcpy(d[count].word,wordn);
            strcpy(d[count].meaning,meaning);
            count++;
        }
    }

    fclose(fp);
    free(word);

    int mindist=1000;
    int idx=-1;

    for(int i=0;i<count;i++){
        int dist=editdistance(input,d[i].word);
        if(dist<mindist)
        {
            mindist=dist;
            idx=i;
        }
    }

    if (idx != -1) {
        printf("Did you mean: %s?\n", d[idx].word);
        printf("Meaning: %s\n", d[idx].meaning);
    } else {
        printf("No suggestion found.\n");
    }

    free(d);
}
