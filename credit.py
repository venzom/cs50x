# Accept credit card number, make sure number is greater than 1
while True:
    try:
        n = int(input("Number: "))
        if n < 0:
            False
        else:
            break
    except:
        print(end="")

# Lenght of number entered
lenght = len(str(n))

# Create credit card array
cc = [int(x) for x in str(n)]

# Multiply each digit by 2, starting with the second to las digit,
# then add the products digits together 
multiply = addDigits = 0
for i in range(lenght - 2, -1, -2):
    multiply = (cc[i] * 2)
    addDigits += sum(int(digit) for digit in str(multiply))

# Add digits not multiplied by 2 to sum
for i in range(lenght, 0, -2):
    addDigits += cc[i-1]

# Check if last digit is zero
checkZero = addDigits % 10    

# Check each for validity of number entered
if lenght < 13 or lenght > 16:
    print("INVALID")
# Check if number is VISA    
elif ((lenght == 13 or lenght == 16) and cc[0] == 4):
    print("VISA")
# Check if number is AMEX
elif (lenght == 15 and cc[0] == 3 and (cc[1] == 4 or cc[1] == 7)):
    print("AMEX")
# Check if number is MASTERCARD    
elif (lenght == 16 and cc[0] == 5 and 1 <= cc[1] <= 5):
    print("MASTERCARD")
# Invalid if no matches    
else:
    print("INVALID")