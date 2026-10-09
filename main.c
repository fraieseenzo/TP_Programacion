#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char modelo[30];
    char categoria;
    int anio;
    float precioPorDia;
    bool disponible;
} t_autos;


void menu() {
    int menu;
    printf("\n1.Aniadir un auto.\n2.Listado completo.\n3.Listado de autos modelo 2020 o mas nuevos.\n4.Busqueda por categoria.\n"
           "5.Ver autos ocupados.\n6.Ver autos disponibles.\n0.Salir\nIngrese una opcion: ");
    scanf("%d", &menu);
    do {
        switch (menu) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            default: {
                break;
            }
        }
    } while (menu != 0);
}

int main() {
    t_autos autos;

    printf("Hello, World!\n");
    return 0;
}