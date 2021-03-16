import csv
import sys
import re, collections

def main():

    # Ensure correct usage with 2 command-line arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    
    
    # Read database list into memory
    names = []
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        strs = next(reader)
        for row in reader:
            names.append(row)
    
    # Read sequence into memory      
    with open(sys.argv[2], "r") as file:
        sequence = file.read()
    
    # Look for each STR from database in sequence and count each occurance
    strCount = (count_STRs(sequence, strs))
    print(strs[1:])
    print(strCount)
    # Print match or no match
    print(count_matches(names, strCount))
    
def count_STRs(sequence, strs):
    
    # Look for each STR from database in sequence and count each occurance
    strCount = []
    
    for j in range(1, len(strs)):
        l = len(strs[j])
        count = 0
        countMax = 0
        for i in range(len(sequence)):
            while count > 0:
                count -= 1
                continue
            if sequence[i: i + l] == strs[j]:
                while sequence[i - l: i] == sequence[i: i + l]:
                    count += 1
                    i += l
                if count > countMax:
                    countMax = count
        countMax += 1
        strCount.append(str(countMax))
        
    return strCount    
        
def count_matches(names, strCount):
    
    # Match the count to name in database and return name or not found
    for i in range(len(names)):
        count = 0
        for j in range(len(strCount)):
            if(strCount[j] == names[i][j+1]):
                count += 1
            if count == len(strCount):
                return names[i][0]
    return "No match"        
    
        
if __name__ == "__main__":
    main()