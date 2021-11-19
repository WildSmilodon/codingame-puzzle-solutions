' https://www.codingame.com/training/medium/shadows-of-the-knight-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        Dim inputs as String()

        Dim W as Integer ' width of the building.
        Dim H as Integer ' height of the building.
        inputs = Console.ReadLine().Split(" ")
        W = inputs(0)
        H = inputs(1)

        Dim N as Integer
        N = Console.ReadLine() ' maximum number of turns before game over.

        Dim X0 as Integer
        Dim Y0 as Integer
        inputs = Console.ReadLine().Split(" ")
        X0 = inputs(0)
        Y0 = inputs(1)

        Dim X1 as integer
        Dim Y1 as integer
        Dim Xm1 as integer = W
        Dim Ym1 as integer = H
        Dim dx as integer
        Dim dy as integer
        dim st as integer = 0
        dim preskok as integer =0
        ' game loop
        While True
            Dim bombDir as String
            Dim fbd as String
            bombDir = Console.ReadLine() ' the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)

            st=st+1
            if (st=1) then
              fbd=bombDir
              if bombDir="UR" or bombDir="U" or bombDir="R"  then
                 Xm1=W
                 Ym1=0
              end if        
              if bombDir="DR" or bombDir="D" or bombDir="R"  then
                 Xm1=W
                 Ym1=H
              end if        
              if bombDir="UL" or bombDir="U" or bombDir="L"  then
                 Xm1=0
                 Ym1=0
              end if        
              if bombDir="DL" or bombDir="D" or bombDir="L"  then
                 Xm1=0
                 Ym1=H
              end if                    
            end if

            if (fbd<>bombDir) then
              preskok=1
            end if

            dy=Math.Abs(Ym1-Y0)\2
            dx=Math.Abs(Xm1-X0)\2

            dy=0.4+Math.Abs(Ym1-Y0)/2
            dx=0.4+Math.Abs(Xm1-X0)/2



            if Math.Abs(Ym1-Y0)=1 then
              dy=1
            end if
            if Math.Abs(Xm1-X0)=1 then
              dx=1
            end if


            if (bombDir)="UR" then
              X1=X0+dx
              Y1=Y0-dy
            end if

            if (bombDir)="UL" then
              X1=X0-dx
              Y1=Y0-dy
            end if

            if (bombDir)="DR" then
              X1=X0+dx
              Y1=Y0+dy
            end if

            if (bombDir)="DL" then
              X1=X0-dx
              Y1=Y0+dy
            end if


            if (bombDir)="R" then
              if dx=0 then
                dx=1
              end if
              X1=X0+dx
            end if

            if (bombDir)="L" then
                          if dx=0 then
                dx=1
              end if
              X1=X0-dx
            end if

            if (bombDir)="D" then
            if dy=0 then
                dy=1
              end if
              Y1=Y0+dy
            end if

            if (bombDir)="U" then
             if dy=0 then
                dy=1
              end if
              Y1=Y0-dy
            end if

            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")


            ' the location of the next window Batman should jump to.
            Console.WriteLine(X1 & " " & Y1)

            If st>1 and preskok=1 then
              Xm1=X0
              Ym1=Y0            
            end if
            X0=X1
            Y0=Y1

            
        End While
    End Sub
End Module
