# Trabajo Práctico - Programación 1

Trabajo práctico desarrollado para la cátedra de **Programación 1** en la **Universidad del Salvador (USAL)**.

---

## 📌 Información General

- **Materia:** Programación 1
- **Institución:** Universidad del Salvador (USAL)
- **Tema elegido:** Gestión de Alquiler / Administración de Autos

---

## 👥 Colaboradores

- Santiago Centeleghe
- Enzo Fraiese

---

## 🚗 Descripción del Proyecto

Programa desarrollado en lenguaje C enfocado en la gestión, administración y control de vehículos. Permite registrar automóviles, filtrar listados por año o categoría, consultar vehículos disponibles u ocupados, y generar reportes exportados automáticamente a archivos de texto.

---

## ⚙️ Estructura de Datos y Validaciones

El sistema utiliza una estructura (`t_autos`) para almacenar la información de cada vehículo:
- **`marca`**: Cadena de caracteres (hasta 30 caracteres).
- **`modelo`**: Cadena de caracteres (hasta 30 caracteres).
- **`categoria`**: Carácter que representa el segmento (`C` = Compacto, `S` = Sedán, `U` = SUV, `P` = Pickup). Validado mediante `toupper`.
- **`anio`**: Entero que indica el año de fabricación (rango válido desde 2006 hasta 2026).
- **`precioPorDia`**: Número flotante que representa el costo diario de alquiler (mínimo $10,000.00).
- **`disponible`**: Valor booleano (`true`/`false` ingresado como `1` o `0`) que indica si el auto está disponible u ocupado.

---

## 📋 Menú de Opciones

El programa cuenta con un menú interactivo con las siguientes funcionalidades:

1. **Agregar un auto**: Permite ingresar los datos de un nuevo vehículo con sus respectivas validaciones y lo almacena en `autos.txt`.
2. **Listado completo**: Muestra todos los vehículos registrados en el archivo.
3. **Listado de autos modelo 2020 o más nuevos**: Filtra y muestra únicamente los vehículos con año de fabricación mayor o igual a 2020.
4. **Búsqueda por categoría**: Solicita una categoría específica y lista los vehículos coincidentes.
5. **Ver autos ocupados**: Filtra en tiempo de ejecución y muestra los autos que se encuentran actualmente ocupados (`disponible = false`).
6. **Ver autos disponibles**: Filtra en tiempo de ejecución y muestra los autos disponibles para alquilar (`disponible = true`).
7. **Generar reporte disponibles**: Exporta y divide los registros almacenados en dos archivos independientes: `autos_disponibles.txt` y `autos_ocupados.txt`.
0. **Salir**: Finaliza la ejecución del programa.

---

## 📁 Archivos del Sistema

- **`autos.txt`**: Archivo principal donde se almacenan todos los registros de vehículos ingresados.
- **`autos_disponibles.txt`**: Archivo generado mediante el reporte con los vehículos disponibles.
- **`autos_ocupados.txt`**: Archivo generado mediante el reporte con los vehículos ocupados.

---

## 🛠️ Compilación y Ejecución

Para compilar y ejecutar el programa desde la terminal utilizando `gcc`:

```bash
# Compilar el programa
gcc main.c -o main

# Ejecutar el programa
./main
```
