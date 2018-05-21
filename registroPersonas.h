//#############################################################################
// ARCHIVO             : registroPersonas.h
// AUTOR/ES            : Mansilla Francisco & Mercado Sebastian
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 29/04/2018.
// ULTIMA ACTUALIZACION: 19/05/2018.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef REGISTROPERSONAS_H_INCLUDED
#define REGISTROPERSONAS_H_INCLUDED
//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;
#include "prototipos.h"
#include <conio.h>

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
                EliminarTelefonosByContacto(per.id_persona,false);
            }

            if(modificado == true)
            {
                fseek(arch_per,-1*sizeof(per),SEEK_CUR);
                fwrite(&per, sizeof(persona),1,arch_per);
                fclose(arch_per);
                sys::cls();
                cout<<"Contacto recuperado:   "<<endl<<endl;
                mostrarContacto(per);
                mostrarTelefonosByContacto(per.id_persona);
                cout<<"Presione ENTER para continuar ..."<<endl;
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
    char numero[50],tipo[50],SN;
    bool salir = false;

    while(!salir)
    {
        menu_switch_mod_telefono();
        cin>>opc;
        cin.get();
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
//// FUNCION   : void mostrar_contactos().
//// ACCION    :
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrar_contactos_eliminados()
{
    int id_contacto;
    int pagina = 0, i=0,tecla=-1;
    bool flag=true;
    sys::cls();
    persona per[100][5];
    inicializar_matriz(per,100,5);
    int	cont = retorna_encontrados(per,true);
    while(flag)
    {
        if(per[pagina][i].id_persona>=0)
        {
            mostrarContacto(per[pagina][i]);
            mostrarTelefonosByContacto(per[pagina][i].id_persona);
            i++;

            if(i==5 || per[pagina][i].id_persona ==-1)
            {
                cout<<"\n <- Anterior \t\t\t Siguiente -> \t\t\t Esc=Salir \t\t\t Intro=Ingresar contacto";
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
                    if(tecla==13)
                    {
                        cout<<"\n\n INGRESE EL ID DEL CONTACTO A RECUPERAR: ";
                        cin>>id_contacto;
                        cin.ignore();
                        recuperar_contacto(id_contacto);
                        flag=false;
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
                strcpy(per.apellido,nuevo_dato);
                modificar_dato_persona(1, per.id_persona, nuevo_dato);
            }
            break;

            case '2':
            {
                cout<<"Ingrese el nuevo Nombre  : ";
                sys::getline(nuevo_dato, 50);
                strcpy(per.nombre,nuevo_dato);
                modificar_dato_persona(2, per.id_persona, nuevo_dato);
            }
            break;

            case '3':
            {
                cout<<"Ingrese el nuevo Alias  : ";
                sys::getline(nuevo_dato, 50);
                strcpy(per.alias,nuevo_dato);
                modificar_dato_persona(3, per.id_persona, nuevo_dato);
            }
            break;

            case '4':
            {
                cout<<"Ingrese el nuevo Correo  : ";
                sys::getline(nuevo_dato, 50);
                strcpy(per.email,nuevo_dato);
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
    mostrarTelefonosByContacto(per.id_persona);
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
            EliminarTelefonosByContacto(per.id_persona,true);
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
persona datos_persona()
{
    persona reg;
    int tecla;
    bool flag=true;
    reg.id_persona = 0;
    reg.eliminado=true;
    while(flag && reg.eliminado)
    {
        sys::cls();
        cout<<"INGRESE:  '0' PARA SALIR          '1' PARA INGRESAR A AYUDA (Reinicia carga de datos)"<<endl;
        do
        {
            flag=validacionCadena(reg.nombre, "nombre");
            if(strcmp(reg.nombre,"1")==0)
            {
                ayuda();
                flag=true;
                break;
            }
            if(!flag&&strcmp(reg.nombre,"0")==0)
                break;
            flag=validacionCadena(reg.apellido, "apellido");
            if(strcmp(reg.apellido,"1")==0)
            {
                ayuda();
                flag=true;
                break;
            }
            if(!flag&&strcmp(reg.apellido,"0")==0)
                break;
            flag=validacionCadena(reg.alias, "alias");
            if(strcmp(reg.alias,"1")==0)
            {
                ayuda();
                flag=true;
                break;
            }
            if(!flag&&strcmp(reg.alias,"0")==0)
                break;
            flag=validacionCadena(reg.domicilio, "domicilio");
            if(strcmp(reg.domicilio,"1")==0)
            {
                ayuda();
                flag=true;
                break;
            }
            if(!flag&&strcmp(reg.domicilio,"0")==0)
                break;
            flag=validacionCadena(reg.email, "correo");
            if(strcmp(reg.email,"1")==0)
            {
                ayuda();
                flag=true;
                break;
            }
            if(!flag&&strcmp(reg.email,"0")==0)
                break;
            reg.eliminado = false;
            reg.id_persona = ID_per;
        }
        while(true && reg.eliminado);
    }
    return reg;
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
    persona per = datos_persona();
    if(per.id_persona!=0)
    {
        if(guardar_persona(per))
            cargarTelefonos(per.id_persona);
    }
    sys::cls();
//
//    sys::cls();
//    persona per;
//    datos_persona(&per);
//    if(guardar_persona(per))
//        cargarTelefonos(per.id_persona);
//    sys::cls();

}
void mostrarIDenTabla(int id)
{
char x=179; //|
    if(id < 10)
        cout<< x << id << "  ";
    else
        cout<< x << id << " ";
}

void mostrarEspacioTextoEnTabla(char *texto, int cant)
{
char x=179;//|
    cout <<  x << texto;
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
char x=196,y=218,l=192,n=179,z=217,m=191,f=195,g=180,q=194,o=197,a=193;
    cout<<y<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<m<<endl;
    cout<< n<<"ID "<<n<<"APELLIDO                  "<<n<<"NOMBRE                    "<<n<<"APODO                     "<<n<<"CORREO                              "<<n<<endl;
    cout<<f<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<g<<endl;
    mostrarIDenTabla(per.id_persona);
    mostrarEspacioTextoEnTabla(per.apellido, 25);
    mostrarEspacioTextoEnTabla(per.nombre, 25);
    mostrarEspacioTextoEnTabla(per.alias, 25);
    mostrarEspacioTextoEnTabla(per.email, 35);
    cout<<n<<"\n"<<l<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<z<<endl;
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
