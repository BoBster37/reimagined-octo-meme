def rm_list(lista):
    return [x for x in lista if x % 2 == 0]

lista = [1,2,3,4,5,6,10,20]
print(rm_list(lista))