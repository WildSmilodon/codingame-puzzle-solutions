' https://www.codingame.com/training/medium/network-cabling


Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim N as Integer
        N = Console.ReadLine()

            Dim X(N-1) as Integer
            Dim Y(N-1) as Integer

        For i as Integer = 0 To N-1
            Dim inputs as String()
            inputs = Console.ReadLine().Split(" ")
            X(i) = inputs(0)
            Y(i) = inputs(1)
        Next
        
        Dim minX as Integer = 100000
        Dim maxX as Integer =-100000
        DIm sumY as Integer = 0
        
        For i as Integer = 0 To N-1
          if x(i)>maxX then
            maxX=x(i)
          end if
          if x(i)<minX then
            minX=x(i)
          end if
         ' Console.Error.WriteLine(y(i))
        next
         

        Array.sort(Y)
                
        
        Dim k as Integer = n \ 2

       ' Console.Error.WriteLine("minX= " & minX & ", maxX= " & maxX & ", n= " & n & ", k= " & k & ", y(k)= " & y(k))

        Dim Dist As Long = maxX - minX
        
         For i as Integer = 0 To N-1
           Dist=Dist + Math.abs(Y(i)-Y(k))
        '   Console.Error.WriteLine(dist & "  " & Y(i))
         Next

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

        Console.WriteLine(dist)
    End Sub
End Module
