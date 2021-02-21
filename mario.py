# Get input from user between 1 and 8

while True:
    try:
        height = int(input("Height: "))
        if height < 1 or height > 8:
            False
        else:
            break
    except:
        print("Only numbers between 1 and 8 allowed")

for i in range(0, height, 1):
    for j in range(1,  height - i, 1):  # Print first space
        print(" ", end="")
    for k in range(0, i + 1, 1):        # Print fist hash
        print("#", end="")
    print("")