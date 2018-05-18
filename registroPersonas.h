//#############################################################################
// ARCHIVO             : main.cpp
// AUTOR/ES            : Mansilla Francisco
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 31/08/2017.
// ULTIMA ACTUALIZACION: 18/09/2017.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef REGISTROPERSONAS_H_INCLUDED
#define REGISTROPERSONAS_H_INCLUDED
//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;
#include "prototipos.h"

////===========================================================================
//// FUNCION   : void recuperar_contacto(int id_contacto).
//// ACCION    : recupera contacto.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void recuperar_contacto(int id_contacto)
{
    FILE *arch_per = fopen(ruta_persona, "rb+");
    persona per;
    bool modificado = false;

    if(arch_per != NULL)
    {
        int pos = 0;
        while(fread(&per, sizeof(persona), 1, arch_per))
        {
            if(per.id_persona == id_contacto &&
                    per.eliminado == true)
            {
                per.eliminado = false;
                modificado = true;
            }

            if(modificado == true)
            {
                fseek(arch_per,-sizeof(per)*pos,1);
                fwrite(&per, sizeof(persona),1,arch_per);
                fclose(arch_per);
                sys::cls();
                cout<<"Contacto recuperado:   "<<endl<<endl;
                mostrarContacto(per);
                break;
            }
            pos++;
        }
        fclose(arch_per);

        if(modificado == false)
        {
            cout<<"EL CONTACTO INGRESADO NO HA SIDO ELIMINADO O NO EXISTE"<<endl;
            sys::msleep(2);
        }
    }
    cin.get();
}

////===========================================================================
//// FUNCION   : void modificar_lista_contactos(persona per, int id_telefono).
//// ACCION    : Agregar telefonos,
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificar_lista_contactos(persona per, int id_telefono)
{
    int opc;
    char numero[50],tipo[50];
    bool salir = false;

    while(!salir)
    {
        menu_switch_mod_telefono();
        cin>>opc;

        switch(opc)
        {
        case 1:
        {
            cout<<"Ingrese el nuevo Tipo"<<endl;
            sys::getline(tipo, 50);
            editar_telefono(per, id_telefono, 2, 0, tipo);
            salir = true;
        }
        break;

        case 2:
        {
            cout<<"Ingrese el nuevo Telefono"<<endl;
            cin>>numero;
            editar_telefono(per, id_telefono, 3, numero, tipo);
            salir = true;
        }
        break;

        case 0:
        {
            salir = true;
        }
        break;
        default:
        {
            cout<<"Opcion Incorrecta.."<<endl;
            sys::msleep(2);
        }
        break;
        }
    }
}

////===========================================================================
//// FUNCION   : void mostrar_contactos_eliminados().
//// ACCION    : muestra contactos eliminados
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrar_contactos_eliminados()
{
    int id_contacto;

    FILE *arch_per;
    arch_per = fopen(ruta_persona,"rb");
    if(arch_per == NULL)
        exit(99);
    persona per;

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;

    int cont = 0;
    sys::cls();

    while(fread(&per, sizeof(persona), 1, arch_per))
    {
        if(per.eliminado != false)
        {
            mostrarContacto(per);
            fseek(arch_tel, sizeof(telefono), SEEK_SET);
            while(fread(&tel, sizeof(telefono), 1, arch_tel))
            {
                if(tel.eliminado)
                mostrarTelefono(tel);
            }
            fclose(arch_tel);
            cont ++;
        }
    }
    fclose(arch_per);

    if(cont == 0)
    {
        cout<<"NO HAY CONTACTOS ELIMINADOS... PRESIONE UNA TECLA PARA CONTINUAR"<<endl;
        cin.get();
    }
    else
    {
        cout<<"INGRESE EL ID DEL CONTACTO A RECUPERAR"<<endl;
        cin>>id_contacto;
        cin.ignore();
        recuperar_contacto(id_contacto);
    }
}

