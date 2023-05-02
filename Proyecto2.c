#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/sysinfo.h>


//Constantes Globales
#define num_threads_pc get_nprocs()


// variables globales


int  mode_password;
unsigned char* password;

unsigned char* decode_password_out;

int len_password ;
int len_real_password=0;

float Total_Time_Decode;
float time_threads;
float init_time;
float final_time;
int thread_WIN = 0;
int flag_thread[16];

int BANDERA = 1;
int BANDERA2 = 1;

char Array_Num[20] = {48,0,49,0,50,0,51,0,52,0,53,0,54,0,55,0,56,0,57,0};

char Array_Num_Min[72] = {48,0,49,0,50,0,51,0,52,0,53,0,54,0,55,0,56,0,57,0,97,0,98,0,99,0,100,0,101,0,102,0,103,0,104,0,105,0,106,0,107,0,108,0,
						  109,0,110,0,111,0,112,0,113,0,114,0,115,0,116,0,117,0,118,0,119,0,120,0,121,0,122,0};

char Array_Num_Min_May[124] = {48,0,49,0,50,0,51,0,52,0,53,0,54,0,55,0,56,0,57,0,65,0,66,0,67,0,68,0,69,0,70,0,71,0,72,0,73,0,74,0,75,0,76,0,77,0,
							  78,0,79,0,80,0,81,0,82,0,83,0,84,0,85,0,86,0,87,0,88,0,89,0,90,0,97,0,98,0,99,0,100,0,101,0,102,0,103,0,104,0,105,0,
							  106,0,107,0,108,0,109,0,110,0,111,0,112,0,113,0,114,0,115,0,116,0,117,0,118,0,119,0,120,0,121,0,122,0};

char Array_Num_Min_May_Car[188] = {33,0,34,0,35,0,36,0,37,0,38,0,39,0,40,0,41,0,42,0,43,0,44,0,45,0,46,0,47,0,48,0,49,0,50,0,51,0,52,0,53,0,54,0,
								  55,0,56,0,57,0,58,0,59,0,60,0,61,0,62,0,63,0,64,0,65,0,66,0,67,0,68,0,69,0,70,0,71,0,72,0,73,0,74,0,75,0,76,0,
								  77,0,78,0,79,0,80,0,81,0,82,0,83,0,84,0,85,0,86,0,87,0,88,0,89,0,90,0,91,0,92,0,93,0,94,0,95,0,96,0,97,0,98,0,
								  99,0,100,0,101,0,102,0,103,0,104,0,105,0,106,0,107,0,108,0,109,0,110,0,111,0,112,0,113,0,114,0,115,0,116,0,117,0,
								  118,0,119,0,120,0,121,0,122,0,123,0,124,0,125,0,126,0};

int len_Array_Num = 20;
int	len_Array_Num_Min = 72;
int	len_Array_Num_Min_May = 124;
int	len_Array_Num_Min_May_Car = 188;

FILE *f; //se declara tipo fichero

struct struct_thread {
	int hilo;
	int activo;
	char character;
	float time;

};


void introduction(){
	printf("\n\n\n");
	printf("________________________________________________\n");
	printf("|                                              |\n");
	printf("|        Arquitectura de Computadores I        |\n");
	printf("|       Proyecto2 Procesamiento Paralelo       |\n");
	printf("|                 Estudiantes:                 |\n");
	printf("|              Alvaro Sossa Rojas              |\n");
	printf("|             Genesis Mendez Castro            |\n");
	printf("|               II semestre 2021               |\n");
	printf("|                                              |\n");
	printf("|     ....Presione enter para continuar....    |\n");
	printf("|______________________________________________|\n");
	getchar();
	system("clear");
}


void read_specific_line(int line){ // Poder acceder a una linea especifica del archivo 
	int count=line-1;
	fseek(f, 0, SEEK_SET);
	work:
		if (count>0){
			while (fgetc(f) != '\n');
			count--;
			goto work;
		}
}

