' https://www.codingame.com/training/easy/chuck-norris

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim MESSAGE as String
        MESSAGE = Console.ReadLine()

        Dim i as Integer
        Dim j as integer
        Dim jj as Integer
        Dim k as Integer
        Dim Crka as Char
        Dim a As Integer
        Dim s As String
        Dim Answer as String
        Answer = ""
        s=""
        ' loop over letters in messahge
        For i=0 to MESSAGE.Length-1
          ' convert i-th letter to binary      
          s=s+ Convert.ToString(Asc(MESSAGE.Substring(i,1)), 2).PadLeft(7, "0"c) '7 bits
        next
         
            ' loop over chrs in string representation of number
            j=0
            Do While j<s.Length
            
            Crka = s.Substring(j,1)
            If (Crka="1") Then
              Answer=Answer+"0 "
            Else
              Answer=Answer+"00 "
            End If
            ' count how many
            jj=0
            For k=j To s.Length-1
              If (s.Substring(k,1)=Crka) Then
                Answer=Answer+"0"
                jj=jj+1
              Else
                Exit For
              End If
            next
            Console.Error.WriteLine(Crka & " " & j & " " & jj)
            j=j+jj
            Answer=Answer+" "
            Loop
            
        
        Answer = Answer.Substring(0,Answer.Length-1)


        Console.WriteLine(Answer)
        
    End Sub
End Module
