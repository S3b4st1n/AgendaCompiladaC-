//#############################################################################
// ARCHIVO             : registroTelefonos.h
// AUTOR/ES            : Mansilla Francisco & Mercado Sebastian
// VERSION             : 0.02 beta.
// FECHA DE CREACION   : 29/04/2018.
// ULTIMA ACTUALIZACION: 19/05/2018.
// LICENCIA            : GPL (General Public License) - Version 3.
//****************************************************************************
#ifndef REGISTROTELEFONOS_H_INCLUDED
#define REGISTROTELEFONOS_H_INCLUDED
#include "CSYSTEM/csystem.h"

//==============================================================================
// DECLARACION DEL ESPACIO DE NOMBRES POR DEFECTO
//------------------------------------------------------------------------------
using namespace std;


////===========================================================================
//// FUNCION   : void modificar_telefono().
//// ACCION    : Agregar telefonos, o modificar lo que ya tiene una persona
//// PARAMETROS: persona.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void modificar_telefono(persona per)
{
    int id_telefono, opci;
    bool salir = false;
    bool flag=false;
    char SN;

    while (!salir)
    {
    sys::cls();

    mostrarContacto(per);
    flag=mostrarTelefonosByContacto(per.id_persona);

        menu_mod_telefonos();
        cin>>opci;
        cin.ignore();

        switch(opci)
        {
        case 1:
        {
            cargarTelefonos(per.id_persona);
        }
        break;

        case 2:
        {
            if(flag){
            cout<<"Ingrese el ID del telefono a modificar"<<endl;
            cin>>id_telefono;
            modificar_lista_contactos(per, id_telefono);
            salir = true;
            } else{
            cout<<"el contacto no tiene telfonos para modificar"<<endl;
            sys::pause();
            }
        }
        break;

        case 3:
        {
            recuperar_telefono(id_telefono,per.id_persona);
            salir = true;
        }
        break;

        case 4:
        {
            if(flag){
            cout<<"Ingrese el ID del telefono a eliminar"<<endl;
            cin>>id_telefono;
            cin.get();
            while(true){
            cout<<"Esta seguro que desea eliminar el telefono S/N?"<<endl;
            cin>>SN;
            cin.get();
            if(SN=='s'||SN=='S'){
            editar_telefono(per, id_telefono, 1, "nonumero", "notipo");
            salir = true;
            break;
            }
            else{
            break;
            }
            }
            salir = true;
            } else{
            cout<<"el contacto no tiene telfonos para eliminar"<<endl;
            sys::pause();
            }
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
// FUNCION   : bool guardarTel(telefono tel).
// ACCION    : .
// PARAMETROS: telefono tel.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
bool guardarTel(telefono tel)
{

    FILE *arch_tel;
    arch_tel= fopen(ruta_telefono,"ab");
    if(arch_tel==NULL)
        exit(98);
    fwrite(&tel, sizeof(telefono), 1, arch_tel);
    fclose(arch_tel);
    //cout << "\nSE GUARDO EL TELEFONO CORRECTAMENTE..." << endl;
    ID_tel++;
    return true;
}

////===========================================================================
//// FUNCION   : void cargarTelefono(persona per, telefono *tel).
//// ACCION    :
//// PARAMETROS: persona per, telefono *tel.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
telefono cargarTelefono(int id_persona){

    telefono reg;
    validacionCadena(reg.tipo, "tipo");
    validacionCadena(reg.numero, "numero");

    bool esNum = false;

    while(!esNum)
    {
        if(esNumero(reg.numero) && (strlen(reg.numero) > 5 && strlen(reg.numero) < 10) )
            esNum = true;
        if(!esNum)
        {
            cout<< " EL NUMERO QUE INGRESO NO ES VALIDO..."<<endl;
            cout << " INGRESE NUEVAMENTE...";
            sys::msleep(1);
            sys::cls();
            cout<< " Ingrese el NUMERO nuevamente: ";
            sys::getline(reg.numero,10);
        }
    }

    reg.id_persona = id_persona;
    reg.id_telefono = ID_tel;
    reg.eliminado = false;
    sys::cls();
    return reg;
}

////===========================================================================
//// FUNCION   : void cargarTelefonos(persona per).
//// ACCION    :
//// PARAMETROS: persona per.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void cargarTelefonos(int id_persona)
{
    telefono tel;
    char key;
    do{
        cout<< "\nPARA CARGAR UN NUEMRO AL CONTACTO PRESIONE 'C' O 'S' PARA SALIR...\n";
        key = sys::getch();
        cin.get();
        if(key == 'c' || key == 'C'){
            if(ID_tel != NULL){
                tel = cargarTelefono(id_persona);
                if(guardarTel(tel)){
                    cout << "SE GUARDO EL TELEFONO CORRECTAMENTE...";
                    sys::msleep(1);
                }
                cout << "\nPARA FINALIZAR LA CARGA DE TELEFONOS PRESIONE 'S' "<<endl;
            }
        }
//        key = sys::getch();
//        cin.get();
        if(key == 's' || key == 'S')
            break;

    }while(key != 's' || key != 'S');
}

////===========================================================================
//// FUNCION   : void mostrarTelefono().
//// ACCION    : muestrta telefono
//// PARAMETROS: telefono tel
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrarTelefono(telefono tel)
{
    char x=196,y=218,l=192,n=179,z=217,m=191,f=195,g=180,q=194,o=197,a=193;
    cout<<y<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<q<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<m<<endl;
   // cout<< "|============================================|"<<endl;
    cout<<n<<"IDT"<<n<<"TIPO_TELEFONO        "<<n<<"NUMERO            "<<n<<endl;
    cout<<f<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<o<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<g<<endl;
    mostrarIDenTabla(tel.id_telefono);
    mostrarEspacioTextoEnTabla(tel.tipo, 20);
    mostrarEspacioTextoEnTabla(tel.numero, 17);
    cout<<n<<"\n"<<l<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<a<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<x<<z<<endl;
   // cout << "|\n|============================================|";
    cout << endl;
}
////===========================================================================
//// FUNCION   : bool EliminarTelefonosByContacto(int id_persona, bool eliminado)
//// ACCION    : muestra telefonos por contacto
//// PARAMETROS: int id_persona.
//// DEVUELVE  : BOOL
////---------------------------------------------------------------------------
bool EliminarTelefonosByContacto(int id_persona, bool eliminado)
{
    bool flag=false;
    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if (tel.id_persona == id_persona && !tel.eliminado)
        {
            flag=true;
            tel.eliminado=eliminado;
        }

    }
    fclose(arch_tel);
    return flag;
}

////===========================================================================
//// FUNCION   : mostrarTelefonosByContacto().
//// ACCION    : muestra telefonos por contacto
//// PARAMETROS: int id_persona.
//// DEVUELVE  : BOOL
////---------------------------------------------------------------------------
bool mostrarTelefonosByContacto(int id_persona)
{
    bool flag=false;
    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if (tel.id_persona == id_persona && !tel.eliminado)
        {
            flag=true;
            mostrarTelefono(tel);
        }

    }
    fclose(arch_tel);
    return flag;
}

////===========================================================================
//// FUNCION   : void mostrarTelefonosEliminadosByContacto().
//// ACCION    : muestra telefonos eliminados por contacto
//// PARAMETROS: int id_persona
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrarTelefonosEliminadosByContacto(int id_persona)
{

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {

        if (tel.id_persona == id_persona && tel.eliminado)
            mostrarTelefono(tel);
    }
    fclose(arch_tel);
}
////===========================================================================
//// FUNCION   : void recuperar_telefono(int id_telefono, int persona_id).
//// ACCION    : Eliminado logico de un telefono
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void recuperar_telefono(int id_telefono, int persona_id)
{
    telefono tel;
    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono, "rb+");
    if(arch_tel == NULL)
        exit(98);

    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if(persona_id==tel.id_persona && tel.eliminado==true)
        {
            mostrarTelefono(tel);
        }
    }
    cout<<"INGRESE ID DE TELEFONO A RECUPERAR: ";
    cin>>id_telefono;
    cin.get();
    fseek(arch_tel, 0, SEEK_SET);

    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if(id_telefono == tel.id_telefono)
        {
            tel.eliminado = false;
            fseek(arch_tel,sizeof(tel)*-1, SEEK_CUR);
            fwrite(&tel, sizeof(telefono), 1, arch_tel);
            cout<< "TELEFONO RECUPERADO" << endl;
            cin.get();
            break;
        }
    }

    if(tel.eliminado == true)
    cout<<"INGRESASTE UN ID INVALIDO..."<<endl;
    fclose(arch_tel);
    cin.get();
}