void read_file(){ // Función que lee el documento txt y verifica que las entradas estén correctas.
	f = fopen("file_password.txt", "r"); //abre el archivo como modo de lectura
	char count_char;
	
		if (f==NULL){
			printf("No se ha podido abrir el archivo. \n");
			exit(1);
		}
	
	read_specific_line(1);	
	//mode_password=fgetc(f)-48;
	fscanf(f,"%d",&mode_password);

	read_specific_line(2);	
	fscanf(f,"%d",&len_password);
	
	read_specific_line(3);
		while(count_char != EOF){ // Determina el tamaño real de contraseña ingresada
			count_char = fgetc(f);
			len_real_password++;
		}
		len_real_password = len_real_password-2; // Se le resta 2 debido a que tambien se toma en cuenta los caracteres '\0' y '\n'
		//printf("Tamaño real: %d\n", len_real_password);
	read_specific_line(3);	
	password=malloc(sizeof(int)*len_real_password);
	fgets(password, len_real_password+1, f);
	
	fclose(f);

	//Datos de contraseña 
	printf("\n\n\n");
	printf(" _________________________________________________ \n");
	printf("                                                   \n");
	printf("      Contraseña a descifrar:  %s                  \n", password);
	printf("      Modo de contraseña:      %d                  \n", mode_password);
	printf("      Tamaño de contraseña:    %d                  \n", len_password);
	printf("  ¡¡..Lectura de Archivo completado con exito..!!  \n" );
	printf("  ¡¡..Se procede a verificar datos ingresados..!!  \n" );
	printf("                                                   \n");
	printf("        ....Presione enter para continuar....      \n");
	printf(" _________________________________________________ \n");
	getchar();
	system("clear");

	if((1 <= len_password <= 10) && (1 <= len_real_password <= 10)){

		//Verificamos coincidencia entre el tamaño real de la contraseña y el parámetro len
		if(len_real_password==len_password){
		
			//Comprobando el formato de la contraseña
			if (mode_password==1){ //Verificamos el modo 1 de contraseña y si la contraseña lo cumple
				int t;
				int flag_number=1; 
				for (int i=0; i <=len_password-1; i++){
					t=password[i];
					
					if (t>=48 && t<=57){
						flag_number=1;
					}
					else {
						flag_number=0;
						break;
					}		
				}
				
				if(flag_number==1){ // Se aprueba
					printf("\n\n\n");
					printf(" ___________________________________________________________ \n");
					printf("|                                                           |\n");
					printf("|                .......... Exito ..........                |\n");
					printf("| Formato de contraseña coincide con lo especificado.       |\n");
					printf("| Se procede a realizar la decodificación de la contraseña. |\n");
					printf("|                                                           |\n");
					printf("|           ....Presione enter para comenzar....            |\n");
					printf("|___________________________________________________________|\n");
					getchar();
					return NULL;
					//hilos(mode_password);
				}
				else {
					printf("\n\n\n");
					printf(" ________________________________________________________________________ \n");
					printf("|                                                                        |\n");
					printf("|                       .......... Error ..........                      |\n");
					printf("| Formato de contraseña no coincide con lo especificado.                 |\n");
					printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
					printf("|________________________________________________________________________|\n");
					exit(0);
				}
			}
			
			else if (mode_password==2){  //Verificamos el modo 2 de contraseña y si la contraseña lo cumple
				int t;
				int flag_number=0;
				int flag_char_min=0;
				for (int i=0; i <=len_password-1; i++){
					t = password[i];

					if (t>=48 && t<=57){
						flag_number=1;
					}
					else if(t>=97 && t<= 122){
						flag_char_min=1;
					}
					else {
						flag_number=0;
						flag_char_min=0;
						break;
					}
				}
				
				if(flag_number==1 || flag_char_min==1){// Se aprueba
					printf("\n\n\n");
					printf(" ___________________________________________________________ \n");
					printf("|                                                           |\n");
					printf("|                .......... Exito ..........                |\n");
					printf("| Formato de contraseña coincide con lo especificado.       |\n");
					printf("| Se procede a realizar la decodificación de la contraseña. |\n");
					printf("|                                                           |\n");
					printf("|           ....Presione enter para comenzar....            |\n");
					printf("|___________________________________________________________|\n");
					getchar();
					return NULL;
					//hilos(mode_password);
				}
				else {
					printf("\n\n\n");
					printf(" ________________________________________________________________________ \n");
					printf("|                                                                        |\n");
					printf("|                       .......... Error ..........                      |\n");
					printf("| Formato de contraseña no coincide con lo especificado.                 |\n");
					printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
					printf("|________________________________________________________________________|\n");
					exit(0);
				}
			}
			
			else if (mode_password==3){ //Verificamos el modo 3 de contraseña y si la contraseña lo cumple
				int t;
				int flag_number=0;
				int flag_char_min=0;
				int flag_char_may=0;
				for (int y=0; y <=len_password-1; y++){
					t=password[y];
					if (t>=48 && t<=57){
						flag_number=1;
					}
					else if(t>=97 && t<= 122){
						flag_char_min=1;
					}
					
					else if(t>=65 && t<= 90){
						flag_char_may=1;
					}
					
					else {
						flag_number=0;
						flag_char_may=0;
						flag_char_min=0;
						break;
					}
				}
				if (flag_number==1 || flag_char_min==1 || flag_char_may==1){ // Se aprueba
					printf("\n\n\n");
					printf(" ___________________________________________________________ \n");
					printf("|                                                           |\n");
					printf("|                .......... Exito ..........                |\n");
					printf("| Formato de contraseña coincide con lo especificado.       |\n");
					printf("| Se procede a realizar la decodificación de la contraseña. |\n");
					printf("|                                                           |\n");
					printf("|           ....Presione enter para comenzar....            |\n");
					printf("|___________________________________________________________|\n");
					getchar();
					return NULL;
					//hilos(mode_password);
				}
				else{
					printf("\n\n\n");
					printf(" ________________________________________________________________________ \n");
					printf("|                                                                        |\n");
					printf("|                       .......... Error ..........                      |\n");
					printf("| Formato de contraseña no coincide con lo especificado.                 |\n");
					printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
					printf("|________________________________________________________________________|\n");
					exit(0);
				}
			}
			
			else if (mode_password==4){   //Verificamos el modo 4 de contraseña y si la contraseña lo cumple
				int t;
				int flag_n=1;
				for (int y=0; y <=len_password-1; y++){
					t=password[y];
					if (t>=33 && t<=126){
						flag_n=1;
					}
					else {
						flag_n=0;

						printf("\n\n\n");
						printf(" ________________________________________________________________________ \n");
						printf("|                                                                        |\n");
						printf("|                       .......... Error ..........                      |\n");
						printf("| Formato de contraseña no coincide con lo especificado.                 |\n");
						printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
						printf("|________________________________________________________________________|\n");
						exit(0);
					}
				}
				if(flag_n==1){ // Se aprueba
					printf("\n\n\n");
					printf(" ___________________________________________________________ \n");
					printf("|                                                           |\n");
					printf("|                .......... Exito ..........                |\n");
					printf("| Formato de contraseña coincide con lo especificado.       |\n");
					printf("| Se procede a realizar la decodificación de la contraseña. |\n");
					printf("|                                                           |\n");
					printf("|           ....Presione enter para comenzar....            |\n");
					printf("|___________________________________________________________|\n");
					getchar();
					return NULL;
					//hilos(mode_password);
				}
			}
			
			else {
				printf("\n\n\n");
				printf(" ________________________________________________________________________ \n");
				printf("|                                                                        |\n");
				printf("|                      .......... Error ..........                       |\n");
				printf("| Modo de contraseña no valida.                                          |\n");
				printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
				printf("|________________________________________________________________________|\n");
				exit(0);
			}

		}
		else {
			printf("\n\n\n");
			printf(" _____________________________________________________________________________ \n");
			printf("|                                                                             |\n");
			printf("|                         .......... Error ..........                         |\n");
			printf("| El tamaño especificado NO coincide con el tamaño de contraseña a descifrar. |\n");
			printf("| Por favor revisar y modificar el archivo con los parametros correctos.      |\n");
			printf("|_____________________________________________________________________________|\n");
			exit(0);
		}
	}
	else {
		printf("\n\n\n");
		printf(" ________________________________________________________________________ \n");
		printf("|                                                                        |\n");
		printf("|                       .......... Error ..........                      |\n");
		printf("| El tamaño de la contraseña debe de ser de 1 a 10 carácteres.           |\n");
		printf("| Por favor revisar y modificar el archivo con los parametros correctos. |\n");
		printf("|________________________________________________________________________|\n");
		exit(0);
	}
}


