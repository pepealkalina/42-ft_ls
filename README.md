# ft_ls

![Language](https://img.shields.io/badge/language-C-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

## 🗣️ Introducción

**ft_ls** es mi propia implementación del famoso comando de Unix `ls`. Su objetivo principal es comprender cómo interactúa el sistema operativo con el sistema de archivos, manejar estructuras de datos complejas y gestionar la memoria de forma eficiente en C.

El programa lista información sobre los archivos y directorios dentro del sistema de archivos, replicando el comportamiento de las flags más comunes del comando original.

---

## 🚀 Características

`ft_ls` soporta las siguientes funcionalidades y flags:

* **Listado básico:** Muestra los archivos del directorio actual o especificado.
* **Manejo de errores:** Gestión robusta de permisos denegados, archivos no existentes, etc.
* **Flags implementadas:**
    * `-l` : **Formato largo.** Muestra permisos, número de enlaces, propietario, grupo, tamaño y fecha de modificación.
    * `-a` : **Todo.** Incluye archivos ocultos (los que empiezan por `.`).
    * `-R` : **Recursivo.** Lista subdirectorios recursivamente.
    * `-r` : **Reverso.** Invierte el orden de clasificación.
    * `-t` : **Tiempo.** Ordena por fecha de modificación (del más nuevo al más antiguo).
* **Combinación de flags:** Soporta combinaciones como `-lart` o `-Rla`.

---

## 🛠️ Instalación y Compilación

Este proyecto está escrito en C y diseñado para compilarse en sistemas Unix/Linux/macOS.

### Requisitos
* `gcc` o `clang`
* `make`

### Pasos
1.  Clona el repositorio:
    ```bash
    git clone [https://github.com/tu-usuario/ft-ls.git](https://github.com/tu-usuario/ft-ls.git)
    cd ft-ls
    ```

2.  Compila el proyecto ejecutando:
    ```bash
    make
    ```
    Esto generará el ejecutable `ft_ls` en la raíz del directorio.

3.  (Opcional) Para limpiar archivos objeto:
    ```bash
    make clean
    ```
    Para limpiar todo (objetos y ejecutable):
    ```bash
    make fclean
    ```

---

## 💻 Uso

La sintaxis es idéntica a la del comando original:

```bash
./ft_ls [FLAGS] [ARCHIVOS/DIRECTORIOS]
