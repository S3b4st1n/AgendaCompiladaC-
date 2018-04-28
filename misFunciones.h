//#############################################################################
// ARCHIVO             : main.cpp
// AUTOR/ES            : Mansilla Francisco
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 31/08/2017.
// ULTIMA ACTUALIZACION: 18/09/2017.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef MISFUNCIONES_H_INCLUDED
#define MISFUNCIONES_H_INCLUDED
#include "menu.h"
#include "registroPersonas.h"
#include "registroPersonasEncontradas.h"
#include "registroTelefonos.h"
//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;
//****************************************************************************



////===========================================================================
//// FUNCION   :bool buscar(int opc).
//// ACCION    : busca de forma generica un contacto por Apellido,Nombre o Alias
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
bool buscar(int opc)
{
    FILE *arch_per = fopen(ruta_persona, "rb+" );
    persona per;
    char sub_cadena[30];
    bool retorno = false;
    int encontrado = 0;
    FILE *arch_per_encotradas = fopen(ruta_per_encontradas, "wb" );

    mostrar_opcion_busqueda(opc);
    sys::getline(sub_cadena, 30);
    sys::cls();


    while(fread(&per, sizeof(persona),1,arch_per))
    {
        if(per.eliminado != true)
        {
            encontrado = 0;

            switch (opc)
            {
            case 1:
            {
                if ( buscar_subcadena(per.apellido, sub_cadena ) != -1 )
                {
                    mostrarContacto(per);
                    retorno = true;
                    encontrado = 1;
                }
            }
            break;

            case 2:
            {
                if ( buscar_subcadena(per.nombre, sub_cadena ) != -1 )
                {
                    mostrarContacto(per);
                    retorno = true;
                    encontrado = 1;
                }
            }
            break;

            case 3:
            {
                if ( buscar_subcadena(per.alias, sub_cadena ) != -1 )
                {
                    mostrarContacto(per);
                    retorno = true;
                    encontrado = 1;
                }
            }
            break;

            default:
            {

            } break;
            }

            if (encontrado  == 1)
                fwrite(&per, sizeof(per), 1, arch_per_encotradas);
        }

    }

    cin.get();

    fclose(arch_per);
    fclose(arch_per_encotradas);

    return retorno;
}

////===========================================================================
//// FUNCION   : void  contar_ID().
//// ACCION    : Contador para ID_telefono y ID_persona.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void contar_ID()
{
    FILE *arch_per;
    arch_per = fopen(ruta_persona,"ab");
    if(arch_per == NULL)
        exit(99);
    fseek(arch_per,0,SEEK_END);
    ID_per = ftell(arch_per) / sizeof(persona);
    fclose(arch_per);

    if (ID_per == 0)
        ID_per = 1;
    else
        ID_per++;

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"ab");
    if(arch_tel == NULL)
        exit(98);
    fseek(arch_tel,0,SEEK_END);
    ID_tel = ftell(arch_tel) / sizeof(telefono);
    fclose(arch_tel);

    if (ID_tel == 0)
        ID_tel = 1;
    else
        ID_tel++;

}

//=============================================================================
// FUNCION   : bool esNumero(char* cadena)
// ACCION    : valida si la cadena ingresada es numero.
// PARAMETROS: char* cadena
// DEVUELVE  : TRUE si esta dentro del rango, FALSE si no lo cumple
//-----------------------------------------------------------------------------
bool esNumero(char* cadena)//* pasar por puntero porque es una cadena/vector.
{
    int i = 0;
    while(cadena[i] != '\0' || strlen(cadena) > 1) //'\0' fin de cadena.
    {
        if(cadena[i] < '1' && cadena[i] > '9')
            return false;
        i++;
    }
    return true;
}

////===========================================================================
//// FUNCION   : void mostrar_contactos().
//// ACCION    :
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrar_contactos(){
    int cont = 0;
    sys::cls();

    FILE *arch_per;
    arch_per = fopen(ruta_persona,"rb");
    if(arch_per == NULL)
        exit(99);
    persona per;
    while( fread(&per, sizeof(persona), 1, arch_per)){

        if(!per.eliminado){
            mostrarContacto(per);
            mostrarTelefonosByContacto(per.id_persona);
        }
        cout<< " ==================================="<<endl<<endl;
        cont ++;
        if(cont == 5){
            cin.get();
            sys::cls();
            cont = 0;
        }
    }
    fclose(arch_per);
    cin.get();
}

//===========================================================================
// FUNCION   : void mostrar_opcion_busqueda(int opc).
// ACCION    : Muestra en pantalla el submenu 1.
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void mostrar_opcion_busqueda(int opc)
{
    switch (opc)
    {
        case 1:
            cout<<"Ingrese Apellido:  ";
        break;

        case 2:
            cout<<"Ingrese Nombre:  ";
        break;

        case 3:
            cout<<"Ingrese Alias:  ";
        break;
    }
}

//=============================================================================
// FUNCION : bool esMinuscula(char caracter)
// ACCION : averigua si el caracter ya es minuscula o no
// PARAMETROS: caracter
// DEVUELVE : tipo --> bool
//-----------------------------------------------------------------------------
bool esMinuscula (char caracter)
{
    int ascii = caracter;
    if(ascii > 93 && ascii < 123)
        return true;
    else
        return false;
}

