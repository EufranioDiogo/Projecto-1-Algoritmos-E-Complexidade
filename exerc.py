flag = -1
lista = [1, 2, 1, 2, 3, 4]

for i in range(len(lista) - 1):
    if lista[i] == 2:
        flag = 0
        lista[i] = lista[i + 1]
    elif flag == 0:
        lista[i] = lista[i + 1]
print(lista)