# 🧩 Libasm — NASM x86_64 Library

![Language](https://img.shields.io/badge/language-NASM%20x86__64-blue)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![School](https://img.shields.io/badge/42-Madrid-black)
![License](https://img.shields.io/badge/license-MIT-yellow)

Implementación en **ensamblador NASM x86_64** de varias funciones estándar de la libc, siguiendo la **System V AMD64 ABI**, la sintaxis Intel y las normas del proyecto **42 Libasm**.

Este proyecto desarrolla una librería estática:

- `libasm.a` (mandatory)
- `libasm_bonus.a` (bonus)

---

## 📁 Estructura del proyecto

```
libasm/
│── main.c
│── README.md
│── Makefile
│── include/
│   └── libasm.h
│
├── srcs/
│   ├── Makefile
│   ├── mandatory/
│   │   ├── ft_strlen.s
│   │   ├── ft_strcpy.s
│   │   ├── ft_strcmp.s
│   │   ├── ft_write.s
│   │   ├── ft_read.s
│   │   └── ft_strdup.s
│   │
│   └── bonus/
│       ├── ft_atoi_base.s
│       ├── ft_list_push_front.s
│       ├── ft_list_size.s
│       ├── ft_list_sort.s
│       └── ft_list_remove_if.s
│
└── tests/
    ├── tests.h
    ├── test_strlen.c
    ├── test_strcpy.c
    ├── test_strcmp.c
    ├── test_write.c
    ├── test_read.c
    ├── test_strdup.c
    ├── test_atoi_base.c
    ├── test_list_push_front.c
    ├── test_list_size.c
    ├── test_list_sort.c
    └── test_list_remove_if.c
```

---

# 🚀 Compilación

### Mandatory:
```bash
make
```

### Bonus:
```bash
make bonus
```

### Ejecutar menú interactivo:
```bash
./main
```

### Ejecutar todos los tests:
```bash
make test
```

---

# 🧠 Funciones Mandatory

## 🔹 `ft_strlen`
Cuenta los caracteres de una cadena hasta `'\0'`.

**ASM:**  
- RAX = contador  
- Leer bytes desde `[RDI + RAX]`  
- Incrementar hasta encontrar 0  

---

## 🔹 `ft_strcpy`
Copia `src` en `dst` incluyendo el `'\0'`.

**ASM:**  
- Guardar `dst` en RAX  
- Copiar byte a byte  
- Parar al copiar `0`  

---

## 🔹 `ft_strcmp`
Compara dos cadenas lexicográficamente.

**ASM:**  
- Leer bytes de ambas  
- Si difieren → devolver resta  
- Si ambos son `0` → return 0  

---

## 🔹 `ft_write`
Wrapper de la syscall `write`.

**ASM:**  
- `RAX = 1`  
- `syscall`  
- Si error → setear `errno` con `__errno_location`  

---

## 🔹 `ft_read`
Wrapper de la syscall `read`.

**ASM:**  
- `RAX = 0`  
- `syscall`  
- Manejo de errores igual que `write`  

---

## 🔹 `ft_strdup`
Duplica una cadena usando `malloc`.

**ASM:**  
- Llamar a `ft_strlen`  
- Reservar memoria  
- Copiar con `ft_strcpy`  

---

# 🧠 Funciones Bonus

## 🔸 `ft_atoi_base`
Convierte un número en una base arbitraria a entero.

**ASM:**  
- Validar base  
- Saltar espacios  
- Detectar signo  
- Convertir usando índice en la base  

---

## 🔸 `ft_list_push_front`
Inserta un nodo al inicio de la lista.

**ASM:**  
- Reservar memoria  
- Asignar `data`  
- Enlazar con head  

---

## 🔸 `ft_list_size`
Cuenta los nodos de la lista.

**ASM:**  
- Recorrer `next`  
- Incrementar contador  

---

## 🔸 `ft_list_sort`
Ordena la lista usando bubble-sort.

**ASM:**  
- Dos bucles  
- Comparar `data`  
- Intercambiar si es necesario  

---

## 🔸 `ft_list_remove_if`
Elimina nodos cuyo `data` coincide con `ref`.

**ASM:**  
- Recorrer lista  
- Si `cmp(data, ref) == 0`:  
  - `free_fct(data)`  
  - Eliminar nodo  
  - Actualizar head  

---

# 🧪 Tests automáticos

Todos los tests están en `/tests` y se integran con un menú interactivo.

Ejecutarlos:
```bash
make test
```

---

# 👤 Autor

Proyecto realizado por **Jose**.

