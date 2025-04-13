# Sistema de gestión de tickets de soporte técnico
Realizado por Hans Gonzalez

## Descripción

Este sistema permite la gestión de tickets de un soporte técnico. Los usuarios pueden registrar su ID y descripcion, asignar prioridades (incluso si es bajo, se debe volver a colocar), ver la lista de espera, tambien el sistema tiene la capacidad de procesar ticket y buscar ticket por ID.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).
- Ademas de tener github, para tener los archivos necesarios, con el link para clonarlos en visual studio (https://github.com/HANSGONZALEZ340/Tarea_1_estructura_de_datos).

### Pasos para compilar y ejecutar:
**Paso 1: Copiar el enlace de github y usarlo en visual studio para tener acceso a los datos**

**Paso 2: Al ya tener todos los componentes necesarios, se debe abrir una nueva terminal y colocar lo siguiente (gcc main.c list.c -o programa
.\programa) de esta forma funcionaria el codigo del sitema de gestion de ticket**

## Funcionalidades ##
### Funcionando correctamente:

- Registrar tickets con su ID(unico) y descripcion.
- Asignar o modificar la prioridad.
- Ver la lista de espera de los tickets, ordenada por prioridad y hora de registro.
- procesar al siguiente ticket, respetando el orden de prioridad.
- Buscar el ticket a traves del ID

### Problemas conocidos:

- Al asignar prioridad, igualmente se debe asignar los tickets de prioridad Baja, ya que el sistema realmente al principio, estan en lista general, asi que incluso si tosos son bajos, deben obligatoriamente declarar el ticket como bajo(o lo que corresponda)

### A mejorar:

- Implementar que si la prioridad es baja, no se deba volver a asignarla.

## Ejemplo de uso

**Paso 1: Registrar un ticket**

Se comienza registrandando un ticket con su ID y descripcion

```
Seleccione una opcion;1
Ingresa ID: 22069096
Ingrese la descripcion del ticket: Fallo de pantalla
Ticket registrado con ID 22069096 y prioridad 'Bajo'
```

El sistema registra al ID 22069096 con una prioridad inicial "Bajo" y guarda la hora actual de registro. Aunque de dice dar una prioridad Baja, si o si en caso que de verdad sea baja, se le debe asignar la prioridad manualmente, sin importar que sea alto, medio o bajo.

**Paso 2: Asignar Prioridad al tickete**

El usuario asigna una prioridad, incluso si es baja, se le debe colocar. Para hacerlo solo debe colocar su ID y asignar prioridad.

```
Seleccione una opcion;2
Ingresa el ID del ticket a asignar prioridad: 22069096
Ingrese la nueva prioridad (Alto, Medio, Bajo): Bajo    
Prioridad del ticket con ID 22069096 cambiada a 'Bajo'.
```

El sistema actualiza la prioridad del ticket, el cual estrara en lista de espera y posterior procesacion.

**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera de todos los tickets.

```
Seleccione una opcion;3

---Tickets Pendientes---
ID: 22069096, Descripcion: Fallo de pantalla, Prioridad: Bajo, Hora: 13:13
```

La lista muestra de forma ordenada los tickets de espera, donde muestra el ID, la descripcion, la prioridad y la hora.

**Paso 4: Procesar el siguiente ticket**

El ticket es procesado a traves de su prioridad y hora de llegada (resgistro).
```
Seleccione una opcion;4

Procesando el Ticket:
ID: 22069096, Descripcion: Fallo de pantalla, Prioridad: Bajo, Hora de llegada: 13:13
Ticket procesado y eliminado de la lista de prioridad
```

El sistema muestra que es procesado y es elimano de la lista de prioridad, sacando de la lista de espera.

**Paso 5: Buscar ticket por ID"**

A traves del Id, se puede observar la informacion del ticket
```
Seleccione una opcion;5
Ingresa el ID del ticket a buscar: 22069096
Ticket encontrado:
ID: 22069096
Descripcion: Fallo de pantalla
Prioridad: Bajo
Hora de llegada: 13:13
```
Incluso despues de ser procesado, se puede ver la informacion del ID del ticket.
