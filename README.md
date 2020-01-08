# iShell


Transforma una conexión simple de una reverse shell de GNU, en interactiva.

## Pre-Usage

```
g++ ishell.cpp -o ishell
```
## Usage
Importante usar como adminroot ya que para enviar comandos entre terminales es necesario.
```
sudo ishell <fd-pts> <pid>
```
## Example
Hay que saber el pid del proceso de la reveseshell y el file descriptor de nuestra shell que hemos ejecutado y ya tenemos conexión de la victima.
```
En local:
ps -aux | grep "nc -lvnp"
wanetty 27292  0.0  0.0   7956  1876 pts/4    S+   15:37   0:00 nc -lvp 1111
wanetty 27340  0.0  0.0  12780   924 pts/3    S+   15:38   0:00 grep --color=auto nc -lvp

Ejecución:
sudo ishell /dev/pts/4 27292
```
OneLiner usage:

```
sudo ./ishell $(ps -aux | grep "nc -lv" | sort -n | awk -F" " '{print "/dev/"$7" "$2}' | head -n 1)
```

## TODO:
- Automatizar la recogida del FileDescriptor y el Pid del proceso que se está ejecutando

## Created by Wanetty
