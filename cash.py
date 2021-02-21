# Get user to input change owed
while True:
    try:
        cents = float(input("Change owed: "))
        if cents < 0:
            False
        else:
            break
    except:
        print("Please enter a positive number only")

# Calculate how many coins it will take to give change

cents = cents * 100
coins = 0

while cents > 0:
    if (cents >= 25):
        cents = cents - 25
        coins += 1
    elif (cents >= 10):
        cents = cents - 10
        coins += 1
    elif (cents >= 5):
        cents = cents - 5
        coins += 1
    elif (cents >= 1):
        cents = cents - 1
        coins += 1
    else:
        break

print(coins)