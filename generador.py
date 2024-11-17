from random import randint
import sys

arch1=open("S1.txt","w")
arch2=open("S2.txt","w")
arch3=open("S3.txt","w")

sys.stdout = arch1
for i in range(100001):
	print(chr(randint(97,122)), end="")

sys.stdout = arch2
for i in range(100001):
	print(chr(randint(97,122)), end="")

sys.stdout = arch3
for i in range(100001):
	print("a", end="")