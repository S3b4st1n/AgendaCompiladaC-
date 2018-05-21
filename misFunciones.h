//#############################################################################
// ARCHIVO             : misFunciones.h
// AUTOR/ES            : Mansilla Francisco & Mercado Sebastian
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 29/04/2018.
// ULTIMA ACTUALIZACION: 19/05/2018.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef MISFUNCIONES_H_INCLUDED
#define MISFUNCIONES_H_INCLUDED
#include "menu.h"
#include "registroPersonas.h"
#include "registroPersonasEncontradas.h"
#include "registroTelefonos.h"
#include <windows.h>
#include <conio.h>
//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;
//****************************************************************************

////===========================================================================
//// FUNCION   : void AltEnter()
//// ACCION    : MAXIM pantalla
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void AltEnter()
{
    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}

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
                    //cout<<"presione enter para continuar..."<<endl;
                    //cin.get();
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
                    cout<<"presione enter para continuar..."<<endl;
                    cin.get();
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
                    cout<<"presione enter para continuar..."<<endl;
                    cin.get();
                    retorno = true;
                    encontrado = 1;
                }
            }
            break;
            default:
            {

            } break;
            }

            if (encontrado == 1)
            {
                // fseek(arch_per, sizeof(persona)*(per.id_persona-1),SEEK_SET);
                fwrite(&per, sizeof(per), 1, arch_per_encotradas);
            }

        }

    }

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
    while(cadena[i] != '\0') //'\0' fin de cadena.
    {
        if(cadena[i] < '1' && cadena[i] > '9')
            return false;
        i++;
    }
    return true;
}

//=============================================================================
// FUNCION   : void inicializar_vector(int *vec,int tam)
// ACCION    : valida si la cadena ingresada es numero.
// PARAMETROS: int *vec,int tam
// DEVUELVE  : nada
//-----------------------------------------------------------------------------

void inicializar_vector(int *vec,int tam)
{
    for(int i=0; i<tam; i++)
    {
        vec[i]=0;
    }
}
////===========================================================================
//// FUNCION   : int retorna_encontrados(struct *persona per)
//// ACCION    :
//// PARAMETROS: struct persona per[][5], bool eliminado
//// DEVUELVE  : cantidad de contactos.
////---------------------------------------------------------------------------
int retorna_encontrados(struct persona per[][5], bool eliminado)
{
    int cont=0, i=0;
    FILE *arch_per;
    persona reg;
    arch_per = fopen(ruta_persona,"rb");
    if(arch_per == NULL)
        exit(99);
    while( fread(&reg, sizeof(persona), 1, arch_per))
    {
        if(reg.eliminado==eliminado)
        {
            per[i][cont]=reg;
            cont=cont+1;
            if(cont==5)
            {
                i=i+1;
                cont=0;
            }
        }
    }
    fclose(arch_per);
    return cont;
}

////===========================================================================
//// FUNCION   : void inicializar_matriz(struct persona per[][5], int fila, int columna)
//// ACCION    :
//// PARAMETROS: struct persona per[][5], int fila, int columna
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void inicializar_matriz(struct persona per[][5], int fila, int columna)
{
    int f=0,c=0;
    for(c=0; c<columna; c++)
    {
        for(f=0; f<fila; f++)
        {
            per[f][c].id_persona=-1;
        }
    }
}
////===========================================================================
//// FUNCION   : void mostrar_contactos().
//// ACCION    :
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrar_contactos()
{
    int pagina = 0, i=0,tecla=-1;
    bool flag=true;
    sys::cls();
    persona per[100][5];
    inicializar_matriz(per,100,5);
    int	cont = retorna_encontrados(per,false);
    while(flag)
    {
        if(per[pagina][i].id_persona>=0)
        {
            mostrarContacto(per[pagina][i]);
            mostrarTelefonosByContacto(per[pagina][i].id_persona);
            i++;

            if(i==5 || per[pagina][i].id_persona ==-1)
            {
                cout<<"\t\t <- Anterior \t\t Siguiente -> \t\t Esc=Salir \t\t A=Ayuda";
                while(true)
                {
                    tecla=getch();
                    if(tecla==77 && per[pagina][i+1].id_persona != -1 )  //siguiente
                    {
                        pagina=pagina+1;
                        i=0;
                        sys::cls();
                        break;
                    }
                    if(tecla==75 && pagina-1>=0)  //anterior
                    {
                        pagina=pagina-1;
                        i=0;
                        sys::cls();
                        break;
                    }
                    if(tecla==27)
                    {
                        flag=false;
                        break;
                    }
                    if(tecla==97)
                    {
                        ayuda();
                        i=0;
                        break;
                    }
                }
            }
        }
        else if(i==0)
        {
            cout<<"no se encontraro contactos a listar"<<endl;
            system("pause");
            flag=false;
        }

    }
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
// FUNCION   : void validacionCadena(char *campo, char *texto)
// ACCION    : valida cadena
// PARAMETROS: char *campo, char *texto
// DEVUELVE  : nada
//-----------------------------------------------------------------------------
bool validacionCadena(char *campo, char *texto)
{
    do
    {
        cout<< " Ingrese el "<< texto << " del contacto: ";
        sys::getline(campo, 50);
        if(strcmp(campo,"0")==0||strcmp(campo,"1")==0)
        {
            return false;
        }
        if(strlen(campo) < 1)
        {
            sys::cls();
            cout<<"INGRESE 0 PARA SALIR"<<endl;
            cout<< " El " << texto << " no puede estar vacio...\n Ingrese nuevamente el " << texto << " del contacto: ";
            sys::getline(campo, 50);
        }
    }
    while(strlen(campo) < 1);
    return true;
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
bool CheckSubstring(char *firstString, char *secondString)
{

    strToUpper(firstString);
    strToUpper(secondString);

    if(strlen(secondString) > strlen(firstString))
        return false;

    for (int i = 0; i < strlen(firstString); i++)
    {
        int j = 0;
        if(firstString[i] == secondString[j])
        {
            while (firstString[i] == secondString[j] && j < strlen(secondString))
            {
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
        while(fread (&per, sizeof(persona), 1, arch_per_encotradas))
        {
            if(id_contacto == per.id_persona)
            {
                sys::cls();
                if (opc == 3)
                    eliminar_registro(per);
                else
                    modificar_registro(per);
                encontrar=1;
            }
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