void* decode(void* arg){

	struct struct_thread *d_thread = (struct struct_thread *) arg;
	char decode_password[len_password];
	
	flag_thread[d_thread->hilo] = 1;
	decode_password[0]= d_thread->character;

	int array_temp[len_password];
	for(int i = 0; i<len_password; i++){
		array_temp[i] = 0;
	}
	switch(mode_password){
			
		case(1):{
						
			for(int i = 1; i<len_password; i++){
				decode_password[i] = Array_Num[0];
			}

			while(BANDERA != 0){
				array_temp[len_password-1] = array_temp[len_password-1]+2;
				if(array_temp[len_password-1] == (len_Array_Num)){
					array_temp[len_password-1] = 0;
					
				}
				decode_password[len_password-1] = Array_Num[array_temp[len_password-1]];

				int p;
				int band_fin;				
				
	            //printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
				BANDERA = strcmp(decode_password, password);
				if(BANDERA == 0){
					BANDERA = 0;
					BANDERA2 = 0;
					decode_password_out = decode_password;
					final_time=clock();
					Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
					thread_WIN = d_thread->hilo;
					pthread_exit(NULL);
					return;
				}

				for(int i = 1; i< len_password; i++){
					p = 0;
					band_fin = 0;
					for(int j = i; j < len_password; j++){

						if(decode_password[j] == Array_Num[len_Array_Num-2]){
							band_fin++;
						
						}
						if(band_fin == (len_password-i)){
							p= 1;
						}
					}

					if((decode_password[i]== Array_Num[len_Array_Num-2]) && p == 1){
						for (int j = i; j< len_password; j++){
							array_temp[j] = 0;
							decode_password[j]= Array_Num[array_temp[j]];
						}

						array_temp[i-1] = array_temp[i-1]+2;
						decode_password[i-1] = Array_Num[array_temp[i-1]];
						
						if(array_temp[0] > 0){		//Cuando no lo encuentro

							flag_thread[d_thread->hilo] = 0;
							pthread_exit(NULL);
							return;	
						}
					}

					//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
					BANDERA = strcmp(decode_password, password);
					if(BANDERA == 0){
						BANDERA2 = 0;
						BANDERA = 0;
						decode_password_out = decode_password;
						thread_WIN = d_thread->hilo;
                        final_time=clock();	
                    	Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
						pthread_exit(NULL);
						return;
					}
				}
			}
		break;
		}
		case(2):{
		
			for(int i = 1; i<len_password; i++){
				decode_password[i] = Array_Num_Min[0];
			}

			while(BANDERA != 0){
				array_temp[len_password-1] = array_temp[len_password-1]+2;
				if(array_temp[len_password-1] == (len_Array_Num_Min)){
					array_temp[len_password-1] = 0;
					
				}
				decode_password[len_password-1] = Array_Num_Min[array_temp[len_password-1]];
				
				int p;
				int band_fin;
				
				//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
				BANDERA = strcmp(decode_password, password);
				if(BANDERA == 0){
					BANDERA = 0;
					BANDERA2 = 0;
					decode_password_out = decode_password;
					final_time=clock();
					Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
					thread_WIN = d_thread->hilo;
					pthread_exit(NULL);
					return;
				}

				for(int i = 1; i< len_password; i++){
				
					p = 0;
					band_fin = 0;
					for(int j = i; j < len_password; j++){
					
						if(decode_password[j] == Array_Num_Min[len_Array_Num_Min-2]){
							band_fin++;
						
						}
						if(band_fin == (len_password-i)){
							p= 1;
						}
					}
					
					if((decode_password[i]== Array_Num_Min[len_Array_Num_Min-2]) && p == 1){
						for (int j = i; j< len_password; j++){
							array_temp[j] = 0;
							decode_password[j]= Array_Num_Min[array_temp[j]];
						}



						array_temp[i-1] = array_temp[i-1]+2;
						decode_password[i-1] = Array_Num_Min[array_temp[i-1]];
						
						if(array_temp[0] > 0){		//Cuando no lo encuentro
							d_thread->activo = 0;
							d_thread->time = Total_Time_Decode;
							flag_thread[d_thread->hilo] = 0;
							pthread_exit(NULL);
							return 0;	
						}
					}

					//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
					BANDERA = strcmp(decode_password, password);
					if(BANDERA == 0){
						BANDERA = 0;
						BANDERA2 = 0;
						decode_password_out = decode_password;
						final_time=clock();
						Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
						thread_WIN = d_thread->hilo;
						pthread_exit(NULL);
						return;
					}
				}
			}
		break;
		}
		case(3):{
		
			for(int i = 1; i<len_password; i++){
				decode_password[i] = Array_Num_Min_May[0];
			}

			while(BANDERA != 0){
				array_temp[len_password-1] = array_temp[len_password-1]+2;
				if(array_temp[len_password-1] == (len_Array_Num_Min_May)){
					array_temp[len_password-1] = 0;
					
				}
				decode_password[len_password-1] = Array_Num_Min_May[array_temp[len_password-1]];

				int p;
				int band_fin;
				
				//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
				BANDERA = strcmp(decode_password, password);
				if(BANDERA == 0){
					BANDERA = 0;
					BANDERA2 = 0;
					decode_password_out = decode_password;
					final_time=clock();
					Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
					thread_WIN = d_thread->hilo;
					pthread_exit(NULL);
					return;
				}

				for(int i = 1; i< len_password; i++){
				
					p = 0;
					band_fin = 0;
					for(int j = i; j < len_password; j++){
					
						if(decode_password[j] == Array_Num_Min_May[len_Array_Num_Min_May-2]){
							band_fin++;
						
						}
						if(band_fin == (len_password-i)){
							p= 1;
						}
					}

					if((decode_password[i]== Array_Num_Min_May[len_Array_Num_Min_May-2]) && p == 1){
						for (int j = i; j< len_password; j++){
							array_temp[j] = 0;
							decode_password[j]= Array_Num_Min_May[array_temp[j]];
						}



						array_temp[i-1] = array_temp[i-1]+2;
						decode_password[i-1] = Array_Num_Min_May[array_temp[i-1]];
						
						if(array_temp[0] > 0){		//Cuando no lo encuentro
							d_thread->activo = 0;
							d_thread->time = Total_Time_Decode;
							flag_thread[d_thread->hilo] = 0;
							pthread_exit(NULL);
							return 0;	
						}
					}

					//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
					BANDERA = strcmp(decode_password, password);
					if(BANDERA == 0){
						BANDERA = 0;
						BANDERA2 = 0;
						decode_password_out = decode_password;
						final_time=clock();
						Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
						thread_WIN = d_thread->hilo;
						pthread_exit(NULL);
						return;
					}
				}
			}
			
		break;
		}
		case(4):{
		
			for(int i = 1; i<len_password; i++){
				decode_password[i] = Array_Num_Min_May_Car[0];
			}

			while(BANDERA != 0){
				array_temp[len_password-1] = array_temp[len_password-1]+2;
				if(array_temp[len_password-1] == (len_Array_Num_Min_May_Car)){
					array_temp[len_password-1] = 0;
					
				}
				decode_password[len_password-1] = Array_Num_Min_May_Car[array_temp[len_password-1]];
				
				int p;
				int band_fin;
				
				//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
				BANDERA = strcmp(decode_password, password);
				if(BANDERA == 0){
					BANDERA = 0;
					BANDERA2 = 0;
					decode_password_out = decode_password;
					final_time=clock();
					Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
					thread_WIN = d_thread->hilo;
					pthread_exit(NULL);
					return;
				}

				for(int i = 1; i< len_password; i++){
				
					p = 0;
					band_fin = 0;
					for(int j = i; j < len_password; j++){
					
						if(decode_password[j] == Array_Num_Min_May_Car[len_Array_Num_Min_May_Car-2]){
							band_fin++;
						
						}
						if(band_fin == (len_password-i)){
							p= 1;
						}
					}

					if((decode_password[i]== Array_Num_Min_May_Car[len_Array_Num_Min_May_Car-2]) && p == 1){
						for (int j = i; j< len_password; j++){
							array_temp[j] = 0;
							decode_password[j]= Array_Num_Min_May_Car[array_temp[j]];
						}



						array_temp[i-1] = array_temp[i-1]+2;
						decode_password[i-1] = Array_Num_Min_May_Car[array_temp[i-1]];
						
						if(array_temp[0] > 0){		//Cuando no lo encuentro
							d_thread->activo = 0;
							d_thread->time = Total_Time_Decode;
							flag_thread[d_thread->hilo] = 0;
							pthread_exit(NULL);
							return 0;	
						}


					}
					
					//printf("decode_password: %s ,password:  %s ,Hilo: %i,  BANDERA:    %i,   C: %c.\n", decode_password, password, d_thread->hilo,BANDERA,d_thread->character);
					BANDERA = strcmp(decode_password, password);
					if(BANDERA == 0){
						BANDERA = 0;
						BANDERA2 = 0;
						decode_password_out = decode_password;
						final_time=clock();
						Total_Time_Decode=(final_time-init_time)/CLOCKS_PER_SEC;
						thread_WIN = d_thread->hilo;
						pthread_exit(NULL);
						return;
					}
				}
			}
		break;
		}
		default:{

		        break;
		}

	}
	
return;	
}