////===========================================================================
//// FUNCION   : void mostrar_contacto().
//// ACCION    :
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrar_contacto(persona per)
{
    cout<< " ==================================="<<endl;
    cout<< "           ID CONTACTO: "<< per.id_persona << endl;
    cout<< " ==================================="<<endl;
    cout<< " NOMBRE  : " << per.nombre << endl;
    cout<< " APELLIDO: " << per.apellido << endl;
    cout<< " CORREO  : " << per.email << endl;
    cout<< " APODO   : " << per.alias << endl;

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono, "rb");
    if(arch_tel != NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if(per.id_persona == tel.id_persona &&
                !tel.eliminado)
        {
            cout<< " -----------------------------------"<<endl;
            cout<< " ID TELEFONO: "<< tel.id_telefono << endl;
            cout<< " -----------------------------------"<<endl;
            cout<< " TELEFONO TIPO: " << tel.tipo << endl;
            cout<< " NUMERO       : " << tel.numero << endl;
        }
    }
    fclose(arch_tel);
    cout<< " ==================================="<<endl;

}

////===========================================================================
//// FUNCION   : void modificar_contacto().
//// ACCION    : Eliminado logico de un contacto
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificar_contacto(persona per)
{
    char opci;
    bool salir = false;
    char nuevo_dato[50];

    while (!salir)
    {
        sys::cls();

        mostrarContacto(per);
        menu_mod_contacto();

        cin>>opci;
        cin.ignore();
        if(esNumero(&opci))
        {
            switch(opci)
            {
            case '1':
            {
                cout<<"Ingrese el nuevo Apellido  : ";
                sys::getline(nuevo_dato, 50);
                modificar_dato_persona(1, per.id_persona, nuevo_dato);
            }
            break;

            case '2':
            {
                cout<<"Ingrese el nuevo Nombre  : ";
                sys::getline(nuevo_dato, 50);
                modificar_dato_persona(2, per.id_persona, nuevo_dato);
            }
            break;

            case '3':
            {
                cout<<"Ingrese el nuevo Alias  : ";
                sys::getline(nuevo_dato, 50);
                modificar_dato_persona(3, per.id_persona, nuevo_dato);
            }
            break;

            case '4':
            {
                cout<<"Ingrese el nuevo Correo  : ";
                sys::getline(nuevo_dato, 50);
                modificar_dato_persona(4, per.id_persona, nuevo_dato);
            }
            break;

            case '0':
            {
                salir = true;
            }
            break;

            default:
            {
                cout<<"Opcion incorrecta presione enter para continuar y ingrese una opcion valida"<<endl;
                cin.get();
            }
            break;
            }

        }
        else
        {
            cout<<"Opcion incorrecta presione enter para continuar y ingrese una opcion valida"<<endl;
            cin.get();
        }
    }
}

////===========================================================================
//// FUNCION   : void modificar_registro().
//// ACCION    : principal a la entrada de modificar un contacto o sus telefonos
//// PARAMETROS: persona.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificar_registro(persona per)
{
    int id_telefono;
    char opci;
    bool salir = false;

    while (!salir)
    {
        sys::cls();
        mostrarContacto(per);
        menu_mod();
        cin>>opci;
        cin.ignore();
        switch(opci)
        {
        case '1':
        {
            modificar_contacto(per);
        }
        break;

        case '2':
        {
            modificar_telefono(per);
        }
        break;

        case '0':
        {
            salir = true;
        }
        break;

        default:
        {
            cout<<"Opcion incorrecta presione enter e ingrese una opcion valida..."<<endl;
            cin.get();
        }
        }
    }

}

