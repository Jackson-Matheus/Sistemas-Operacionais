#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h>

#define ARG_LIM 10
#define INPUT_LIM 500
#define B_SIZE 1000
#define FILENAME_LIM 200


void exec_pwd(void);
void exec_cd(char * dir){
	printf("Diretorio solicitado : %s\n",dir);
	
	if(!chdir(dir))
		printf("Nao foi possivel acessar: %s\n",dir);
	exec_pwd();

	printf("boa lek");

}

void exec_pwd(void){
	char dir[300];
	printf("Diretorio atual %s \n",getcwd(dir,300));
}

void exec_ls(void){
	printf("Arquivos e pastas do diretorio atual : \n");
	system("ls");	
}


void exec_piping(char *args1[ARG_LIM], char *args2[ARG_LIM]){
	int pip[2];
	int pstat = pipe(pip);

	/*
	   int j = 0;

	   while(args1[j])
	   printf("sou o %d arg do 1 array : %s\n",j,args1[j++]);

	   j = 0;

	   printf("\n");

	   while(args2[j])
	   printf("sou o %d arg do 2 array : %s\n",j,args2[j++]);

	   printf("\n");
	   */
	if(pstat < 0){
		
		printf("Falha ao tentar usar pipe\n");
		exit(1);
	}

	int filho = fork();

	//printf("nice %d  \n\n\n",filho);
	if(filho < 0){
		printf("Falha ao criar o fork\n");
		exit(1);
	}else if(filho == 0){
		close(1);
		close(pip[0]);
		dup(pip[1]);
		execvp(args1[0],args1);
		exit(1);
	}else{
		wait(NULL);
		close(0);
		close(pip[1]);
		dup(pip[0]);
		execvp(args2[0],args2);
		//exit(1);
	}
}

void exec_in_out(char * args[ARG_LIM], char *filename,int mode){
	int arq;
	int i = 0;
	while (args[i])
		printf("%s\n",args[i++]);

    close(STDOUT_FILENO);
    open(filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    printf("%s", filename);
   
	/*if(arq < 0){
		printf("NAO FUNCIONOU \n");
		exit(1);
	}

	int desc = dup2(arq,0);
	if(desc < 0){
		printf("dozonte ork \n");
		exit(1);
	}*/


	//parte comentada Lino

    printf("%s", filename);
	execvp(args[0],args);    
	
	execvp(args[0],args);
}


void exec_arq(char * arq){
	char * aux;
	//char * aux_2;

	char * args[ARG_LIM];
	char * pargs[ARG_LIM];
	char filename[FILENAME_LIM];
	int i = 0,j = 0;
	int piping = 0;
	int in_out = 0;
	aux = strtok(arq," ");
	//printf("param %i : %s\n",i,aux);	
	while(aux != NULL){

		//printf("param %i : %s\n",i,aux);

		if(!strcmp(aux,"|")){
			//printf("Precisa de pipe\n");
			piping = 1;
			for(j = 0; j<i;j++){
				pargs[j] = args[j];
				args[j] = NULL;
			}
			pargs[j] = NULL;
			i = 0;
		}else if(!strcmp(aux,">")){
			args[i] = NULL;
			aux = strtok(NULL," ");
			strcpy(filename,aux);
			exec_in_out(args,filename,1);
			i = 0;
		}else if(!strcmp(aux,"<")){
			in_out = 1;
			args[i] = NULL;
			aux = strtok(NULL," ");
			strcpy(filename,aux);
		}else
			args[i++] = aux;

		aux = strtok(NULL," ");
	}
	args[i] = NULL;

	if(piping)
		exec_piping(pargs,args);	
	else if(in_out){
			close(0);
			
			int ap = open(filename, O_RDONLY);
			dup(ap);
			if(fork() == 0){
				execvp(args[0], args);
				exit(1);
			}else wait(NULL);
		

		}
	else
		execvp(args[0],args);

	//printf("%s\n",arq);
}

void exec_funcs(char * str){
	char * arg;
	char entrada[INPUT_LIM];
	//para o pipe
	char buffer[B_SIZE]; 
	//*
	strcpy(entrada,str);
	arg = strtok(str," ");

	if(!strcmp(arg,"exit")){
		printf("Bye !\n");
		exit(0);
	}

	int pfilho = fork();

	if(pfilho < 0){
		printf("O falha na criacao de um processo filho via fork !\n");
		return;
	}else if(pfilho == 0){

		if(!strcmp(arg,"cd")){

			printf("cmd : %s\n\n",arg);
			arg = strtok(NULL," ");

			printf("dir : %s\n\n",arg);

			printf("Diretorio solicitado : %s\n", arg);
	
			if(chdir(arg))
				printf("Nao foi possivel acessar: %s\n",arg);
			else 
				exec_pwd();
			printf("O comando cd precisa de um argumento para funcionar !\n");

		}else if(!strcmp(arg,"pwd")){
			exec_pwd();
		}  else {
			exec_arq(entrada);
		}
		//kill((int)getpid(),SIGKILL);
	}else wait(NULL);
}

int main(void){
	char entrada[INPUT_LIM];
	char dir[300];
	printf("Proto terminal 0.1v\nAutor : Lino Mota and Jackson Matheus \n");

	while(printf("%s $>",getcwd(dir,300))){
		scanf("%[^\n]%*c",entrada);
		exec_funcs(entrada);
	}

	return 0;
}

