#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

const char ruta_persona[] = "Datos.data";
const char ruta_telefono[] = "Telefono.data";
const char ruta_per_encontradas[] = "Personas_Encontradas.data";
int ID_per, ID_tel = 0;

struct persona
{
    int id_persona;
    char nombre[50];
    char apellido[50];
    char alias[50];
    char domicilio[50];
    char email[50];
    bool eliminado;
};

struct telefono
{
    int id_telefono;
    int id_persona;
    char tipo[50];
    char numero[10];
    bool eliminado;
};

//registro Telefono
void modificar_telefono(persona per);
bool guardarTel(telefono tel);
void cargarTelefono(int id_persona, telefono *tel);
void cargarTelefonos(int id_persona);
void mostrarTelefono(telefono tel);
void mostrarTelefonosByContacto(int id_persona);
void mostrarTelefonosEliminadosByContacto(int id_persona);
void eliminar_telefono(int id_telefono);
void editar_telefono(persona per, int id_telefono, int opcion, char* nuevo_numero, char* nuevo_tipo);
//misFunciones.h
void contar_ID();
bool esNumero(char* cadena);
void mostrar_contactos();
void mostrar_opcion_busqueda(int opc);
bool esMinuscula (char caracter);
void strToUpper(char * cadena);
bool CheckSubstring(char *firstString, char *secondString);
int buscar_subcadena(char* persona_nombre, char* subcadena);
void preguntar_id(int opc);
bool buscar(int opc);
void mostrar_contactosEncontrados();

//registroPersonas.h
void recuperar_contacto(int id_contacto);
void modificar_lista_contactos(persona per, int id_telefono);
void mostrar_contactos_eliminados();
void mostrar_contacto(persona per);
void modificar_contacto(persona per);
void modificar_registro(persona per);
void modificar_dato_persona(int opc, int id_persona, char* nuevo_dato);
void eliminar_registro(persona per);
bool guardar_persona(persona per);
void datos_persona(persona *per);
void cargar_persona();
void mostrarContacto(persona per);
void modificarContacto(int opc, int id_persona, char* nuevo_dato);
void opciones_modificacion_contacto(persona per);

//menu.h
void menu_mod_telefonos();
void menu_switch_mod_telefono();
void menu_mod();
void menu_eliminar_registro();
void despedida();
void ayuda();
void presentacion();
void mostrarMenuPrincipal();
void mostrar_Sub_Menu_buscar();
void sub_Menu_Buscar(int mod_bus);
void menuPrincipal();
void menu_mod_contacto();


#include "registroTelefonos.h"
#include "registroPersonas.h"
#include "misFunciones.h"
#include "menu.h"


#endif // PROTOTIPOS_H_INCLUDED
