def func(x):
    min = int(input("podaj min: "))
    max = int(input("podaj max: "))
    if x>=min and x <= max:
        print("wartosc jest miedzy min and max")
    else:
        print("wartosc nie jest miedzy min and max")

func(15)