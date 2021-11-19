' https://www.codingame.com/training/medium/scrabble

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim N as Integer
        Dim NN as Integer = 0
        N = Console.ReadLine()
        Dim besede(N-1) as String

        For i as Integer = 0 To N-1
            Dim W as String
            W = Console.ReadLine()
           ' Console.Error.WriteLine(W & " " & W.Length)
            If W.Length<8 then  ' skip long words
              besede(nn)=W
              nn=nn+1
            end if
        Next

        Dim LETTERS as String
        LETTERS = Console.ReadLine()
        Console.Error.WriteLine(n & " " & nn & "_" & LETTERS & "_xxx")

        Dim nlet as Integer = LETTERS.Length-1

        ' assign values to letters
        Dim crke(nlet) As String
        Dim vred(nlet) As Integer
          For i As Integer = 0 to nlet
            crke(i)=LETTERS.SubString(i,1)
            if crke(i)="q" or  crke(i)="z" then      
              vred(i)=10
            else if crke(i)="j" or  crke(i)="x" then      
              vred(i)=8
            else if crke(i)="k" then      
              vred(i)=5
            else if crke(i)="f" or  crke(i)="h" or crke(i)="v" or  crke(i)="w" or crke(i)="y" then      
              vred(i)=4
            else if crke(i)="b" or  crke(i)="c" or crke(i)="m" or  crke(i)="p" then      
              vred(i)=3              
            else if crke(i)="d" or  crke(i)="g" then      
              vred(i)=2
            else
              vred(i)=1
            end if
            Console.Error.WriteLine(i & " " & crke(i) & " " & vred(i))
          Next

        Dim por(nlet) As Integer
        Dim tocke as Integer
        Dim found as Integer
        Dim mword As String
        Dim mtocke As Integer = -1
        For i as Integer = 0 To nn-1
            For k as integer = 0 to nlet
              por(k)=0
            Next
            found=0
            tocke=0
            For j as Integer = 0 To besede(i).length-1
              For k as integer = 0 to nlet
                If besede(i).substring(j,1)=crke(k) and por(k)=0 then
                  por(k)=1
                  found=found+1
                  tocke=tocke+vred(k)
                  Exit For
                End if
              Next
            Next
            if found=besede(i).length and tocke>mtocke then
              mtocke=tocke
              mword=besede(i)
              Console.Error.WriteLine(besede(i) & "  " & tocke)
            end if
        Next


        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

        Console.WriteLine(mword)
    End Sub
End Module
