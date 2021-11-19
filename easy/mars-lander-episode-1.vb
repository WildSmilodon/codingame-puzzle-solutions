' /https://www.codingame.com/training/easy/mars-lander-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        Dim inputs as String()
        Dim surfaceN as Integer
        surfaceN = Console.ReadLine() ' the number of points used to draw the surface of Mars.

        For i as Integer = 0 To surfaceN-1

            Dim landX as Integer ' X coordinate of a surface point. (0 to 6999)
            Dim landY as Integer ' Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
            inputs = Console.ReadLine().Split(" ")
            landX = inputs(0)
            landY = inputs(1)

        Next

        ' game loop
        While True
            Dim X as Integer
            Dim Y as Integer
            Dim hSpeed as Integer ' the horizontal speed (in m/s), can be negative.
            Dim vSpeed as Integer ' the vertical speed (in m/s), can be negative.
            Dim fuel as Integer ' the quantity of remaining fuel in liters.
            Dim rotate as Integer ' the rotation angle in degrees (-90 to 90).
            Dim power as Integer ' the thrust power (0 to 4).
            inputs = Console.ReadLine().Split(" ")
            X = inputs(0)
            Y = inputs(1)
            hSpeed = inputs(2)
            vSpeed = inputs(3)
            fuel = inputs(4)
            rotate = inputs(5)
            power = inputs(6)

            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")
            if vspeed<-35 then
              power=4
            else
              power=3
            end if
            Console.WriteLine("0 "& power)
            ' 2 integers: rotate power. rotate is the desired rotation angle (should be 0 for level 1), power is the desired thrust power (0 to 4).
        '    Console.WriteLine("0 3")
        End While
    End Sub
End Module
