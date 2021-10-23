import time

start = time.time()

while True:
    try:
        num1 = int(input())

    except:
        break
    num2 = int(input())
    op = input()

    if(op == '+'):
        print(num1+num2)

    elif(op == '-'):
        if num1 < num2:
            print("Error")       
        else:
            print(num1 - num2)


    elif(op == '*'):
        print(num1 * num2)

    elif(op == '/'):
        if(num2 == 0):
            print("Error")
        else:
            print(num1 // num2)
    elif(op == '^'):
        if(num1 == num2 == 0):
            print("Error")
        else:
            print(num1**num2)    
    else:
        print("Error")

end = time.time()

print("TIme:" + str(end - start) + "s")