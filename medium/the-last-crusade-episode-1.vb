' https://www.codingame.com/training/medium/the-last-crusade-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        Dim inputs as String()

        Dim W as Integer ' number of columns.
        Dim H as Integer ' number of rows.
        inputs = Console.ReadLine().Split(" ")
        W = inputs(0)
        H = inputs(1)

        Dim LINE as String()
        Dim Grid(H,W) as Integer
        For i as Integer = 0 To H-1 
            LINE = Console.ReadLine().Split(" ") ' represents a line in the grid and contains W integers. Each integer represents one room of a given type.
            For j as Integer = 0 to W-1
              grid(i,j)=LINE(j)
         '     Console.Error.WriteLine(LINE(j))
          '    Console.Error.WriteLine(i & " " & j & " " & grid(i,j))
            Next
        Next

        Dim EX as Integer
        EX = Console.ReadLine() ' the coordinate along the X axis of the exit (not useful for this first mission, but must be read).

        ' game loop
        While True
            Dim XI as Integer
            Dim YI as Integer
            Dim X as Integer
            Dim Y as Integer            
            Dim POS as String
            inputs = Console.ReadLine().Split(" ")
            XI = inputs(0)
            YI = inputs(1)
            POS = inputs(2)

            y=YI
            x=XI
            
            IF grid(YI,XI)=1 then
              y=YI+1
            ELSE IF grid(YI,XI)=2 then
              If POS="LEFT" then
                x=XI+1
              End if              
              If POS="RIGHT" then
                x=XI-1
              End if              
            ELSE IF grid(YI,XI)=3 then
              If POS="TOP" then
                y=YI+1
              End if
            ELSE IF grid(YI,XI)=4 then
              If POS="TOP" then
                x=XI-1
              End if              
              If POS="RIGHT" then
                y=YI+1
              End if 
            ELSE IF grid(YI,XI)=5 then
              If POS="TOP" then
                x=XI+1
              End if              
              If POS="LEFT" then
                y=YI+1
              End if 
            ELSE IF grid(YI,XI)=6 then
              If POS="LEFT" then
                x=XI+1
              End if              
              If POS="RIGHT" then
                x=XI-1
              End if 
            ELSE IF grid(YI,XI)=7 then
               y=YI+1
            ELSE IF grid(YI,XI)=8 then
               y=YI+1
           ELSE IF grid(YI,XI)=9 then
               y=YI+1
           ELSE IF grid(YI,XI)=10 then
               x=XI-1
           ELSE IF grid(YI,XI)=11 then
               x=XI+1
            ELSE IF grid(YI,XI)=12 then
               y=YI+1
            ELSE IF grid(YI,XI)=13 then
               y=YI+1               
            end if
            
          '  Console.Error.WriteLine(YI & " " & XI & " " & grid(YI,XI))
            
            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")


            ' One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
            Console.WriteLine(x & " " & y)
        End While
    End Sub
End Module
