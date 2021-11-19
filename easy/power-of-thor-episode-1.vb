' https://www.codingame.com/training/easy/power-of-thor-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.
' ---
' Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

    Sub Main ()
        
        Dim inputs as String()
        Dim lightX as Integer ' the X position of the light of power
        Dim lightY as Integer ' the Y position of the light of power
        Dim initialTX as Integer ' Thor's starting X position
        Dim initialTY as Integer ' Thor's starting Y position
        inputs = Console.ReadLine().Split(" ")
        lightX = inputs(0)
        lightY = inputs(1)
        initialTX = inputs(2)
        initialTY = inputs(3)

        ' game loop
        While True
            Dim remainingTurns as Integer
            remainingTurns = Console.ReadLine() ' The remaining amount of turns Thor can move. Do not remove this line.

            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")
            
            
            if initialTX<lightX then
              if  initialTY<lightY then
                 Console.WriteLine("SE")
                 initialTX=initialTX+1
                 initialTY=initialTY+1
              end if 
              if initialTY=lightY then
                 Console.WriteLine("E")
                 initialTX=initialTX+1
              end if
              if initialTY>lightY then
                 Console.WriteLine("NE")
                 initialTX=initialTX-1
                 initialTY=initialTY+1
              end if
            end if

            if initialTX>lightX then
              if  initialTY<lightY then
                 Console.WriteLine("SW")
                 initialTX=initialTX-1
                 initialTY=initialTY+1
              end if 
              if initialTY=lightY then
                 Console.WriteLine("W")
                 initialTX=initialTX-1
             end if     
                 
              if initialTY>lightY then
                 Console.WriteLine("NW")
                 initialTX=initialTX-1
                 initialTY=initialTY+1
              end if
            end if

            if initialTX=lightX then
              if  initialTY<lightY then
                 Console.WriteLine("S")
                 initialTY=initialTY+1
              end if 
              if initialTY>lightY then
                 Console.WriteLine("N")
                  initialTY=initialTY-1
              end if
           end if


            ' A single line providing the move to be made: N NE E SE S SW W or NW
           
        End While
    End Sub
End Module
