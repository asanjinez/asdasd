/*
 * iMongoStore.h
 *
 *  Created on: 25 may. 2021
 *      Author: utnso
 */

#ifndef IMONGOSTORE_H_
#define IMONGOSTORE_H_

#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <commons/bitarray.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
#include <shared/conexion.h>


//LOGS, CONFIGS, TRIPULANTE, SABOTAJE Y PATOTA
typedef struct{
	uint8_t idSabotaje;
	uint8_t posx;
	uint8_t posy;
} Sabotaje;

t_log* iniciar_logger(char* logger_path);
t_config* leer_config(char* config_path);

//VARIABLES GLOBALES
t_config *mongoStore_config;
t_config *conexion_config;
t_log *logger;
t_list* blocks_used;

char* IP;
char* logger_path_mongostore;
char* punto_montaje;

int bloques;
int tamanio_bloque;
int tiempoSincro;
//Falta posiciones sabotaje

t_bitarray* bitmap;
int tamanioBitmap;

char* ruta_metadata;

void* copiaBlock;
void* superbloque;

int bloquesDelSistema;
int sabotaje_actual=1;
int size_o=0;
int size_c=0;
int size_b=0;

pthread_mutex_t mutexEscrituraBloques;

//VARIABLES GLOBALES

//INICIALIZACION FILE SYSTEM
void inicializar_carpetas();
void nueva_carpeta(char *nueva_carpeta);
void crear_archivo_files();
void crear_metadata(char* archivo, char* valor);
void nuevo_archivo_metadata(char* nuevo_archivo);
void escribir_en_bitacora(int idTripulante, char* texto);
void crear_superbloque();
int verificar_existencia(char* nombre_archivo);
void leer_files();
void inicializar_bloques();
void arreglar_sabotaje(void);
//INICIALIZACION FILE SYSTEM
void interrupt_handler(int signal);
void generar_bitacora(int idTripulante);
void* atender_mensaje(int cliente);
void agregarCaracter(int cantidad, char caracter);
void escribirEnBloque(int cantidad, char caracter, char* rutita);
void actualizar_metadata(char* valorBlocks, char* valorSize, char* valorBlockCount, char* ruta, char* caracter);
void actualizar_bitacora(char* valorBlocks, char* valorSize, char* valorBlockCount, char* ruta);
void eliminarCaracter(int cantidad, char caracter);
void eliminarEnBloque(int cantidad, char caracter, char* rutita);
int existeEnArray(char** array, char contenido);
_Bool esMetadataRecurso(char* rutini);

#endif /* IMONGOSTORE_H_ */
