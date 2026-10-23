#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#define STR_MAX 30

typedef struct {
    char marca[STR_MAX];
    char modelo[STR_MAX];
    char categoria;
    int anio;
    float precioPorDia;
    bool disponible;
} t_autos;

void verificador_categoria(char *c) {
    printf("\nCategoria (C=Compacto, S=Sedan, U=SUV, P=Pickup): ");
    scanf("%c", c);
    while (getchar() != '\n');
    *c = toupper(*c);
    while (*c != 'C' && *c != 'S' && *c != 'U' && *c != 'P') {
        puts("\nOpcion Invalida");
        puts("IMPORTANTE: Categorias disponibles (C=Compacto, S=Sedan, U=SUV, P=Pickup)");
        printf("Ingrese de nuevo: ");
        scanf("%c", c);
        while (getchar() != '\n');
        *c = toupper(*c);
    }
}

void verificador_anio(int *nro) {
    int min = 2006, max = 2026;
    printf("\nAnio (Desde %d hasta el anio actual (%d): ", min, max);
    while (scanf("%d", nro) != 1 || (*nro < min || *nro > max)) {
        while (getchar() != '\n');
        printf("\nAnio invalido, desde %d hasta el anio actual (%d): ", min, max);
    }
    while (getchar() != '\n');
}

void verificador_precio(float *precio) {
    float min = 10000;
    printf("\nPrecio por dia (Precio minimo $%.2f): ", min);
    while (scanf("%f", precio) != 1 || (*precio < min)) {
        while (getchar() != '\n');
        printf("\nPrecio invalido, el precio debe ser superior a $%.2f: ", min);
    }
    while (getchar() != '\n');
}

void verificador_disponibilidad(bool *d) {
    int disp;
    printf("\nDisponible (1:Si o 0:No): ");
    while (scanf("%d", &disp) != 1 || (disp != 0 && disp != 1)) {
        while (getchar() != '\n');
        printf("\nEntrada invalida, ingrese 1:Si o 0:No: ");
    }
    while (getchar() != '\n');
    *d = (bool) disp;
}

bool continuar() {
    char rta;
    printf("\nDeseas continuar (S:Si - N:No): ");
    scanf("%c", &rta);
    while (getchar() != '\n');
    rta = toupper(rta);
    while (rta != 'S' && rta != 'N') {
        printf("\nOpcion Invalida - (S:Si - N:No): ");
        scanf("%c", &rta);
        while (getchar() != '\n');
        rta = toupper(rta);
    }
    return rta == 'S';
}

void carga_datos(t_autos *m) {
    printf("\nMarca: ");
    scanf("%s", m->marca);
    while (getchar() != '\n');
    printf("\nModelo: ");
    scanf("%s", m->modelo);
    while (getchar() != '\n');

    verificador_categoria(&m->categoria);
    verificador_anio(&m->anio);
    verificador_precio(&m->precioPorDia);
    verificador_disponibilidad(&m->disponible);
}

void agregar_auto(t_autos *a) {
    FILE *f = fopen("autos.txt", "a");
    if (f == NULL) puts("Error al abrir el archivo");
    else {
        fprintf (f, "%s %s %c %d %.2f %d\n", a->marca, a->modelo, a->categoria, a->anio, a->precioPorDia, a->disponible);
        fclose(f);
    }
}

void listar_autos(int *filtro, char *categoria_buscada) {
    t_autos m;
    int disp;
    FILE *f = fopen("autos.txt", "r");
    if (f == NULL) puts("Error al abrir el archivo");

    else {
        printf("\n");
        for (int i=0; fscanf(f, "%s %s %c %d %f %d", m.marca, m.modelo, &m.categoria, &m.anio, &m.precioPorDia, &disp) == 6; i++) {
            m.disponible = (bool)disp;

            bool mostrar = false;
            if (*filtro == 2) mostrar = true;
            else if (*filtro == 3 && m.anio >= 2020) mostrar = true;
            else if (*filtro == 4 && categoria_buscada != NULL && m.categoria == *categoria_buscada) mostrar = true;

            if (mostrar) {
                printf("%-15s %-15s %-5c %-6d %-10.2f\n", m.marca, m.modelo, m.categoria, m.anio, m.precioPorDia);
            }
        }
        fclose(f);
    }
}

void generar_reporte_disponibilidad(bool *estado, int *opcion) {
    t_autos r;
    int disp, no_imprimir=7;

    FILE *f = fopen("autos.txt", "r");
    if (f == NULL) puts("\nError al abrir el archivo");
    else {
        FILE *f2 = fopen("autos_disponibles.txt", "w");
        if (f2 == NULL) puts("\nError al abrir el archivo");
        else {
            FILE *f3 = fopen("autos_ocupados.txt", "w");
            if (f3 == NULL) puts("\nError al abrir el archivo");

            else {
                for (int i=0; fscanf(f, "%s %s %c %d %f %d", r.marca, r.modelo, &r.categoria, &r.anio, &r.precioPorDia, &disp) == 6; i++) {
                    r.disponible = (bool) disp;
                    if (r.disponible) {
                        fprintf(f2, "%s %s %c %d %.2f %d\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia, r.disponible);
                    }
                    else fprintf(f3, "%s %s %c %d %.2f %d\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia, r.disponible);

                    if (*opcion != no_imprimir && estado != NULL && r.disponible == *estado) printf("%-15s %-15s %-5c %-6d %-10.2f\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia);
                }
                fclose(f);
                fclose(f2);
                fclose(f3);

                if (*opcion == no_imprimir) puts("\nArchivos: autos_disponibles.txt y autos_ocupados.txt generados con exito");
            }
        }
    }
}

void menu() {
    t_autos m;
    int opcion, disp;
    char categoria;
    bool estado;
    do {
        printf("\n1. Agregar un auto.\n"
           "2. Listado completo.\n"
           "3. Listado de autos modelo 2020 o mas nuevos.\n"
           "4. Busqueda por categoria.\n"
           "5. Ver autos ocupados.\n"
           "6. Ver autos disponibles.\n"
           "7. Generar reporte disponibles.\n"
           "0. Salir\n"
           "\nIngrese una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch (opcion) {
            case 0: {
                puts("Saliste del menu");
                break;
            }
            case 1: {
                do {
                    carga_datos(&m);
                    agregar_auto(&m);
                } while (continuar());
                break;
            }
            case 2: {
                listar_autos(&opcion, NULL);
                break;
            }
            case 3: {
                listar_autos(&opcion, NULL);
                break;
            }
            case 4: {
                do {
                    verificador_categoria(&categoria);
                    listar_autos(&opcion, &categoria);
                } while (continuar());
                break;
            }
            case 5: {
                puts("\nLista de Autos Ocupados");
                estado = false;
                generar_reporte_disponibilidad(&estado, &opcion);
                break;
            }
            case 6: {
                puts("\nLista de Autos Disponibles");
                estado = true;
                generar_reporte_disponibilidad(&estado, &opcion);
                break;
            }
            case 7: {
                generar_reporte_disponibilidad(NULL, &opcion);
                break;
            }
            default: {
                puts("Valor invalido");
                break;
            }
        }
    } while (opcion != 0);
}

int main() {
    menu();
    return 0;
}