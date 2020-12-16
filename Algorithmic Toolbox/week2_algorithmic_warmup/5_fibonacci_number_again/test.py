#!/bin/python

n, m = [int(x) for x in input().split()]

def find_pisano(n, m):
    pisano = []
    pisano.append(0)

    # при делении на 1 остаток будет всегда 0
    if m == 1:
        return pisano

    pisano.append(1)

    # при m > 0 остатки от деления первого и второго числа Фибоначчи
    # всегда 0 и 1
    if n <= 1:
        return pisano

    n0 = 0
    n1 = 1
    for __ in range(m * 6):
        # для ускорения не вычисляем числа Фибоначчи полностью
        # берём только остатки по модулю m
        n0, n1 = n1, (n0 + n1) % m

        pisano.append(n1 % m)

        # Проверяем не начался ли новый период 
        # период всегда начинается с 0 и 1
        if pisano[len(pisano) - 1] == 1 \
            and pisano[len(pisano) - 2] == 0:
            break

    return pisano[:-2]

pisano = find_pisano(n, m)
print(pisano)
print(pisano[n % len(pisano)])