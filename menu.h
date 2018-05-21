//#############################################################################
// ARCHIVO             : main.cpp
// AUTOR/ES            : Mansilla Francisco & Mercado Sebastian
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 31/08/2017.
// ULTIMA ACTUALIZACION: 18/09/2017.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "misFunciones.h"
#include "registroPersonas.h"
#include "registroPersonasEncontradas.h"
#include "registroTelefonos.h"
//****************************************************************************
//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;

////===========================================================================
//// FUNCION   : void menu_mod_telefonos().
//// ACCION    : Muestra menu modificacion telefonos contacto.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void menu_mod_telefonos()
{
    cout<< " =================================="<<endl;
    cout<< "|                                  |"<<endl;
    cout<< "|  1) - AGREGAR TELEFONOS          |"<<endl;
    cout<< "|  2) - MODIFICAR TELEFONOS        |"<<endl;
    cout<< "|  3) - RECUPERAR TELEFONO         |"<<endl;
    cout<< "|  4) - ELIMINAR  TELEFONO         |"<<endl;
    cout<< "|  0) - VOLVER AL MENU PRINCIPAL   |"<<endl;
    cout<< "|                                  |"<<endl;
    cout<< " =================================="<<endl;
    cout<< " INGRESE UNA OPCION: ";
}

//*****************************************************************************

////===========================================================================
//// FUNCION   : void menu_switch_mod_telefono().
//// ACCION    : Muestra menu modificacion de telefono.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------

void menu_switch_mod_telefono()
{
    cout<< " =================================="<<endl;
    cout<< "|                                  |"<<endl;
    cout<< "|  1) - MODIFICAR TIPO             |"<<endl;
    cout<< "|  2) - MODIFICAR NUMERO           |"<<endl;
    cout<< "|  0) - VOLVER AL MENU PRINCIPAL   |"<<endl;
    cout<< "|                                  |"<<endl;
    cout<< " =================================="<<endl;
    cout<< " INGRESE UNA OPCION: ";
}

//======================================================================
// FUNCION : presentacion ()
// ACCION : muestra la presentacion.
// PARAMETROS: -
// DEVUELVE : -
//----------------------------------------------------------------------
void presentacion() //funcion de la pantalla de presentacion.
{
    //sys::cls();
    cout<<endl;
    cout<<"  #####�--���������������������������������������������������������--�#####"<<endl;
    cout<<"  #####�--����    �� �   � ��� � ��� �    � ��� � �    ���   ������--�#####"<<endl;
    cout<<"  #####�--���� ��� � � ���  �� � ��� � ����  �� � � ��� � ��� �����--�#####"<<endl;
    cout<<"  #####�--����    �� �   � � � � ��� �    � � � � � ��� � ��� �����--�#####"<<endl;
    cout<<"  #####�--���� ��� � � ��� ��  �� � �� ���� ��  � � ��� � ��� �����--�#####"<<endl;
    cout<<"  #####�--����    �� �   � ��� ��� ���    � ��� � �    ���   ������--�#####"<<endl;
    cout<<"  #####�--���������������������������������������������������������--�#####"<<endl;
    cout<<"  #####���������������������������������������������������������������#####"<<endl;
    cout<<"  #####��������������                                   ��������������#####"<<endl;
    cout<<"  #####��������������         AGENDA ELECTRONICA        ��������������#####"<<endl;
    cout<<"  #####��������������                2018               ��������������#####"<<endl;
    cout<<"  #####��������������                                   ��������������#####"<<endl;
    cout<<"  #####���������������������������������������������������������������#####"<<endl;
    cout<<"  #####����������������������������������      MiSoftCPP     ���������#####"<<endl;
    cout<<"  #####���������������������������������������������������������������#####"<<endl;
    cout<<"  #########################################################################"<<endl;
    cout<<endl;
    sys::msleep(1);
}