////===========================================================================
//// FUNCION   : void eliminar_telefono(int id_telefono).
//// ACCION    : Eliminado logico de un telefono
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void eliminar_telefono(int id_telefono)
{
    telefono tel;
    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono, "rb+");
    if(arch_tel == NULL)
        exit(98);

    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if(id_telefono == tel.id_telefono)
        {
            tel.eliminado = true;
            fseek(arch_tel, -sizeof(tel)*tel.id_telefono, 1);
            fwrite(&tel, sizeof(telefono), 1, arch_tel);
            cout<< "TELEFONO ELIMINADO" << endl;
            sys::msleep(2);

            break;
        }
    }

    if(tel.eliminado != true)
        cout<<"INGRESASTE UN ID INVALIDO..."<<endl;

    fclose(arch_tel);
    cin.get();
}

////===========================================================================
//// FUNCION   : void eliminar_telefono().
//// ACCION    : Editar dato de telefono o eliminado
//// PARAMETROS: NADA.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void editar_telefono(persona per, int id_telefono, int opcion, char* nuevo_numero, char* nuevo_tipo)
{
    bool modificado = false;

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono, "rb+");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel))
    {
        if(tel.id_persona == per.id_persona && id_telefono == tel.id_telefono && tel.eliminado==false)
        {
            switch(opcion)
            {
            case 1:
            {
                tel.eliminado = true;
                fseek(arch_tel,-1*sizeof(telefono), SEEK_CUR);
                fwrite(&tel, sizeof(telefono), 1, arch_tel);
                cout<< "Telefono Eliminado"<<endl;
                modificado=true;
                fclose(arch_tel);
                cin.get();
            }
            break;

            case 2:
            {
                strcpy(tel.tipo, nuevo_tipo);
                fseek(arch_tel,-1*sizeof(telefono), SEEK_CUR);
                fwrite(&tel, sizeof(telefono), 1, arch_tel);
                cout<< "Tipo de telefono Modificado"<<endl;
                fclose(arch_tel);
                modificado=true;
                cin.get();
            }
            break;

            case 3:
            {
                strcpy(tel.numero, nuevo_numero);
                fseek(arch_tel,-1*sizeof(telefono), SEEK_CUR);
                fwrite(&tel, sizeof(telefono), 1, arch_tel);
                cout<< "Numero de telefono Modificado"<<endl;
                fclose(arch_tel);
                modificado=true;
                cin.get();
            }
            break;
            }

        }
    }

    if(!modificado)
        cout<<"El ID de telefono no pertenece a este contacto o no existe"<<endl;
    cin.get();
}
#endif // REGISTROTELEFONOS_H_INCLUDED
