#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
typedef struct MorseNode
{
char letter;
struct MorseNode* dot;
struct MorseNode* dash;
}morse;

void insert(char* token, char letter, morse* root)
{
    morse* current=root;
    int i=0;
    while(token[i]!='\0')
    {
        if (token[i]=='.')
        {
                if (root->dot !=NULL)
                {
                    root = root->dot;
                }
                else{
                    //morse* temp;
                    root->dot=(morse*)malloc(sizeof(morse));
                    root->dot->dot=root->dot->dash=NULL;
                    root=root->dot;
                    }
        }
        if (token[i]=='-')
        {
                if (root->dash!=NULL)
                    root = root->dash;
	            else {
                    //morse* temp;
                    root->dash=(morse*)malloc(sizeof(morse));
                    root->dash->dot=root->dash->dash=NULL;
                    root = root->dash; 
                    }
        }
      i++;
    }
root->letter=letter;   
root=current;
}

void printInorder(morse* root)
{      
morse* current=root;        
        if (current != NULL) {
            printInorder(current->dot);
            if(current->letter!=' ')
            printf("%c",current->letter);  
            printInorder(current->dash);
        }
}

void decode(char* str, morse* root)
{
    if(str[0]!='\0')
    {
    printf("Decoded value is:  ");
        char signal;
        char* result;
        morse* current = root;
        for (int i = 0;i<strlen(str); i++) {
            signal = str[i];
            if (signal=='.') {
                if (current->dot!= NULL) {
                    current = current->dot;
                } /*else {
                    current->dot=(morse*)malloc(sizeof(morse));
                    current = current->dot;
                }*/
            }
            if (signal=='-') {
                if (current->dash != NULL) {
                    current = current->dash;
                } /*else {
                    current->dash=(morse*)malloc(sizeof(morse));
                    current = current->dash;
                }*/
            }
            else {
                printf("%c",current->letter);
	            current = root;
            }
        }
//if(current->letter!='\0' ||current->letter!=' ')
printf("%c\n",current->letter);
current=root;
    }
}

int searchTree(morse* current, char ltr, char*s, int top)
{
if(current==NULL){s[top--]='\0';return 0;}
if(current->letter==ltr){s[++top]='\0';return 1;}
s[++top]='.';
if(searchTree(current->dot,ltr,s,top)==1)
    return 1;
else
    s[top--]='\0';
s[++top]='-';
if(searchTree(current->dash,ltr,s,top)==1)
    return 1;
else
    s[top--]='\0';
s[top--]='\0';
return 0;
}

 
void encode(char* str, morse* root) {
        if(str[0]!='\0')
        {
        morse* current = root;
        char s[1000];
        int top=-1;
        char ltr;
        printf("Encoded value is:  ");
        for (int i = 0; i < strlen(str); i++) {
            ltr = tolower(str[i]);
            if(isalpha(str[i]))
            {
            searchTree(current, ltr,s,top);
            printf("%s ",s);
            }
            else if(str[i]==' ')
                printf("  ");
         }
         printf("\n");
        }
        str=NULL;
}

int main()
{
printf("*****WELCOME TO OUR MORSE CONVERTOR*****\n\n");
morse* root=(morse*)malloc(sizeof(morse));
root->letter=' ';
root->dot=NULL;
root->dash=NULL;
FILE* fp;
fp=fopen("encode.txt","r");
if(fp==NULL)
{
printf("Error in reading file\n");
exit(0);
}
char* token;
char* token1;
char t;
char read[100];
while(fgets(read,100,fp))
{
token1=strtok(read,",");
t=token1[0];
token=strtok(NULL,",");
insert(token,t,root);
}
fclose(fp);
printf("The binary tree has been loaded and looks like this inorder:  ");
printInorder(root);
printf("\n\n");
char eng[1000]="";
char mor[1000]="";
int loop=1;
int c;
int x=1;
printf("Enter 1 to convert English to Morse\nEnter 2 to convert Morse to English\nEnter 0 to stop execution\n");
while(loop)
{
scanf("%d",&c);
printf("\n");
switch(c)
{
case 1:
printf("Enter something to be converted into morse\n");
scanf("%[^\n]s",eng);
encode(eng,root);
break;
case 2:
printf("Enter something to be converted into english\n");
scanf("%[^\n]s",mor);
decode(mor,root);
break;
default:loop=0;
break;
}
}
return 0;
}