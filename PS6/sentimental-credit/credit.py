# TODO
import cs50

number = cs50.get_string("Number: ")
sum = 0
length = len(number)
for i in range(1,length+1):
    if i % 2 == 0:
        num = number[len(number)-i]
        if int(num) > 4:
            num = int(num)*2
            num = str(num)
            sum = sum + int(num[0])+int(num[1])
        else:
            sum = sum + int(number[len(number)-i])*2
    else:
        sum = sum + int(number[len(number)-i])
if sum%10 == 0:
    math = True
else:
    math = False
if length == 15 and (number[:2] == "34" or number[:2] == "37"):
    print("AMEX")
if length == 16 and (number[:2] == "51" or number[:2] == "52" or number[:2] == "53"or number[:2] == "54"or number[:2] == "55"):
    print("MASTERCARD")
if (length == 13 or length == 16) and number[:1] == "4":
    print("VISA")
else:
    print("INVALID")

