#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAMM 10
#define TAMTR 20
#define TAMT 4
#define TAMC 5
#define TAMS 4
#define TAMCL 10

typedef struct
{
    int dia;
    int mes;
    int anio;
} eFecha;

typedef struct
{
    int id;
    char descripcion[25];
    float precio;
} eServicio;

typedef struct
{
    int id;
    char descripcion[20];
} eTipo;

typedef struct
{
    int id;
    char nombreColor[20];
} eColor;

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
}eCliente;

typedef struct
{
    int id;
    char marca[20];
    int idTipo;
    int idColor;
    int idCliente;
    int cilindrada;
    int puntaje;
    int isEmpty;
} eMoto;

typedef struct
{
    int id;
    int idMoto;
    int idServicio;
    eFecha fechaIngreso;
    int isEmpty;
} eTrabajo;



int menu();
int harcodearMotos(int* pId, eMoto motos[], int tamM, int cant);

int inicializarMotos(eMoto motos[], int tamM);
int buscarLibre(eMoto motos[], int tamM, int* pIndice);

int altaMoto(eMoto motos[], int tamM, eTipo tipos[], int tamT, eColor colores[], int tamC, eCliente clientes[], int tamCl, int* pNextId);
int cargarMoto(eMoto* pMoto, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);

int mostarMoto(eMoto motos, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);
int mostarMotos(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);

int buscarMotoId(eMoto motos[],int tamM, int id);
int bajaMoto(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);

int modificarMoto(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);
int submenuModificacion();

int listarColores(eColor colores[], int tamC);
int mostrarColores(eColor colores[], int tamC);
int cargarDescripcionColor(int id, char descripcion[], eColor color[], int tamC);

int listarTipos(eTipo tipos[], int tamT);
int mostrarTipos(eTipo tipos[], int tamT);
int cargarDescripcionTipo(int id, char descripcion[], eTipo tipos[], int tamT);

int listarServicios(eServicio servicios[], int tamS);
int mostrarServicios(eServicio servicios[], int tamS);

int mostrarClientes(eCliente clientes[], int tamCl);
int cargarNombreCliente(int id, char nombre[], eCliente clientes[], int tamCl);


int inicializarTrabajos(eTrabajo trabajos[], int tamTr);
int buscarLibreTrabajo(eTrabajo trabajos[], int tamTr, int* pIndice);
int altaTrabajo(eTrabajo trabajos[], int tamTr, eMoto motos[], int tamM, eTipo tipos[], int tamT, eColor colores[], int tamC, eCliente clientes[], int tamCl, eServicio servicios[], int tamS, int* pNextId);
int cargarTrabajo(eTrabajo* pTrabajo, eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl, eServicio servicios[], int tamS);
//**************************--------------------------------***********************************
int mostarTrabajo(eMoto motos[],int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);
int mostarTrabajos(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl);

