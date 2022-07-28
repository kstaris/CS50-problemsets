# TODO
import cs50


height = 0
while height < 1 or height > 8:
    height = cs50.get_int("Input the height of pyramid (1..8)")
for i in range(1, height+1):
    j = height - i
    print(" " * j + "#" * i + "  " + "#" * i)