char character (){

	int ok = 0;
	switch(mode_password){

		case(1):{	//Sólo numeros
		
			srand(time(NULL));
			int ram = rand()%(len_Array_Num-1);

			if (ram %2 !=0) 
				ram = ram+1;
			if(ram == (len_Array_Num-1))
				ram = ram-1;
			
			
			for (int i = ram; i < len_Array_Num; i= i+2){
				
				if((int)Array_Num[i+1] == 0){
					char character = Array_Num[i];
					
					Array_Num[i+1] = 1;
					return (character);
				}
			}

			for (int i = ram - 2; i >= 0; i= i-2){
				char character = Array_Num[i];
				
				if((int)Array_Num[i+1] == 0){
					char character = Array_Num[i];
					
					Array_Num[i+1] = 1;
					return (character);
				}
			}

			return(-1);			
		break;
		}
		case(2):{
			srand(time(NULL));
			int ram = rand()%(len_Array_Num_Min-1);

			if (ram %2 !=0) 
				ram = ram+1;
			if(ram == (len_Array_Num_Min-1))
				ram = ram-1;
			
			for (int i = ram; i < len_Array_Num_Min; i= i+2){
				
				if((int)Array_Num_Min[i+1] == 0){
					char character = Array_Num_Min[i];
					
					Array_Num_Min[i+1] = 1;
					return (character);
				}
			}

			for (int i = ram - 2; i >= 0; i= i-2){
				char character = Array_Num_Min[i];
				
				if((int)Array_Num_Min[i+1] == 0){
					char character = Array_Num_Min[i];

					Array_Num_Min[i+1] = 1;
					return (character);
				}
			}
			return(-1);	

		break;	
		}
		case(3):{
			
			srand(time(NULL));
			int ram = rand()%(len_Array_Num_Min_May-1);

			if (ram %2 !=0) 
				ram = ram+1;
			if(ram == (len_Array_Num_Min_May-1))
				ram = ram-1;
			
			for (int i = ram; i < len_Array_Num_Min_May; i= i+2){
				
				if((int)Array_Num_Min_May[i+1] == 0){
					char character = Array_Num_Min_May[i];
					
					Array_Num_Min_May[i+1] = 1;
					return (character);
				}
			}

			for (int i = ram - 2; i >= 0; i= i-2){
				char character = Array_Num_Min_May[i];
				
				if((int)Array_Num_Min_May[i+1] == 0){
					char character = Array_Num_Min_May[i];
					
					Array_Num_Min_May[i+1] = 1;
					return (character);
				}
			}
			return(-1);	

		break;	
		}
		case(4):{
			srand(time(NULL));
			int ram = rand()%(len_Array_Num_Min_May_Car-1);
			
			if (ram %2 !=0) 
				ram = ram+1;
			if(ram == (len_Array_Num_Min_May_Car-1))
				ram = ram-1;
			
			
			for (int i = ram; i < len_Array_Num_Min_May_Car; i= i+2){
				
				if((int)Array_Num_Min_May_Car[i+1] == 0){
					char character = Array_Num_Min_May_Car[i];
					
					Array_Num_Min_May_Car[i+1] = 1;
					return (character);
				}
			}

			for (int i = ram - 2; i >= 0; i= i-2){
				char character = Array_Num_Min_May_Car[i];
				
				if((int)Array_Num_Min_May_Car[i+1] == 0){
					char character = Array_Num_Min_May_Car[i];
					
					Array_Num_Min_May_Car[i+1] = 1;
					return (character);
				}
			}
			return(-1);

		break;	
		}
		default:{
		        break;
		}
	

	}
}



