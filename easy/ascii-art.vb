' https://www.codingame.com/training/easy/ascii-art

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim L as Integer
        L = Console.ReadLine()

        Dim H as Integer
        H = Console.ReadLine()

        Dim T as String
        T = Console.ReadLine()

        Dim Dolzina as Integer = T.Length
        dim aznak as integer
        dim znak as Char
        dim MojaCrka as String = ""



        For i as Integer = 0 To H-1
            Dim ROW as String
            ROW = Console.ReadLine()

            for j as Integer = 0 To Dolzina-1

              znak = T.SubString(j,1)
              aznak = Asc(znak)  ' A=65, a=97


              if (aznak>64 And aznak<97) then
                aznak=(aznak-65)*L
              else if (aznak>96 And aznak<129) then
                aznak=(aznak-97)*L
              else
                aznak=(asc("Z")+1-65)*L
              end if


              mojacrka=mojacrka+ROW.SubString(aznak,L)
            
            next
                        
            Console.WriteLine(mojacrka)
            mojacrka=""
       
        Next

    End Sub
End Module
