# TODO
import cs50

text = cs50.get_string("Text: ")
letters = 0
words = 1
sentences = 0
for i in text:
    if i.isalpha():
        letters += 1
    if i.isspace():
        words += 1
    if (i == "!") or (i == ".") or (i == "?"):
        sentences += 1
avL = letters * 100 / words
avS = sentences * 100 / words
index = round(0.0588 * avL - 0.296 * avS - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade " + str(index))