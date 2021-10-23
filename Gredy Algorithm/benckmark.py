from random import randint

NUMBER = [1000, 1500, 2500, 3000]

length = len(NUMBER)

for i in range(length):
    start = 1
    end = NUMBER[i]
    from_vertex = 1
    to_vertex = 1
    max_weight = 20

    with open(f'test_{NUMBER[i]}.txt', "w+") as file:
        file.write(f"{end} {end*end}\n")
        for i in range(1,end*end):
            from_vertex = randint(start,end)
            to_vertex = randint(start, end)
            w = randint(1, max_weight)
            while from_vertex >= to_vertex:
                from_vertex = randint(start, end)
                to_vertex = randint(start, end)
            file.write(f'{from_vertex} {to_vertex} {w}\n')