#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //buscado para registrar hora de llegada
#include "list.h"

typedef struct Ticket
{
    int id;
    char descripcion[256];
    char prioridad[10];
    time_t hora_llegada;
} Ticket;

//funcion investigada para mostrar hora y minutos de llegada
void mostrarHora(time_t hora) 
{
    char buffer[6];
    struct tm* tiempo = localtime(&hora);
    strftime(buffer, sizeof(buffer), "%H:%M", tiempo);
    printf("%s", buffer);
}

void mostrarMenu()
{
    printf("\n---MENU---\n");
    printf("1.Registrar ticket\n");
    printf("2.Asignar prioridad\n");
    printf("3.Mostrar tickets pendientes\n");
    printf("4.Procesar el siguiente ticket\n");
    printf("5.Buscar ticket por ID\n");
    printf("0.Salir\n");
    printf("Seleccione una opcion;");
}

//verifica que no se repitan los ID
int idExiste(List* lista, int id)
{
    void* ptr = firstList(lista);
    while (ptr != NULL)
    {
        Ticket* t = (Ticket*)ptr;
        if (t->id == id) return 1;
        ptr = nextList(lista);
    }
}

void registrar(List* lista_general)
{
    int id;
    char descripcion[256];
    printf("Ingresa ID: ");
    scanf("%d", &id);
    getchar();

    if (idExiste(lista_general, id))
    {
        printf("Ya existe un ticket con esta ID\n");
        return;
    }
    printf("Ingrese la descripcion del ticket: ");
    fgets(descripcion, 256, stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0';
    Ticket* nuevo_Ticket = (Ticket*)malloc(sizeof(Ticket));
    if (nuevo_Ticket == NULL) return;

    nuevo_Ticket->id = id;
    strcpy(nuevo_Ticket->descripcion, descripcion);
    strcpy(nuevo_Ticket->prioridad, "Bajo");
    nuevo_Ticket->hora_llegada = time(NULL);

    pushBack(lista_general, nuevo_Ticket);
    printf("Ticket registrado con ID %d y prioridad 'Bajo'\n", id);
}

void asignar_prioridad(List* lista_general, List* lista_alto, List* lista_medio, List* lista_bajo)
{
    int id;
    char prioridad[10];
    int encontrado = 0;

    printf("Ingresa el ID del ticket a asignar prioridad: ");
    scanf("%d", &id);
    getchar();
    printf("Ingrese la nueva prioridad (Alto, Medio, Bajo): ");
    fgets(prioridad, sizeof(prioridad), stdin);
    prioridad[strcspn(prioridad, "\n")] = '\0';

    void* ptr = firstList(lista_general);
    while (ptr != NULL)
    {
        Ticket* t = (Ticket*)ptr;
        if (t->id == id)
        {
            strcpy(t->prioridad, prioridad);
            encontrado = 1;

            if (strcmp(prioridad, "Alto") == 0){
                pushBack(lista_alto, t);
            } else if (strcmp(prioridad, "Medio") == 0){
                pushBack(lista_medio, t);
            } else if (strcmp(prioridad, "Bajo") == 0){
                pushBack(lista_bajo, t);
            } else{
                printf("Prioridad Invalida\n");
                return;
            }
            break;
        }
        ptr = nextList(lista_general);
    }
    if (!encontrado){
        printf("No se encontro un ticket con ID %d.\n", id);
    } else{
        printf("Prioridad del ticket con ID %d cambiada a '%s'.\n", id, prioridad);
    }
}

void mostrarTicketsPorLista(List* lista, const char* prioridad)
{
    List* copia = createList();
    void* ptr = firstList(lista);
    while (ptr != NULL)
    {
        pushBack(copia, ptr);
        ptr = nextList(lista);
    }
    //(metodo de la burbuja) Orden por hora de llegada
    for (Node* i = copia->head; i && i->next; i = i->next)
    {
        for (Node* j = i->next; j; j = j->next)
        {
            Ticket* t1 = (Ticket*)i->data;
            Ticket* t2 = (Ticket*)j->data;
            if (t1->hora_llegada > t2->hora_llegada)
            {
                void* tmp = i->data;
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
    ptr = firstList(copia);
    while (ptr != NULL)
    {
        Ticket* t = (Ticket*)ptr;
        printf("ID: %d, Descripcion: %s, Prioridad: %s, Hora: ", t->id, t->descripcion, prioridad);
        mostrarHora(t->hora_llegada);
        printf("\n");
        ptr = nextList(copia);
    }
}

void mostrarTickets(List* lista_bajo, List* lista_medio, List* lista_alto)
{
    printf("\n---Tickets Pendientes---\n");
    if (!firstList(lista_alto) && !firstList(lista_medio) && !firstList(lista_bajo))
    {
        printf("No hay tickets registrados\n");
        return;
    }
    mostrarTicketsPorLista(lista_alto, "Alto");
    mostrarTicketsPorLista(lista_medio, "Medio");
    mostrarTicketsPorLista(lista_bajo, "Bajo");
}

void procesarSiguiente(List* lista_alto, List* lista_medio, List* lista_bajo)
{
    List* lista_objetivo = NULL;
    Ticket* ticket_a_procesar = NULL;

    // Revisamos primero la lista de alta prioridad
    void* ptr = firstList(lista_alto);
    if (ptr != NULL)
    {
        ticket_a_procesar = (Ticket*)ptr;
        lista_objetivo = lista_alto;
    }
    else
    {
        ptr = firstList(lista_medio);
        if (ptr != NULL)
        {
            ticket_a_procesar = (Ticket*)ptr;
            lista_objetivo = lista_medio;
        }
        else
        {
            ptr = firstList(lista_bajo);
            if (ptr != NULL)
            {
                ticket_a_procesar = (Ticket*)ptr;
                lista_objetivo = lista_bajo;
            }
        }
    }

    if (ticket_a_procesar)
    {
        printf("\nProcesando el Ticket:\n");
        printf("ID: %d, Descripcion: %s, Prioridad: %s, Hora de llegada: ", ticket_a_procesar->id, ticket_a_procesar->descripcion, ticket_a_procesar->prioridad);

        mostrarHora(ticket_a_procesar->hora_llegada);
        printf("\n");
        popFront(lista_objetivo);
        printf("Ticket procesado y eliminado de la lista de prioridad\n");
    } else printf("No hay tickets pendientes\n");
}

void buscar(List* list_general)
{
    int id;
    printf("Ingresa el ID del ticket a buscar: ");
    scanf("%d", &id);
    getchar();
    void* ptr = firstList(list_general);
    while (ptr != NULL)
    {
        Ticket* t = (Ticket*)ptr;
        if (t->id == id)
        {
            printf("Ticket encontrado:\n");
            printf("ID: %d\n", t->id);
            printf("Descripcion: %s\n", t->descripcion);
            printf("Prioridad: %s\n", t->prioridad);
            printf("Hora de llegada: ");
            mostrarHora(t->hora_llegada);
            printf("\n");
            return;
        }
        ptr = nextList(list_general);
    }
    printf("No se encontro un ticket con ID %d.\n", id);
}

int main()
{
    List* lista_general = createList();
    List* lista_bajo = createList();
    List* lista_medio = createList();
    List* lista_alto = createList();

    int opcion;
    do
    {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();
        switch(opcion)
        {
            case 1:
                registrar(lista_general);
                break;
            case 2:
                asignar_prioridad(lista_general, lista_alto, lista_medio, lista_bajo);
                break;
            case 3:
                mostrarTickets(lista_bajo, lista_medio, lista_alto);
                break;
            case 4:
                procesarSiguiente(lista_alto, lista_medio, lista_bajo);
                break;
            case 5:
                buscar(lista_general);
                break;
            case 0:
                printf("Saliendo.....\n");
                break;
            default:
                printf("Opcion Invalida\n"); 
                break;
        }
    } while (opcion != 0);
    
    return 0;
}