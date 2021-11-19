# https://www.codingame.com/ide/puzzle/power-of-thor-episode-1

import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, tx, ty = [int(i) for i in input().split()]

# game loop
while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)
    if light_y == ty:
        if light_x > tx:
            print("E")
            tx = tx + 1
        else:
            print("W")
            tx = tx - 1

    if light_x == tx:            
        if light_y > ty:
            print("S")
            ty = ty + 1
        else:
            print("N")
            ty = ty - 1

    if light_x < tx and light_y > ty:
        print("SW")
        tx = tx - 1
        ty = ty + 1

    if light_x < tx and light_y < ty:
        print("NW")
        tx = tx - 1
        ty = ty - 1

    if light_x > tx and light_y > ty:
        print("SE")
        tx = tx + 1
        ty = ty + 1

    if light_x > tx and light_y < ty:
        print("NE")
        tx = tx + 1
        ty = ty - 1


    print("Thor = (", tx, ",", ty, ")", file=sys.stderr)

    # A single line providing the move to be made: N NE E SE S SW W or NW
    #print("SE")

