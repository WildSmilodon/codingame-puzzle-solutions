' https://www.codingame.com/training/medium/don't-panic-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        Dim inputs as String()

        Dim nbFloors as Integer ' number of floors
        Dim width as Integer ' width of the area
        Dim nbRounds as Integer ' maximum number of rounds
        Dim exitFloor as Integer ' floor on which the exit is found
        Dim exitPos as Integer ' position of the exit on its floor
        Dim nbTotalClones as Integer ' number of generated clones
        Dim nbAdditionalElevators as Integer ' ignore (always zero)
        Dim nbElevators as Integer ' number of elevators
        inputs = Console.ReadLine().Split(" ")
        nbFloors = inputs(0)
        width = inputs(1)
        nbRounds = inputs(2)
        exitFloor = inputs(3)
        exitPos = inputs(4)
        nbTotalClones = inputs(5)
        nbAdditionalElevators = inputs(6)
        nbElevators = inputs(7)

        Dim elevatorFloor(nbElevators) as Integer ' floor on which this elevator is found
        Dim elevatorPos(nbElevators) as Integer' position of the elevator on its floor
        Dim b as integer =0

        For i as Integer = 0 To nbElevators-1
            inputs = Console.ReadLine().Split(" ")
            elevatorFloor(i) = inputs(0)
            elevatorPos(i) = inputs(1)

        Next

        ' game loop
        While True
            Dim cloneFloor as Integer ' floor of the leading clone
            Dim clonePos as Integer ' position of the leading clone on its floor
            Dim direction as String ' direction of the leading clone: LEFT or RIGHT
            inputs = Console.ReadLine().Split(" ")
            cloneFloor = inputs(0)
            clonePos = inputs(1)
            direction = inputs(2)
            b=0
            If cloneFloor = exitFloor then
              Console.Error.WriteLine(clonePos & " " & exitPos)
              if direction="LEFT" and clonePos-exitPos<0 then
                b=1
              end if 
              if direction="RIGHT" and clonePos-exitPos>0 then
                b=1
              end if 
            end if

            If cloneFloor < exitFloor then
              For i as Integer = 0 To nbElevators-1
                if cloneFloor=elevatorFloor(i)  then
                  Console.Error.WriteLine(clonePos & " " & elevatorPos(i))
                  if direction="LEFT" and clonePos-elevatorPos(i)<0 then
                    b=1
                  end if 
                  if direction="RIGHT" and clonePos-elevatorPos(i)>0 then
                    b=1
                  end if 
                end if
              next
            end if



            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")
            if b=1 then
              Console.WriteLine("BLOCK") ' action: WAIT or BLOCK
            else
              Console.WriteLine("WAIT") ' action: WAIT or BLOCK
            end if
        End While
    End Sub
End Module
