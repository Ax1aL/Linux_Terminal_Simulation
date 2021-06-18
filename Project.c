#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define clear() printf("\033[H\033[J")

//PORJECT OPERATING SYSTEMS II
//DOBRE RADU-CRISTIAN
//1221 EA



void init_shell();
void takeInput();
int execInput();
void printDir();
void help();

char history[100][100];
int pos=0;



void init_shell()
{
	clear();
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****MY SHELL****");
	printf("\n\n    -USE HELP FOR MORE INFO-");
	printf("\n\n\n\n*******************"
		"***********************");
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
	sleep(3);
	clear();
}

void takeInput(){
printf("\n>>>");
	char str[1024]="";
fgets(str,1024,stdin);

if(!strcmp(str,"\n")){
return;}
for(int j=0;j<strlen(str);++j){
str[j]=tolower(str[j]);}

char* nul;
char * t=strtok_r(str,"\n",&nul);
char *toke;

while((toke=strtok_r(t,";",&t))){
char temp[255]="";
strcat(temp,toke);

switch(execInput(temp)){

		case 0:exit(0);break;
		case 1:printf("is unknown command!\n");break;
		case 2:system("ls");break;
		case 3:help();break;
		case 4:system("pwd");break;

		default:break;
		}


	}


}


int execInput(char input[100])
{
char buf[100]="";
strcat(buf,input);

char * token=strtok(buf," ");


if(token==NULL){return -1;}

//history[pos++]=token;

if(!strcmp(token,"history")){
int hisTemp=0;
printf("\nHistory:");
while(strcmp(history[hisTemp],"\n")!=0){
printf("%s ",history[hisTemp]);
	++hisTemp;
	}
printf("\n");
return -1;
}

memcpy(history[pos++],token,strlen(token));
if(!strcmp(token,"exit")){
return 0;
}



if(!strcmp(token,"ls")){
return 2;
}

if(!strcmp(token,"help")){
return 3;
}

if(!strcmp(token,"pwd")){

return 4;
}



if(!strcmp(token,"cd")){
token=strtok(NULL,"");
chdir(token);
return -1;
}

if(!strcmp(token,"mkdir")){
token=strtok(NULL,"");
char lol[100]="";
memcpy(lol,token,strlen(token));
strcat(buf," ");
strcat(buf,lol);
system(buf);
return -1;
}

if(!strcmp(token,"touch")){
token=strtok(NULL,"");
char lol[100]="";
memcpy(lol,token,strlen(token));
strcat(buf," ");
strcat(buf,lol);
system(buf);
return -1;
}

//GETING FROM FILE
if(!strcmp(token,"getfilecom")){
token=strtok(NULL,"");

FILE *ptr;
if((ptr=fopen(token,"r"))==NULL){
printf("\nError opening the file!\n");
return -1;}


char str[1024]="";

fgets(str,1024,ptr);
while(!feof(ptr)){
for(int j=0;j<strlen(str);++j){str[j]=tolower(str[j]);}
char* nul;
char * t=strtok_r(str,"\n",&nul);
char * toke;

while((toke=strtok_r(t,";",&t))){

char temp[255]="";
strcat(temp,toke);

switch(execInput(temp)){

		case 0:exit(0);break;
		case 1:printf("is unknown command!\n");break;
		case 2:system("ls");break;
		case 3:help();break;
		case 4:system("pwd");break;

		default:break;
		}

	}

fgets(str,1024,ptr);
}
fclose(ptr);


return -1;
}


printf("\n%s ",buf);
return 1;
}
 
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nCurrent dir: %s", cwd);
}

void help(){
printf("\nls         -to list the files in the current dir\n");
printf("exit       -leave the program\n");
printf("cd *name*  -enter another dir\n");
printf("pwd        -prints current dir\n");
printf("history    -gets the last commands in this session\n");
printf("mkdir *name* -makes a new dir\n");
printf("touch *name* -makes a new file\n");
printf("getfilecom *file name* -gets commands from file\n");




}



int main()
{
	init_shell();

for(int i=0;i<100;++i){
memcpy(history[i],"\n",2);
}


	while (1) {
		printDir();
		takeInput();
		//exit(0);
	}
	return 0;
}