//=============================================================================
// FUNCION : void strToUpper(char * cadena)
// ACCION : convierte una cadena a mayúsculas.
// PARAMETROS: cadena
// DEVUELVE : tipo --> void
//-----------------------------------------------------------------------------
void strToUpper(char * cadena)
{
    int i = 0;
    int ascii = 0;

    while(cadena[i] != '\0')
    {
        if(esMinuscula(cadena[i]))
        {
            ascii = cadena[i] - 32;
            cadena[i] = ascii;
            ascii = 0;
        }
        i++;
    }
}

////===========================================================================
//// FUNCION   : CheckSubstring(char *firstString, char *secondString)
//// ACCION    :
//// PARAMETROS:
//// DEVUELVE  : -1 si no encuentra la subcadena
////---------------------------------------------------------------------------
bool CheckSubstring(char *firstString, char *secondString){

    strToUpper(firstString);
    strToUpper(secondString);

    if(strlen(secondString) > strlen(firstString))
        return false;

    for (int i = 0; i < strlen(firstString); i++){
        int j = 0;
        if(firstString[i] == secondString[j]){
            while (firstString[i] == secondString[j] && j < strlen(secondString)){
                j++;
                i++;
            }

            if (j == strlen(secondString))
                    return true;
        }
    }
    return false;
}
////===========================================================================
//// FUNCION   : int buscar_subcadena(char* persona_nombre, char* subcadena).
//// ACCION    :
//// PARAMETROS:
//// DEVUELVE  : -1 si no encuentra la subcadena
////---------------------------------------------------------------------------
int buscar_subcadena(char* persona_nombre, char* subcadena)
{
    int i = 0;
    int j = 0;
    int retorno = 0;

    char per_nombre[50], sub_cadena[50];

    strcpy(per_nombre, persona_nombre);
    strcpy(sub_cadena, subcadena);

    strToUpper(per_nombre);
    strToUpper(sub_cadena);

    while (per_nombre[i] != '\0')
    {
        if(per_nombre[i] == sub_cadena[j])
        {
            if ( retorno == -1 )
                retorno = i;

            j++;
        }
        else
        {
            if(sub_cadena[j] != '\0')
            {
                retorno = -1;
                j = 0;
            }
        }

        i++;
    }

    if (per_nombre[i] == '\0' && sub_cadena[j] != '\0')
        retorno = -1;

    return retorno;
}

////===========================================================================
//// FUNCION   : void preguntar_id().
//// ACCION    : busca sobre los contactos guardados a partir de la funcion generica void buscar()
//// PARAMETROS: opc(eliminar o modificar).
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void preguntar_id(int opc)
{
    FILE *arch_per_encotradas = fopen(ruta_per_encontradas, "rb" );
    if(arch_per_encotradas == NULL)
        exit(97);
    persona per;
    int id_contacto;
    int encontrar = 2;

    cout<< "Ingrese el ID dentro de la lista resultado (cero para volver al menu anterior)"<<endl;
    cin>> id_contacto;
    cin.ignore();

    while (encontrar == 2 && id_contacto != 0)
    {
        while(fread (&per, sizeof(persona), 1, arch_per_encotradas) && (id_contacto == per.id_persona))
        {
            sys::cls();
            mostrarContacto(per);

            cin.get();

            if (opc == 3)
                eliminar_registro(per);
            else
                modificar_registro(per);

            encontrar = 1;
            break;
        }
        if( encontrar == 2)
        {
            sys::cls();
            cout<< "El ID ingresado no esta en la lista de encontrados:  "<<endl<<endl;
            cout<< "Ingrese el ID dentro de la lista resultado  (cero para volver al menu anterior)"<<endl;
            cin>> id_contacto;
            cin.ignore();
        }
    }
    fclose(arch_per_encotradas);
}



//===========================================================================
// FUNCION   : void mostrar_contactosEncontrados(persona per)
// ACCION    : Muestra contactos encontrados
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void mostrar_contactosEncontrados()
{
    FILE *arch_per_enc;
    arch_per_enc = fopen(ruta_per_encontradas,"rb");
    if(arch_per_enc == NULL)
        exit(97);
    persona per;

    while(fread(&per, sizeof(persona), 1, arch_per_enc))
    {
            cout<< " ==================================="<<endl;
            cout<< "           ID CONTACTO: "<< per.id_persona << endl;
            cout<< " ==================================="<<endl;
            cout<< " NOMBRE  : " << per.nombre << endl;
            cout<< " APELLIDO: " << per.apellido << endl;
            cout<< " CORREO  : " << per.email << endl;
            cout<< " APODO   : " << per.alias << endl;

            FILE *arch_tel;
            arch_tel = fopen(ruta_telefono,"rb");
            if(arch_tel == NULL)
                exit(98);
            telefono tel;

            while(fread(&tel, sizeof(telefono), 1, arch_tel))
            {
                if (tel.eliminado != true)
                {
                    if(per.id_persona == tel.id_persona)
                    {
                        cout<< " -----------------------------------"<<endl;
                        cout<< " ID TELEFONO: "<< tel.id_telefono << endl;
                        cout<< " -----------------------------------"<<endl;
                        cout<< " TELEFONO TIPO: " << tel.tipo << endl;
                        cout<< " NUMERO       : " << tel.numero << endl;
                    }
                }

            }
            fclose(arch_tel);
            cout<< " ==================================="<<endl<<endl;
            //cont ++;
        }
    fclose(arch_per_enc);
}

#endif // MISFUNCIONES_H_INCLUDED
