#ifndef REGISTROTELEFONOS_H_INCLUDED
#define REGISTROTELEFONOS_H_INCLUDED


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

    sys::cls();

    mostrar_contacto(per);
    cout<<endl<<endl;

    while (!salir)
    {
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
            cout<<"Ingrese el ID del telefono a modificar"<<endl;
            cin>>id_telefono;
            modificar_lista_contactos(per, id_telefono);
            salir = true;

        }
        break;

        case 3:
        {
            mostrar_contactos_eliminados();
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
// FUNCION   : bool guardarTel(telefono tel).
// ACCION    : .
// PARAMETROS: telefono tel.
// DEVUELVE  : NADA.
//---------------------------------------------------------------------------
bool guardarTel(telefono tel){

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
void cargarTelefono(int id_persona, telefono *tel){

    cout<< " Ingrese el TIPO del numero: ";
    sys::getline( tel->tipo, 50);
    cout<< " Ingrese el NUMERO del contacto: ";
    sys::getline(tel->numero, 10);
    bool esNum = false;
    //TODO: brackpoint
    while(!esNum)
    {
        if(esNumero(tel->numero) && (strlen(tel->numero) >= 8 && (strlen(tel->numero) <= 10)))
            esNum = true;
        if(!esNum)
        {
            cout<< " EL NUMERO QUE INGRESO NO ES VALIDO..."<<endl;
            cout << " INGRESE NUEVAMENTE...";
            sys::msleep(1);
            sys::cls();
            cout<< " Ingrese el NUMERO nuevamente: ";
            sys::getline(tel->numero,10);
        }
    }

    tel->id_persona = id_persona;
    tel->id_telefono = ID_tel;
    tel->eliminado = false;
    sys::cls();
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
        cout<< "\nPARA CARGAR UN NUEMRO AL CONTACTO PRESIONE 'C'...\n";
        key = sys::getch();
        //cin.ignore();
        if(key == 'c' || key == 'C'){
            if(ID_tel != NULL){
                cargarTelefono(id_persona, &tel);
                if(guardarTel(tel)){
                    cout << "SE GUARDO EL TELEFONO CORRECTAMENTE...";
                    sys::msleep(1);
                }
                cout << "\nPARA FINALIZAR LA CARGA DE TELEFONOS PRESIONE 'S' "<<endl;
            }
        }
        key = sys::getch();

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
void mostrarTelefono(telefono tel){
    cout<< " -----------------------------------"<<endl;
    cout<< " ID TELEFONO: "<< tel.id_telefono << endl;
    cout<< " -----------------------------------"<<endl;
    cout<< " TELEFONO TIPO: " << tel.tipo << endl;
    cout<< " NUMERO       : " << tel.numero << endl;
    cout<< " -----------------------------------"<<endl;
}

////===========================================================================
//// FUNCION   : mostrarTelefonosByContacto().
//// ACCION    : muestra telefonos por contacto
//// PARAMETROS: int id_persona.
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrarTelefonosByContacto(int id_persona){

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel)){

        if (tel.id_persona == id_persona && !tel.eliminado)
            mostrarTelefono(tel);
    }
    fclose(arch_tel);
}

////===========================================================================
//// FUNCION   : void mostrarTelefonosEliminadosByContacto().
//// ACCION    : muestra telefonos eliminados por contacto
//// PARAMETROS: int id_persona
//// DEVUELVE  : NADA.
////---------------------------------------------------------------------------
void mostrarTelefonosEliminadosByContacto(int id_persona){

    FILE *arch_tel;
    arch_tel = fopen(ruta_telefono,"rb");
    if(arch_tel == NULL)
        exit(98);
    telefono tel;
    while(fread(&tel, sizeof(telefono), 1, arch_tel)){

        if (tel.id_persona == id_persona && tel.eliminado)
            mostrarTelefono(tel);
    }
    fclose(arch_tel);
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
        if( tel.id_persona == per.id_persona && id_telefono == tel.id_telefono && tel.eliminado)
            modificado = true;
        if(modificado){
                //TODO: aca break
                fseek(arch_tel,sizeof(tel)*tel.id_telefono-1, SEEK_SET);
                fwrite(&tel, sizeof(telefono), 1, arch_tel);
                fclose(arch_tel);
                sys::msleep(2);
        }
        switch(opcion){
            case 1:{
                tel.eliminado = true;
                cout<< "Telefono Eliminado"<<endl;
            }break;

            case 2:{
                strcpy(tel.tipo, nuevo_tipo);
                cout<< "Tipo de telefono Modificado"<<endl;
            }break;

            case 3:{
                strcpy(tel.numero, nuevo_numero);
                cout<< "Numero de telefono Modificado"<<endl;
            }break;

            case 4:{
                tel.eliminado = false; //TODO: revisar
                cout<< "Telefono Recuperado"<<endl;
            }break;
        }
    }
    fclose(arch_tel);
    if(!modificado)
        cout<<"El ID de telefono no pertenece a este contacto o no existe"<<endl;
    cin.get();
}
#endif // REGISTROTELEFONOS_H_INCLUDED
