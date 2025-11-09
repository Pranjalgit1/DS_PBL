#include "spellchecker.h"

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
    if(d==NULL){
        printf("Memory allocation failed\n");
        fclose(fp);
        return;
    }
    
    int count=0;
    char line[256];

    while(fgets(line, sizeof(line), fp) != NULL && count < 3000){
        line[strcspn(line,"\n")]=0;
        
        char *wordn=NULL,*meaning=NULL;
        wordn=strtok(line,"|");
        meaning=strtok(NULL,"|");
        
        if(wordn && meaning){
            strcpy(d[count].word,wordn);
            strcpy(d[count].meaning,meaning);
            count++;
        }
    }

    fclose(fp);

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

char* get_spellcheck_suggestion(char *input, const char *dict_file, char *suggestion_word, char *suggestion_meaning) {
    FILE *fp=NULL;
    fp=fopen(dict_file,"r");

    if(fp==NULL){
        return NULL;
    }

    dictionary *d=malloc(3000*sizeof(dictionary));
    if(d==NULL){
        fclose(fp);
        return NULL;
    }
    
    int count=0;
    char line[256];

    while(fgets(line, sizeof(line), fp) != NULL && count < 3000){
        line[strcspn(line,"\n")]=0;
        
        char *wordn=NULL,*meaning=NULL;
        wordn=strtok(line,"|");
        meaning=strtok(NULL,"|");
        
        if(wordn && meaning){
            strcpy(d[count].word,wordn);
            strcpy(d[count].meaning,meaning);
            count++;
        }
    }

    fclose(fp);

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
        strcpy(suggestion_word, d[idx].word);
        strcpy(suggestion_meaning, d[idx].meaning);
        free(d);
        return suggestion_word;
    } else {
        free(d);
        return NULL;
    }
}
