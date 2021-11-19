' https://www.codingame.com/training/medium/mayan-calculation

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim inputs as String()
        Dim L as Integer
        Dim H as Integer
        inputs = Console.ReadLine().Split(" ")
        L = inputs(0)
        H = inputs(1)

        Dim stevilke(20,H-1) As String

        For i as Integer = 0 To H-1
            Dim numeral as String
            numeral = Console.ReadLine()

            For j As Integer = 0 to 19
              stevilke(j,i)=numeral.SubString(j*L,L)
            Next
        Next
        
        ' display mayan numbers
  '      For j As Integer = 0 to 19
  '        Console.Error.WriteLine(j)
  '        For i As Integer = 0 to H-1
  '          Console.Error.WriteLine(stevilke(j,i))
  '        Next
  '      Next
        

        Dim S1 as Integer
        S1 = Console.ReadLine()
         

        Dim n1cif As Integer = S1 / H
        Dim n1(n1cif-1) As Integer
        
        Console.Error.WriteLine(S1 & " " & n1cif & " " & L & " " & H )
        Dim ll As Integer
        
        Dim num1Line(H-1) as String        
        For i as Integer = 0 To n1cif-1
            For j As Integer = 0 To H-1
              num1Line(j) = Console.ReadLine()
            Next
            ' find cifro
            For k As Integer = 0 To 19
              ll = 0
              For j As Integer = 0 To H-1
                If num1Line(j)=stevilke(k,j) then
                  ll=ll+1
                End if
              Next
              IF ll=H Then
                Console.Error.WriteLine("k1=" & k)
                n1(i)=k
                Exit For
              End if
            Next

        Next


        Dim S2 as Integer
        S2 = Console.ReadLine()
         

        Dim n2cif As Integer = S2 / H
        Dim n2(n2cif-1) As Integer
                
        Dim num2Line(H-1) as String        
        For i as Integer = 0 To n2cif-1
            For j As Integer = 0 To H-1
              num2Line(j) = Console.ReadLine()
            Next
            ' find cifro
            For k As Integer = 0 To 19
              ll = 0
              For j As Integer = 0 To H-1
                If num2Line(j)=stevilke(k,j) then
                  ll=ll+1
                End if
              Next
              IF ll=H Then
                Console.Error.WriteLine("k2=" & k)
                n2(i)=k
                Exit For
              End if
            Next

        Next

    Console.Error.WriteLine("n1cif= " & n1cif & " n2cif=" & n2cif)
    ' izpisi cifre
    Dim n1des As long = 0
    For i as Integer = 0 To n1cif-1
      Console.Error.WriteLine(i & " "  & n1(i))
      n1des=n1des+n1(i)*20^(n1cif-1-i)
    Next
    Dim n2des As long = 0
    For i as Integer = 0 To n2cif-1
      Console.Error.WriteLine(i & " " & n2(i))
      n2des=n2des+n2(i)*20^(n2cif-1-i)
    Next



        Dim operation as String
        operation = Console.ReadLine()

        Dim ResDes As Long = 0
        
        Console.Error.WriteLine("Des= " & n1des & operation & n2des )
        
        If operation="+" then
          ResDes=n1des+n2des
        else if  operation="-" then
          ResDes=(n1des-n2des)
        else if  operation="*" then
          ResDes=n1des*n2des
        else if  operation="/" then
          ResDes=n1des/n2des
        end if

     Console.Error.WriteLine("Des= " & n1des & operation & n2des & "=" & ResDes)

        'back to 20-ish
        Dim Div As long = 1
        Dim Rema(10) As long
        Dim nRema As Integer = 0
        while Div>0
          Div=ResDes\20
             Console.Error.WriteLine("div=" & div & "resDes=" & ResDes & " " & ResDes\20 )
          Rema(nrema)=ResDes-Div*20
           Console.Error.WriteLine("Rema=" & rema(nrema))
          nrema=nrema+1
          ResDes=Div
        End While
        
        Console.Error.WriteLine("nrema=" & nrema)
        for i as integer = 0 to nrema-1
          Console.Error.WriteLine(Rema(nrema-1-i))
          For j As Integer = 0 To H-1         
                Console.WriteLine(stevilke(Rema(nrema-1-i),j))
          next
        next
          
        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

      '  Console.WriteLine("result")
    End Sub
End Module
