from cs50 import get_string

# Get input text from user
text = get_string("Text: ")
 
# Count sentences by counting punctuation
sentences = text.count('!') + text.count('?') + text.count('.')

# Count words by counting spaces
words = sum(c.isspace() for c in text) + 1

# Count letters
letters = sum(c.isalpha() for c in text)

# Calculate index
L = letters * 100 / words
S = sentences * 100 / words
index = 0.0588 * L - 0.296 * S - 15.8

# Print out grade level index
# print(letters)
# print(words)
# print(sentences)

if index <= 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", round(index))