////===========================================================================
//// FUNCION   : void modificar_dato_persona(int opc, int id_persona, char* nuevo_dato).
//// ACCION    : Dependiendo de la opc recivida, modifica el contacto o lo elimina
//// PARAMETROS: opc, ed_persona, nuevo_dato.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificar_dato_persona(int opc, int id_persona, char* nuevo_dato)
{
    persona per;
    FILE *arch_per = fopen(ruta_persona, "rb+" );

    while(fread(&per, sizeof(persona),1,arch_per) )
    {
        if ( id_persona == per.id_persona && per.eliminado == false )
        {
            if (opc == 1 )
                strcpy(per.apellido, nuevo_dato);

            if (opc == 2 )
                strcpy(per.nombre, nuevo_dato);

            if (opc == 3 )
                strcpy(per.alias, nuevo_dato);

            if (opc == 4 )
                strcpy(per.email, nuevo_dato);

            if(opc == 5)
                per.eliminado = true;

            fseek(arch_per,-sizeof(per),1);
            fwrite(&per, sizeof(persona),1,arch_per);

            if (opc == 5)
                cout<<"Contacto Eliminado presione enter para continuar...";
            else
            {
                cout<<"Contacto Modificado presione enter para continuar...";
            }
            break;
        }
    }

    fclose(arch_per);
    cin.get();
}

//===========================================================================
// FUNCION   : bool guardar_persona(persona per).
// ACCION    : .
// PARAMETROS: persona per.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
bool guardar_persona(persona per)
{

    FILE *arch_per;
    arch_per = fopen(ruta_persona,"ab");
    if(arch_per == NULL)
        exit(99);
    fwrite(&per, sizeof(persona), 1, arch_per);
    fclose(arch_per);
    cout << "\nSE GUARDARON LOS DATOS CORRECTAMENTE..." << endl;
    ID_per ++;
    return true;
}

////===========================================================================
//// FUNCION   : void eliminar_registro(persona per).
//// ACCION    : Agregar telefonos,
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void eliminar_registro(persona per)
{
    int id_telefono, opci;
    bool salir = false;


    sys::cls();

    mostrarContacto(per);
    while (!salir)
    {
        menu_eliminar_registro();

        cin>>opci;
        cin.ignore();

        switch(opci)
        {
        case 1:
        {
            modificar_dato_persona(5, per.id_persona, "A");
            salir = true;
        }
        break;

        case 2:
        {
            cout<<"Ingrese el ID de telefono a eliminar \n (cero para salir)"<<endl;
            cin>>id_telefono;
            cin.ignore();
            if(id_telefono != 0)
                editar_telefono(per, id_telefono,1, 0, "A");
            salir = true;
        }
        break;

        case 0:
        {
            salir = true;

        }
        break;

        default:
        {
            cout<<"Opcion incorrecta"<<endl;
            sys::msleep(2);

        }
        break;
        }
    }
}

//===========================================================================
// FUNCION   : void datos_persona(persona *per).
// ACCION    : .
// PARAMETROS: persona per.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void datos_persona(persona *per)
{
    do
    {
        sys::cls();
        if(!per->eliminado) cout<<"Ingreso NOMBRE o APELLIDO vacio vuelva a cargar..."<<endl;
        cout<< " Ingrese el NOMBRE del contacto: ";
        sys::getline(per->nombre, 50);
        cout<< " Ingrese el APELLIDO del contacto: ";
        sys::getline(per->apellido, 50);
        cout<< " Ingrese el APODO del contacto: ";
        sys::getline(per->alias, 50);
        cout<< " Ingrese el DOMICILIO del contacto: ";
        sys::getline(per->domicilio, 50);
        cout<< " Ingrese el CORREO del contacto: ";
        sys::getline(per->email, 50);
        per->eliminado=false;
        per->id_persona = ID_per;
    }
    while(strcmp(per->nombre,"\0")==0|| strcmp(per->apellido,"\0")==0);
}

////===========================================================================
//// FUNCION   : void cargar_persona().
//// ACCION    : Cargar una persona y telefonos (si se desean)
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void cargar_persona()
{

    sys::cls();
    persona per;
    datos_persona(&per);
    if(guardar_persona(per))
        cargarTelefonos(per.id_persona);
    sys::cls();

}
void mostrarIDenTabla(int id)
{

    if(id < 10)
        cout<< "|" << id << "  ";
    else
        cout<< "|" << id << " ";
}

