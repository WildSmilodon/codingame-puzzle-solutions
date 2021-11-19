' https://www.codingame.com/training/medium/stock-exchange-losses

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim n as Integer
        n = Console.ReadLine()

        Dim inputs as String()
        Dim v(n) as Integer
        inputs = Console.ReadLine().Split(" ")
        For i as Integer = 0 To n-1
            v(i) = inputs(i)
        Next
   
        Console.Error.WriteLine("n=" & n)
   
        Dim mloss as integer = 0
        Dim mj as integer = 0
        Dim mi as integer = 0

        For i as Integer = 0 To n-1
          If v(i)>=v(mi) or i>mj Then
            For j as integer =i+1 To n-1
              if v(j)-v(i) < mloss then
                mloss =  v(j)-v(i)
                mj=j
                mi=i
              end if
            next
         end if
          ' Console.Error.WriteLine(v(i) & " " & mloss)
        next

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

        Console.WriteLine(mloss)
    End Sub
End Module
