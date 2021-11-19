' https://www.codingame.com/training/medium/the-gift

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim N as Integer
        N = Console.ReadLine()
        Console.Error.WriteLine("N=" & N)

        Dim C as Integer
        C = Console.ReadLine()
        Console.Error.WriteLine("C=" & C)

        Dim B(N-1) as Integer
        Dim P(N-1) as Integer
        Dim vsota As Integer = 0
        For i as Integer = 0 To N-1
            B(i) = Console.ReadLine()
           ' Console.Error.WriteLine(i & " " & B(i))
            vsota=vsota+B(i)
            P(i)=0
        Next
        
        Array.Sort(B)
        
        Console.Error.WriteLine("vsota=" & vsota)
        If Vsota<C then
          Console.WriteLine("IMPOSSIBLE")
        Else
        
          Dim nost As Integer = N
          Dim ave As Integer = C/nost
          Dim np As Integer = 0 
          Dim ostanek As Integer
          vsota=C
         
         
            For i as Integer = 0 To N-1
              ave=vsota/nost
              If B(i)<ave Then
                P(i)=B(i)
              Else
                P(i)=ave
              End if
              vsota=vsota-P(i)
              nost=nost-1
              ' Console.Error.WriteLine(ave & "  " & vsota & " " & nost & " " & P(i))
            Next

            Array.Sort(P)
           
            For i as Integer = 0 To N-1          
                 Console.WriteLine(P(i))
            Next
            
          
          
        
'

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")


         End if
        
    End Sub
End Module