int main() {
	system("clear");

	introduction();
	read_file();

	//Inicializa Hilos y Estructura de Hilos
	pthread_t threads[num_threads_pc];
	struct struct_thread s_threads[num_threads_pc];
	
	//Inicializa Listas y banderas
	for (int i=0; i < num_threads_pc; i++){
		s_threads[i].activo = 0;
		s_threads[i].hilo =i;
		s_threads[i].character = 0;
		s_threads[i].time = 0;
	}
	for (int i = 0; i < num_threads_pc; ++i)
	{
		flag_thread[i] = 0;
	}

	char c;
	printf("\n\n\n");

	init_time = clock();

	while(BANDERA2 != 0){
		for(int i= 0; i<num_threads_pc; i++){
			if(flag_thread[i] == 0){
				c = character();
				flag_thread[i]= 1;
				s_threads[i].character = c;
				s_threads[i].hilo = i;
				printf("hilo: %i con c: %c \n",s_threads[i].hilo,c);  //Este print nos indica el hilo que vamos a usar
				s_threads[i].activo = pthread_create(&threads[i], NULL, decode, &s_threads[i]);
			}
		}

	}
	printf("\n\n\n");
	printf(" __________________________________________________ \n");
	printf(" __________________________________________________ \n");
	printf("                                                    \n");
	printf("       Contraseña encontrada correctamente          \n");
	printf("                                                    \n");
	printf("         Contraseña a descifrar:  %s                \n", password);
	printf("         Contraseña obtenida:     %s                \n", decode_password_out);
	printf("         Hilo que encontró la contraseña: %i        \n", thread_WIN);
	printf("         Tiempo de ejecucion:    %f                 \n", Total_Time_Decode);
	printf(" __________________________________________________ \n");
	printf(" __________________________________________________ \n");
	printf("                                                    \n");
    printf("\n\n.........Salí del Código.........\n\n");
return 0;
}