//======================================================================
// FUNCION   : despedida ()
// ACCION    : muestra la pantalla de despedida.
// PARAMETROS: NADA
// DEVUELVE  : NADA
//----------------------------------------------------------------------
void despedida()
{
    sys::cls();
    cout<<"\n\n      #-���������������������������������������������������������-#"<<endl;
    cout<<"      #-����������                                      ���������-#"<<endl;
    cout<<"      #-����������          AGENDA ELECTRONICA          ���������-#"<<endl;
    cout<<"      #-����������                                      ���������-#"<<endl;
    cout<<"      #-����������                 2018                 ���������-#"<<endl;
    cout<<"      #-����������                                      ���������-#"<<endl;
    cout<<"      #-����������         CERRANDO EL PROGRAMA         ���������-#"<<endl;
    cout<<"      #-����������                                      ���������-#"<<endl;
    cout<<"      #-���������������������������������������������������������-#"<<endl;
    sys::msleep(1);

}

//======================================================================
// FUNCION   : void ayuda()
// ACCION    : es el acceso a la ayuda.
// PARAMETROS: NADA
// DEVUELVE  : NADA
//----------------------------------------------------------------------
void ayuda()
{

    sys::cls();
    cout << " #-=========================================================-#"<<endl;
    cout << " #                      AGREGAR CONTACTO                     #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # Permite ingresar los datos de un contacto                 #" << endl;
    cout << " # como nombre, apellido, direccion                          #" << endl;
    cout << " # nro de telefono , direccion E-Mail.                       #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout << " #                       BUSCAR CONTACTO                     #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # Permite buscar un contacto                                #"<<endl;
    cout << " # por nombre, apellido u apodo no es case sensitive.        #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout << " #                    MODIFICAR CONTACTO                     #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # Tras una busqueda permite modificar datos                 #" << endl;
    cout << " # del contacto ( nombre, apellido, direccion,               #" << endl;
    cout << " # nro de telefono, direccion E-Mail) o sus telefonos        #" << endl;
    cout << " # (agregar, eliminar, modificar tipo y numeros).            #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout << " #                     LISTAR CONTACTO                       #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # muestra todos los contactos con sus respectivos datos.    #" << endl;
    cout << " # si la lista supera los 5 contactos,                       #" << endl;
    cout << " # se mostraran en tandas de a 5.                            #" << endl;
    cout << " # Los contactos son listados, con la flechas se pasa de un  #" << endl;
    cout << " # contacto al otro con el enter se ingresa el id para       #" << endl;
    cout << " # recuperar el contacto                                     #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout << " #                    ELIMINAR CONTACTO                      #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # Tras una busqueda permite eliminar el contacto deseado.   #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout << " #                RECUPERAR CONTACTO ELIMINADO               #" << endl;
    cout << " #-----------------------------------------------------------#"<<endl;
    cout << " # Recupera un contacto eliminado mediante la eleccion       #" << endl;
    cout << " # de un ID tanto de contacto como de telefono.              #" << endl;
    cout << " # Los contactos son listados, con la flechas se pasa de un  #" << endl;
    cout << " # contacto al otro con el enter se ingresa el id para       #" << endl;
    cout << " # recuperar el contacto                                     #" << endl;
    cout << " #-=========================================================-#"<<endl;
    cout<<"\t  PRESIONE ENTER PARA CONTINUAR ...";
    cin.get();
    sys::cls();
}

//===========================================================================
// FUNCION   : void mostrarPrincipal().
// ACCION    : Muestra en pantalla el menu principal.
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void mostrarMenuPrincipal()
{
    char x=186;
    sys::cls();
    cout<< " ������������������������������������������������ͻ"<<endl;
    cout<< " �               AGENDA ELECTRONICA               �"<<endl;
    cout<< " ������������������������������������������������ĺ"<<endl;
    cout<< " �                                                �"<<endl;
    cout<< " �  C ) C A R G A R                               �"<<endl;
    cout<< " �  M ) M O D I F I C A R                         �"<<endl;
    cout<< " �  B ) B U S C A R                               �"<<endl;
    cout<< " �  L ) L I S T A R                               �"<<endl;
    cout<<" "<<x<<"  A ) R E C U P E R A R                         �"<<endl;
    cout<< " �  D ) E L I M I N A R                           �"<<endl;
    cout<< " �  H ) A Y U D A                                 �"<<endl;
    cout<< " �  S ) S A L I R                                 �"<<endl;
    cout<< " �                                                �"<<endl;
    cout<< " ������������������������������������������������ͼ\n"<<endl;
    cout << "INGRESE UNA OPCION: ";
}

