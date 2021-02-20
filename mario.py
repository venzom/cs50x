height = 0
while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(0, height, 1):
    for j in range(1,  height - i, 1):
        print(" ", end ="")
    for k in range(0, i + 1, 1):
        print("#", end ="")
    print("  ", end ="")
    for j in range(0, i + 1, 1):
        print("#", end ="")
    print("\n", end ="")