int main()
{
   int nextIdMoto = 100;
    int nextIdTrabajo = 30000;
    char salir = 'n';

    eMoto motos[TAMM];

    eTipo tipos[TAMT] = {{1000, "Enduro"},
        {1001, "Chopera"},
        {1002, "Scooter"},
        {1003, "Vintage"}
    };

    eColor colores[TAMC] = {{10000, "Gris"},
        {10001, "Negro"},
        {10002, "Azul"},
        {10003, "Blanco"},
        {10004, "Rojo"}
    };

    eCliente clientes[TAMCL] =
    {
      {7000, "Julian", 'm'},
      {7001, "Sofia", 'f'},
      {7002, "Lucrecia", 'f'},
      {7003, "Bautista", 'm'},
      {7004, "Mariana", 'f'},
      {7005, "Gonzalo", 'm'},
      {7006, "Matias", 'm'},
      {7007, "Hector", 'm'},
      {7008, "Romina", 'f'},
      {7009, "Camila", 'f'},
    };

    eServicio servicios[TAMS] = { {20000, "Limpieza", 450},
        {20001, "Ajuste", 300},
        {20003, "Balanceo", 150},
        {20004, "Cadena", 390}
    };

    eTrabajo trabajos[TAMTR];


    inicializarMotos(motos, TAMM);
    inicializarTrabajos(trabajos, TAMTR);
    harcodearMotos(&nextIdMoto, motos, TAMM, 5);


    do
    {
        switch(menu())
        {
            case 'A':
                if(altaMoto(motos, TAMM, tipos, TAMT, colores, TAMC, clientes, TAMCL, &nextIdMoto))
                {
                    printf("ALTA EXITOSA!!!\n");
                }
                else
                {
                    printf("ERROR AL REALIZAR EL ALTA\n\n");
                }
                break;
            case 'B':
                modificarMoto(motos, TAMM, colores, TAMC, tipos, TAMT, clientes, TAMCL);
                break;
            case 'C':
                bajaMoto(motos, TAMM, colores, TAMC, tipos, TAMT, clientes, TAMCL);
                break;
            case 'D':
                mostarMotos(motos, TAMM, colores, TAMC, tipos, TAMT, clientes, TAMCL);
                break;
            case 'E':
                listarTipos(tipos, TAMT);
                break;
            case 'F':
                listarColores(colores, TAMC);
                break;
            case 'G':
                listarServicios(servicios, TAMS);
                break;
            case 'H':
                if(altaTrabajo(trabajos, TAMTR, motos, TAMM, tipos, TAMT, colores, TAMC, clientes, TAMCL, servicios, TAMS, &nextIdTrabajo))
                {
                    printf("ALTA EXITOSA!!!\n");
                }
                else
                {
                    printf("ERROR AL REALIZAR EL ALTA\n\n");
                }
                break;
            case 'I':
                printf("LISTAR TRABAJOS\n");
                break;
            case 'J':
                printf("HA SELECCIONADO SALIR\n");
                salir = 's';
                break;
            default:
                printf("OPCION INVALIDA!!!\n");
                break;
        }

        system("pause");

    }
    while(salir == 'n');

    return 0;
}