//===========================================================================
// FUNCION   : void mostrarSubMenu1().
// ACCION    : Muestra en pantalla el submenu 1.
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void mostrar_Sub_Menu_buscar(int mod_bus)
{
    if (mod_bus==2)
    {
        cout<< " ������������������������������������������ͻ"<<endl;
        cout<< " �           OPCIONES DE BUSQUEDA           �"<<endl;
        cout<< " ������������������������������������������ĺ"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " �  A ) Buscar por Apellido                 �"<<endl;
        cout<< " �  B ) Buscar por Nombre                   �"<<endl;
        cout<< " �  C ) Buscar por Alias                    �"<<endl;
        cout<< " �  D ) Ayuda                               �"<<endl;
        cout<< " �  S ) Volver a Menu Principal             �"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " ������������������������������������������ͼ\n"<<endl;
        cout<< "INGRESE UNA OPCION: ";
    }
    else if(mod_bus==1)
    {
        cout<< " ������������������������������������������ͻ"<<endl;
        cout<< " �INGRESE OPCION DE BUSQUEDA PARA MODIFICAR �"<<endl;
        cout<< " ������������������������������������������ĺ"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " �  A ) Buscar por Apellido                 �"<<endl;
        cout<< " �  B ) Buscar por Nombre                   �"<<endl;
        cout<< " �  C ) Buscar por Alias                    �"<<endl;
        cout<< " �  D ) Ayuda                               �"<<endl;
        cout<< " �  S ) Volver a Menu Principal             �"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " ������������������������������������������ͼ\n"<<endl;
        cout<< "INGRESE UNA OPCION: ";
    }
    else
    {
        cout<< " ������������������������������������������ͻ"<<endl;
        cout<< " � INGRESE OPCION DE BUSQUEDA PARA ELIMINAR �"<<endl;
        cout<< " ������������������������������������������ĺ"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " �  A ) Buscar por Apellido                 �"<<endl;
        cout<< " �  B ) Buscar por Nombre                   �"<<endl;
        cout<< " �  C ) Buscar por Alias                    �"<<endl;
        cout<< " �  D ) Ayuda                               �"<<endl;
        cout<< " �  S ) Volver a Menu Principal             �"<<endl;
        cout<< " �                                          �"<<endl;
        cout<< " ������������������������������������������ͼ\n"<<endl;
        cout<< "INGRESE UNA OPCION: ";
    }
}

//===========================================================================
// FUNCION   : void subMenu1().
// ACCION    : Inicia el submenu1.
// PARAMETROS: NADA.
// DEVUELVE  : Si desea salir del programa o no.
//---------------------------------------------------------------------------
bool sub_Menu_Buscar(int mod_bus)
{
    //bool result = false;
    bool salir= false;//variable que controla el ciclo del menu
    char opcion;//variable que guarda la opcion seleccionada por el usuario

    bool encontro = true;

    while(!salir)
    {
        sys::cls();
        mostrar_Sub_Menu_buscar(mod_bus);
        cin.get(opcion);
        cin.ignore();

        switch(opcion)//Evaluo la variable opcion
        {
        case 'a':
        case 'A':
        {
            if(!buscar(1))
            {
                encontro = false; // Si no encontro, no se puede modificar
                cout << "No se encontro el contacto buscado, presione enter para continuar...";
                cin.get();
            }else salir=true;
        }
        break;

        case 'b':
        case 'B':
        {
            if(!buscar(2))
            {
                encontro = false; // Si no encontro, no se puede modificar
                cout << "No se encontro el contacto buscado, presione enter para continuar...";
                cin.get();
            }else salir=true;
        }
        break;

        case 'c':
        case 'C':
        {
            if( !buscar(3) )
            {
                encontro = false; // Si no encontro, no se puede modificar
                cout << "No se encontro el contacto buscado, presione enter para continuar...";
                cin.get();
            }else salir=true;
        }
        break;

        case 'd':
        case 'D':
        {
            ayuda();
        }
        break;
        case 's':
        case 'S':
        {
            return false;
        }
        break;
        default:
        {
            cout <<"Opcion no valida!!! presione enter para continuar";
            cin.get();
        }
        }

    }
    if ( mod_bus == 1 || mod_bus == 3 && encontro)
    {
        preguntar_id(mod_bus);
    }
    else
    {
        cout<<"no se encontro resultado"<<endl;
    }
    return true;

}