void mostrarEspacioTextoEnTabla(char *texto, int cant)
{

    cout <<  "|" << texto;
    for(int i = cant; i > (strlen(texto)-1); i--)
        cout << " ";
}
////===========================================================================
//// FUNCION   : void mostrarContacto(persona per){
//// ACCION    : muestra detalle contacto
//// PARAMETROS: persona per
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrarContacto(persona per)
{


    cout<< "|=========================================================================================================================|"<<endl;
    cout<< "|ID |APELLIDO                  |NOMBRE                    |APODO                     |CORREO                              |"<<endl;
    mostrarIDenTabla(per.id_persona);
    mostrarEspacioTextoEnTabla(per.apellido, 25);
    mostrarEspacioTextoEnTabla(per.nombre, 25);
    mostrarEspacioTextoEnTabla(per.alias, 25);
    mostrarEspacioTextoEnTabla(per.email, 35);
    cout << "|\n|=========================================================================================================================|";
    cout << endl;
    //cout<< " ======================================================================================|"<<endl;

}


////===========================================================================
//// FUNCION   : void modificar_dato_persona(int opc, int id_persona, char* nuevo_dato).
//// ACCION    : Dependiendo de la opc recibida, modifica el contacto o lo elimina
//// PARAMETROS: int opc, int id_persona, char* nuevo_dato
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificarContacto(int opc, int id_persona, char* nuevo_dato) //modificar_dato_persona
{

    FILE *arch_per = fopen(ruta_persona, "rb+" );
    if(arch_per == NULL)
        exit(99);
    persona per;


    while(fread(&per, sizeof(persona),1,arch_per))
    {
        if ( id_persona == per.id_persona && !per.eliminado)
        {
            switch(opc)
            {
            case 1:
                strcpy(per.apellido, nuevo_dato);
                break;
            case 2:
                strcpy(per.nombre, nuevo_dato);
                break;
            case 3:
                strcpy(per.alias, nuevo_dato);
                break;
            case 4:
                strcpy(per.email, nuevo_dato);
                break;
            case 5:
                per.eliminado = true;
                break;
            }
            //TODO: aca breakpoint
            fseek(arch_per, -sizeof(per)*per.id_persona, SEEK_CUR);
            fwrite(&per, sizeof(persona), 1,  arch_per);
            fclose(arch_per);

            if (opc == 5)
            {
                cout<<"Contacto Eliminado"<<endl;
                cin.get();

            }

            else
            {
                cout<<"Contacto Modificado"<<endl;
                cin.get();

            }

        }
    }
    fclose(arch_per);
}

////===========================================================================
//// FUNCION   : void opciones_modificacion_contacto().
//// ACCION    : opciones_modificacion_contacto
//// PARAMETROS: persona per
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void opciones_modificacion_contacto(persona per)
{
    int opci;
    bool salir = false;
    char nuevo_dato[50];
    sys::cls();
    mostrarContacto(per);

    while (!salir)
    {
        menu_mod_contacto();
        cin>>opci;
        cin.ignore();

        switch(opci)
        {
        case 1:
        {
            cout<<"Ingrese el nuevo Apellido  : ";
            sys::getline(nuevo_dato, 50);
            modificarContacto(1, per.id_persona, nuevo_dato);
        }
        break;

        case 2:
        {
            cout<<"Ingrese el nuevo Nombre  : ";
            sys::getline(nuevo_dato, 50);
            modificarContacto(2, per.id_persona, nuevo_dato);
        }
        break;

        case 3:
        {
            cout<<"Ingrese el nuevo Alias  : ";
            sys::getline(nuevo_dato, 50);
            modificarContacto(3, per.id_persona, nuevo_dato);
        }
        break;

        case 4:
        {
            cout<<"Ingrese el nuevo Correo  : ";
            sys::getline(nuevo_dato, 50);
            modificarContacto(4, per.id_persona, nuevo_dato);
        }
        break;

        case 0:
            salir = true;
            break;

        default:
            cout<<"Opcion incorrecta"<<endl;
            break;
        }
    }
}

#endif // REGISTROPERSONAS_H_INCLUDED