int listarColores(eColor colores[], int tamC)
{
    int todoOk = 0;

    if(colores != NULL && tamC > 0)
    {
        system("cls");

        printf("|===================|\n");
        printf("|  COLORES DE MOTO  |\n");
        printf("|===================|\n");
        for(int i = 0; i < tamC; i++)
        {
            printf("|       %-6s      |\n", colores[i].nombreColor);
            printf("|-------------------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}



int mostrarColores(eColor colores[], int tamC)
{
    int todoOk = 0;

    if(colores != NULL && tamC > 0)
    {
        system("cls");

        printf("|=======|==================|\n");
        printf("|  ID   |  COLORES DE MOTO |\n");
        printf("|=======|==================|\n");
        for(int i = 0; i < tamC; i++)
        {
            printf("| %d |       %-6s     |\n", colores[i].id, colores[i].nombreColor);
            printf("|-------|------------------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}

int cargarDescripcionColor(int id, char descripcion[], eColor color[], int tamC)
{
    int todoOk = 0;

    if(descripcion != NULL && color != NULL && tamC > 0)
    {
        for(int i = 0 ; i < tamC ; i++)
        {
            if(color[i].id == id)
            {
                strcpy(descripcion, color[i].nombreColor);
                break;
            }
        }

        todoOk = 1;
    }
    return todoOk;
}

int menu()
{
    char opcion;

    system("cls");

    printf("       ***ABM MOTOS***\n\n");
    printf("A- ALTA MOTO\n");
    printf("B- MODIFICAR MOTO\n");
    printf("C- BAJA MOTO\n");
    printf("D- LISTAR MOTO\n");
    printf("E- LISTAR TIPOS\n");
    printf("F- LISTAR COLORES\n");
    printf("G- LISTAR SERVICIOS\n");
    printf("H- ALTA TRABAJO\n");
    printf("I- LISTAR TRABAJOS\n");
    printf("J- SALIR\n");
    printf("Ingrese una opcion: ");
    fflush(stdin);
    scanf("%c", &opcion);

    opcion = toupper(opcion);

    return opcion;
}

int inicializarMotos(eMoto motos[], int tamM)
{
    int todoOk = 0;

    if(motos != NULL && tamM > 0)
    {
        for(int i = 0; i < tamM; i++)
        {
            motos[i].isEmpty = 1;
        }

        todoOk = 1;
    }

    return todoOk;
}


int buscarLibre(eMoto motos[], int tamM, int* pIndice)
{
    int todoOk = 0;
    int indice = -1;

    if(motos != NULL && tamM > 0 && pIndice != NULL)
    {
        for(int i = 0; i < tamM; i++)
        {
            if(motos[i].isEmpty)
            {
                indice = i;
                break;
            }
        }

        *pIndice = indice;
        todoOk = 1;

    }

    return todoOk;
}

int cargarMoto(eMoto* pMoto, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl)
{
    int todoOk = 0;
    char auxCad[20];
    int auxInt;
    if(pMoto != NULL && colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0)
    {
        printf("Ingrese la marca de la moto: ");
        fflush(stdin);
        gets(auxCad);
        //validacion
        strcpy(pMoto->marca, auxCad);

        mostrarTipos(tipos, tamT);
        printf("Ingrese el id del tipo de moto: ");
        scanf("%d", &auxInt);
        //validacion
        pMoto->idTipo = auxInt;

        mostrarColores(colores, tamC);
        printf("Ingrese el id del color de la moto: ");
        scanf("%d", &auxInt);
        //validacion
        pMoto->idColor = auxInt;

        mostrarClientes(clientes, tamCl);
        printf("Ingrese el id del cliente: ");
        scanf("%d", &auxInt);
        //validacion
        pMoto->idCliente = auxInt;

        printf("Ingrese la cilindrada de la moto: ");
        scanf("%d", &auxInt);
        //validar
        pMoto->cilindrada = auxInt;

        printf("Ingrese puntaje de la moto: ");
        scanf("%d", &auxInt);
        //validar
        pMoto->puntaje = auxInt;

        pMoto->isEmpty = 0;

        todoOk = 1;
    }

    return todoOk;
}


int altaMoto(eMoto motos[], int tamM, eTipo tipos[], int tamT, eColor colores[], int tamC, eCliente clientes[], int tamCl, int* pNextId)
{
    int todoOk = 0;
    int indiceLibre;
    eMoto auxMoto;

    if(motos != NULL && tamM > 0 && tipos != NULL && tamT > 0 && colores != NULL && tamC > 0 && clientes != NULL && tamCl > 0 && pNextId != NULL)
    {
        system("cls");

        printf("        ***ALTA MOTOS*** \n");
        printf("----------------------------------\n");
        buscarLibre(motos, tamM, &indiceLibre);

        if(indiceLibre == -1)
        {
            printf("NO HAY LUGAR EN EL SISTEMA\n");
        }
        else
        {
            cargarMoto(&auxMoto, colores, tamC, tipos, tamT, clientes, tamCl);
            auxMoto.id = *pNextId;
            *pNextId = *pNextId + 1;

            motos[indiceLibre] = auxMoto;
            todoOk = 1;
        }

    }

    return todoOk;
}

int mostarMoto(eMoto motos, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl)
{
    int todoOk = 0;
    char auxTipo[20];
    char auxColor[20];
    char auxCliente[20];

    if(colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0)
    {
        cargarDescripcionTipo(motos.idTipo, auxTipo, tipos, tamT);
        cargarDescripcionColor(motos.idColor, auxColor, colores, tamC);
        cargarNombreCliente(motos.idCliente, auxCliente, clientes, tamCl);

        printf("|%d |   %-10s  |  %-7s  |  %-6s |  %-10s |    %-3d     |   %2d    |\n", motos.id,
                                                                                          motos.marca,
                                                                                          auxTipo,
                                                                                          auxColor,
                                                                                          auxCliente,
                                                                                          motos.cilindrada,
                                                                                          motos.puntaje
                                                                                         );

        todoOk = 1;
    }

    return todoOk;
}


int mostarMotos(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl)
{
    int todoOk = 0;
    int flag = 1;

    if(motos != NULL && tamM > 0 && colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0)
    {
        system("cls");

        printf("|===============================================================================|\n");
        printf("|                                LISTA DE MOTOS                                 |\n");
        printf("|=====================================================================|=========|\n");
        printf("| ID |     MARCA     |   TIPO    |  COLOR  |   CLIENTE   | CILINDRADA | PUNTAJE |\n");
        printf("|----|---------------|-----------|---------|-------------|------------|---------|\n");

        for(int i; i < tamM; i++)
        {
            if(!motos[i].isEmpty)
            {
                mostarMoto(motos[i], colores, tamC, tipos, tamT, clientes, tamCl);
                printf("|----|---------------|-----------|---------|-------------|------------|---------|\n");
                flag = 0;
                todoOk = 1;
            }
        }

        if(flag)
        {
            printf("No hay motos para mostrar\n");
        }
    }

    return todoOk;

}



int harcodearMotos(int* pId, eMoto motos[], int tamM, int cant)
{
    int todoOk =  0;
    eMoto almacenMotos[] =
    {
        {100,"Honda",1000,10001, 7000, 500, 6, 0},
        {101,"Yamaha",1003,10000, 7001, 750, 2, 0},
        {102,"Kawasaki",1002,10004, 7002, 50, 10, 0},
        {103,"Piaggio",1002,10003, 7003, 600, 4, 0},
        {104,"Ducati",1001,10002, 7004, 125, 7, 0},
    };

    if(motos != NULL && tamM > 0 && cant <= tamM && cant <= 5)
    {
        for(int i = 0; i < cant; i++)
        {
            motos[i] = almacenMotos[i];
            *pId = *pId + 1;
        }
        todoOk = 1;
    }
    return todoOk;
}

int buscarMotoId(eMoto motos[],int tamM, int id)
{
    int indice = -1;

    if(motos != NULL && tamM > 0)
    {
        for(int i = 0; i < tamM; i++)
        {
            if(!motos[i].isEmpty && motos[i].id == id)
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}

int bajaMoto(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl)
{
    int todoOk = 0;
    int idMoto;
    char confirma;
    int indice;

    if(motos != NULL && tamM > 0 && colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0)
    {
        mostarMotos(motos, tamM, colores, tamC, tipos, tamT, clientes, tamCl);
        printf("Ingrese el ID de la moto que desea dar de baja: ");
        scanf("%d", &idMoto);

        indice = buscarMotoId(motos, tamM, idMoto);

        system("cls");
        if(indice == -1)
        {
            printf("No hay motos para dar de baja\n");
        }
        else
        {
            mostarMoto(motos[indice], colores, tamC, tipos, tamT, clientes, tamCl);
            printf("Desea dar de baja esta moto?: ");
            fflush(stdin);
            scanf("%c", &confirma);
            //validar s o n y meter tolower
            system("cls");

            if(confirma == 's')
            {
                motos[indice].isEmpty = 1;
                printf("Baja realizada con exito\n");
                todoOk = 1;
            }
            else
            {
                printf("Baja cancelada\n");
            }
        }

    }
    return todoOk;
}





int modificarMoto(eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl)
{
    int todoOk = 0;
    int idMoto;
    char confirma;
    int indice;
    int auxPuntaje;
    int auxIdColor;

    if(motos != NULL && tamM > 0 && colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0)
    {
        mostarMotos(motos, tamM, colores, tamC, tipos, tamT, clientes, tamCl);
        printf("Ingrese el ID de la moto que desea modificar: ");
        scanf("%d", &idMoto);

        indice = buscarMotoId(motos, tamM, idMoto);

        system("cls");
        if(indice == -1)
        {
            printf("No hay motos para modificar\n");
        }
        else
        {
            mostarMoto(motos[indice], colores, tamC, tipos, tamT, clientes, tamCl);
            printf("Desea modificar esta moto?: ");
            fflush(stdin);
            scanf("%c", &confirma);

            system("cls");

            if(confirma == 's')
            {
                switch(submenuModificacion())
                {
                    case 1:
                        mostrarColores(colores, tamC);
                        printf("Ingrese el ID del nuevo color: \n");
                        scanf("%d", &auxIdColor);
                        //validacion
                        motos[indice].idColor = auxIdColor;
                        break;
                    case 2:
                        printf("Ingrese nuevo puntaje: \n");
                        scanf("%d", &auxPuntaje);
                        //validacion
                        motos[indice].puntaje = auxPuntaje;
                        break;
                    case 3:
                        printf("SALIR\n");
                        break;
                    default:
                        printf("OPCION INVALIDA!!!\n");
                        break;

                }
            }
            else
            {
                printf("Modificacion cancelada\n");
            }
        }

    }
    return todoOk;
}


int submenuModificacion()
{
    int opcion;

    system("cls");

    printf("       ***SUBMENU MODIFICACION***\n\n");
    printf("1- MODIFICAR COLOR\n");
    printf("2- MODIFICAR PUNTAJE\n");
    printf("3- SALIR\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

int listarServicios(eServicio servicios[], int tamS)
{
    int todoOk = 0;

    if(servicios != NULL && tamS > 0)
    {
        system("cls");

        printf("|=====================|\n");
        printf("|  SERVICIOS DE MOTO  |\n");
        printf("|=====================|\n");
        for(int i = 0; i < tamS; i++)
        {
            printf("|       %-8s      |\n", servicios[i].descripcion);
            printf("|---------------------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}

int mostrarServicios(eServicio servicios[], int tamS)
{
    int todoOk = 0;

    if(servicios != NULL && tamS > 0)
    {
        system("cls");

        printf("|=======|=============|========|\n");
        printf("|  ID   |  SERVICIO   | PRECIO |\n");
        printf("|=======|=============|========|\n");
        for(int i = 0; i < tamS; i++)
        {
            printf("| %d |   %-8s  | %6.2f |\n", servicios[i].id, servicios[i].descripcion, servicios[i].precio);
            printf("|-------|-------------|--------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}

int listarTipos(eTipo tipos[], int tamT)
{
    int todoOk = 0;

    if(tipos != NULL && tamT > 0)
    {
        system("cls");

        printf("|=================|\n");
        printf("|  TIPOS DE MOTO  |\n");
        printf("|=================|\n");
        for(int i = 0; i < tamT; i++)
        {
            printf("|    %-7s      |\n", tipos[i].descripcion);
            printf("|-----------------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}


int mostrarTipos(eTipo tipos[], int tamT)
{
    int todoOk = 0;

    if(tipos != NULL && tamT > 0)
    {
        system("cls");

        printf("|======|================|\n");
        printf("|  ID  |  TIPOS DE MOTO |\n");
        printf("|======|================|\n");
        for(int i = 0; i < tamT; i++)
        {
            printf("| %d |    %-7s     |\n", tipos[i].id, tipos[i].descripcion);
            printf("|------|----------------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}


int cargarDescripcionTipo(int id, char descripcion[], eTipo tipos[], int tamT)
{
    int todoOk = 0;

    if(descripcion != NULL && tipos != NULL && tamT > 0)
    {
        for(int i = 0 ; i < tamT ; i++)
        {
            if(tipos[i].id == id)
            {
                strcpy(descripcion, tipos[i].descripcion);
                break;
            }
        }

        todoOk = 1;
    }
    return todoOk;
}

int inicializarTrabajos(eTrabajo trabajos[], int tamTr)
{
    int todoOk = 0;

    if(trabajos != NULL && tamTr > 0)
    {
        for(int i = 0; i < tamTr; i++)
        {
            trabajos[i].isEmpty = 1;
        }

        todoOk = 1;
    }

    return todoOk;
}

int buscarLibreTrabajo(eTrabajo trabajos[], int tamTr, int* pIndice)
{
    int todoOk = 0;
    int indice = -1;

    if(trabajos != NULL && tamTr > 0 && pIndice != NULL)
    {
        for(int i = 0; i < tamTr; i++)
        {
            if(trabajos[i].isEmpty)
            {
                indice = i;
                break;
            }
        }

        *pIndice = indice;
        todoOk = 1;

    }

    return todoOk;
}



int altaTrabajo(eTrabajo trabajos[], int tamTr, eMoto motos[], int tamM, eTipo tipos[], int tamT, eColor colores[], int tamC, eCliente clientes[], int tamCl, eServicio servicios[], int tamS, int* pNextId)
{
    int todoOk = 0;
    int indiceLibre;
    eTrabajo auxTrabajo;

    if(trabajos != NULL && tamTr > 0 && motos != NULL && tamM > 0 && tipos != NULL && tamT > 0 && colores != NULL && tamC > 0 && clientes != NULL && tamCl > 0 && servicios != NULL && tamS > 0 && pNextId != NULL)
    {
        system("cls");

        printf("        ***ALTA TRABAJOS*** \n");
        printf("----------------------------------\n");
        buscarLibreTrabajo(trabajos,tamTr, &indiceLibre);

        if(indiceLibre == -1)
        {
            printf("NO HAY LUGAR EN EL SISTEMA\n");
        }
        else
        {
            cargarTrabajo(&auxTrabajo, motos, tamM, colores, tamC, tipos, tamT, clientes, tamCl, servicios, tamS);
            auxTrabajo.id = *pNextId;
            *pNextId = *pNextId + 1;

            trabajos[indiceLibre] = auxTrabajo;
            todoOk = 1;
        }

    }

    return todoOk;
}




int cargarTrabajo(eTrabajo* pTrabajo, eMoto motos[], int tamM, eColor colores[], int tamC, eTipo tipos[], int tamT, eCliente clientes[], int tamCl, eServicio servicios[], int tamS)
{
    int todoOk = 0;
    int auxInt;
    eFecha auxFecha;

    if(pTrabajo != NULL && motos != NULL && tamM > 0 && colores != NULL && tamC > 0 && tipos != NULL && tamT > 0 && clientes != NULL && tamCl > 0 && servicios != NULL && tamS > 0)
    {
        mostarMotos(motos, tamM, colores, tamC, tipos, tamT, clientes, tamCl);
        printf("Ingrese el id de la moto: ");
        scanf("%d", &auxInt);
        //validacion
        pTrabajo->idMoto = auxInt;

        mostrarServicios(servicios, tamS);
        printf("Ingrese el id del servicio que desea realizar: ");
        scanf("%d", &auxInt);
        //validacion
        pTrabajo->idServicio = auxInt;

        printf("Ingrese fecha: ");
        scanf("%d/%d/%d", &auxFecha.dia, &auxFecha.mes, &auxFecha.anio);
        //validacion
        pTrabajo->fechaIngreso = auxFecha;

        pTrabajo->isEmpty = 0;

        todoOk = 1;
    }

    return todoOk;
}




int mostrarClientes(eCliente clientes[], int tamCl)
{
    int todoOk = 0;

    if(clientes != NULL && tamCl > 0)
    {
        system("cls");

        printf("|======|==================|======|\n");
        printf("|  ID  |  NOMBRE CLIENTE  | SEXO |\n");
        printf("|======|==================|======|\n");
        for(int i = 0; i < tamCl; i++)
        {
            printf("| %d |      %-10s  |  %c   |\n", clientes[i].id, clientes[i].nombre, clientes[i].sexo);
            printf("|------|------------------|------|\n");
        }


        todoOk = 1;
    }

    return todoOk;
}

int cargarNombreCliente(int id, char nombre[], eCliente clientes[], int tamCl)
{
    int todoOk = 0;

    if(nombre != NULL && clientes != NULL && tamCl> 0)
    {
        for(int i = 0 ; i < tamCl ; i++)
        {
            if(clientes[i].id == id)
            {
                strcpy(nombre, clientes[i].nombre);
                break;
            }
        }

        todoOk = 1;
    }
    return todoOk;
}