////===========================================================================
//// FUNCION   : void menu_mod().
//// ACCION    : Muestra menu modificacion de registro.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void menu_mod()
{
    cout<< " ======================================="<<endl;
    cout<< "|                                       |"<<endl;
    cout<< "| 1) - MODIFICAR DATOS DEL CONTACTO     |"<<endl;
    cout<< "| 2) - MODIFICAR DATOS DE SUS TELEFONOS |"<<endl;
    cout<< "| 0) - VOLVER AL MENU PRINCIPAL         |"<<endl;
    cout<< "|                                       |"<<endl;
    cout<< " ======================================= "<<endl;
    cout<< " INGRESE UNA OPCION: ";
}

////===========================================================================
//// FUNCION   : void menu_eliminar_registro().
//// ACCION    : Muestra menu eliminacion de registro
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void menu_eliminar_registro()
{
    cout<< " =================================="<<endl;
    cout<< "|                                  |"<<endl;
    cout<< "|  1) - ELIMINAR CONTACTO          |"<<endl;
    cout<< "|  2) - ELIMINAR TELEFONO          |"<<endl;
    cout<< "|  0) - VOLVER AL MENU PRINCIPAL   |"<<endl;
    cout<< "|                                  |"<<endl;
    cout<< " =================================="<<endl;
    cout<< " INGRESE UNA OPCION: ";
}

////===========================================================================
//// FUNCION   : void menu_mod_datos().
//// ACCION    : Muestra menu modificacion datos contacto.
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void menu_mod_contacto()
{
    cout<< " =================================="<<endl;
    cout<< "|                                  |"<<endl;
    cout<< "|  1) - MODIFICAR APELLIDO         |"<<endl;
    cout<< "|  2) - MODIFICAR NOMBRE           |"<<endl;
    cout<< "|  3) - MODIFICAR ALIAS            |"<<endl;
    cout<< "|  4) - MODIFICAR CORREO           |"<<endl;
    cout<< "|  0) - VOLVER AL MENU PRINCIPAL   |"<<endl;
    cout<< "|                                  |"<<endl;
    cout<< " =================================="<<endl;
    cout<< " INGRESE UNA OPCION: ";
}

//===========================================================================
// FUNCION   : void menuPrincipal().
// ACCION    : Inicia el menu principal.
// PARAMETROS: NADA.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
void menuPrincipal()
{

    contar_ID();

    bool salir= false;
    char opcion;

    while( !salir )
    {
        mostrarMenuPrincipal();
        cin.get(opcion);
        cin.ignore();

        switch(opcion)
        {
        case 'c':
        case 'C':
        {
            cargar_persona();
        }
        break;

        case 'm':
        case 'M':
        {
            //Modificar contacto
            sub_Menu_Buscar(1);
        }
        break;

        case 'B':
        case 'b':
        {
            sub_Menu_Buscar(2);
        }
        break;
        case 'D':
        case 'd':
        {
            sub_Menu_Buscar(3);
            //elminar contacto
        }
        break;

        case 'l':
        case 'L':
        {
            //listado de a 5 conactos
            mostrar_contactos();
        }
        break;
        case 'a':
        case 'A':
        {
            mostrar_contactos_eliminados();
        }
        break;

        case 'H':
        case 'h':
        {
            ayuda();
        }
        break;

        case 'S':
        case 's':
        {
            despedida();
            salir=true;
        }
        break;

        default:
        {
            cout <<"Opcion no valida, presione enter para ingresa otra opcion...!!!";
            cin.get();
        }
        break;
        }
    }
}

#endif // MENU_H_INCLUDED
