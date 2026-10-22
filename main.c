#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char marca[30];
    char modelo[30];
    char categoria;
    int anio;
    float precioPorDia;
    bool disponible;
} t_autos;

void verificador_categoria(char *c) {
    *c = toupper(*c);
    while (*c != 'C' && *c != 'S' && *c != 'U' && *c != 'P') {
        puts("Opcion Invalida");
        puts("IMPORTANTE: categorias disponibles (C=Chico/Compacto, S=Sedan, U=SUV, P=Pickup)");
        printf("Ingrese de nuevo la categoria: ");
        scanf("%c", &*c);
        while (getchar() != '\n');
        *c = toupper(*c);
    }
}

void generar_reporte_disponibilidad(bool *estado) {
    t_autos r;
    FILE *f = fopen("autos.txt", "r");
    if (f == NULL) puts("Error al abrir el archivo");
    else {
        FILE *f2 = fopen("autos_disponibles.txt", "w");
        if (f2 == NULL) puts("Error al abrir el archivo");
        else {
            FILE *f3 = fopen("autos_ocupados.txt", "w");
            if (f3 == NULL) puts("Error al abrir el archivo");

            else {
                for (int i=0; fscanf(f, "%s %s %c %d %f %d", r.marca, r.modelo, &r.categoria, &r.anio, &r.precioPorDia, &r.disponible) == 6; i++) {
                    if (r.disponible) {
                        fprintf(f2, "%s %s %c %d %.2f %d\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia, r.disponible);
                    }
                    else fprintf(f3, "%s %s %c %d %.2f %d\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia, r.disponible);
                    if (r.disponible == *estado) printf("%-15s %-15s %-5c %-6d %-10.2f\n", r.marca, r.modelo, r.categoria, r.anio, r.precioPorDia);
                }
                fclose(f);
                fclose(f2);
                fclose(f3);
            }
        }
    }
}

bool continuar(char *rta) {
    *rta = toupper(*rta);
    while (*rta != 'S' && *rta != 'N') {
        puts("Opcion Invalida - (S:Si - N:No)");
        scanf("%s", &*rta);
        while (getchar() != '\n');
        *rta = toupper(*rta);
    }
    return *rta == 'S';
}

void menu() {
    t_autos m;
    int menu;
    char categoria, rta_categoria;
    bool estado;
    do {
        printf("\n1. Agregar un auto.\n"
           "2. Listado completo.\n"
           "3. Listado de autos modelo 2020 o mas nuevos.\n"
           "4. Busqueda por categoria.\n"
           "5. Ver autos ocupados.\n"
           "6. Ver autos disponibles.\n"
           "0. Salir\n"
           "Ingrese una opcion: ");
        scanf("%d", &menu);
        while (getchar() != '\n');

        switch (menu) {
            case 0: {
                puts("Saliste del menu");
                break;
            }
            case 1: {
                break;
            }
            case 2: {
                printf("Listado completo: \n");
                FILE *f = fopen("autos.txt", "r");
                if (f == NULL) puts("Error al abrir el archivo");
                else {
                    for (int i=0; fscanf(f, "%s %s %c %d %f %d", m.marca, m.modelo, &m.categoria, &m.anio, &m.precioPorDia, &m.disponible) == 6; i++) {
                        printf("%-15s %-15s %-5c %-6d %-10.2f %-5d\n", m.marca, m.modelo, m.categoria, m.anio, m.precioPorDia, m.disponible);
                    }
                    fclose(f);
                }
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                do {
                    printf("Ingrese la categoria (C=Chico/Compacto, S=Sedan, U=SUV, P=Pickup): ");
                    scanf("%c", &categoria);
                    while (getchar() != '\n');
                    verificador_categoria(&categoria);
                    FILE *f = fopen("autos.txt", "r");
                    if (f == NULL) puts("Error al abrir el archivo");
                    else {
                        for (int i=0; fscanf(f, "%s %s %c %d %f %d", m.marca, m.modelo, &m.categoria, &m.anio, &m.precioPorDia, &m.disponible) == 6; i++) {
                            if (m.categoria == categoria) printf("%-15s %-15s %-5c %-6d %-10.2f\n", m.marca, m.modelo, m.categoria, m.anio, m.precioPorDia);
                        }
                        fclose(f);
                    }
                    printf("Deseas buscar otra categoria (S:Si - N:No): ");
                    scanf("%c", &rta_categoria);
                    while (getchar() != '\n');
                } while (continuar(&rta_categoria));
                break;
            }
            case 5: {
                puts("Lista de Autos Ocupados");
                estado = false;
                generar_reporte_disponibilidad(&estado);
                break;
            }
            case 6: {
                puts("Lista de Autos Disponobles");
                estado = true;
                generar_reporte_disponibilidad(&estado);
                break;
            }
            default: {
                puts("Valor invalido");
                break;
            }
        }
    } while (menu != 0);
}

int main() {

    menu();
    return 0;
}