import random
import sys

''' 
Generador de vectores y matrices de costos
Recibe:
    tipo de archivo a crear (vector o matriz)
    tipo de matriz a crear (constante o variable)
    nombre del archivo a crear

Imprime resultado en el archivo especificado
'''
type = int(input("Ingrese tipo (1 matriz, 0 vector): "))
mode = int(input("Inserte modo (1 constante, 0 aleatorio): "))
if (mode!=0): val = int(input("Inserte valor: "))
filename = input("Inserte nombre de archivo: ")

f = open(filename, 'w')
sys.stdout = f

x=range(26)

if (type != 0):
    for i in x:
        for j in x:
            if (i==j): print(0,end=" ")
            else: 
                if mode:
                    print (val, end=" ")
                else: 
                    print (random.randint(1,9),end=" ")
        print ("")

else: 
    for i in x:
        if mode:
            print (val, end=" ")
        else: 
            print (random.randint(1,9),end=" ")

f.close()