' https://www.codingame.com/training/easy/mime-type

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim N as Integer
        N = Console.ReadLine() ' Number of elements which make up the association table.

        Dim Q as Integer
        Q = Console.ReadLine() ' Number Q of file names to be analyzed.

        Dim jEXT(N) as String
        Dim jMT(N) as String

        For i as Integer = 0 To N-1
            Dim inputs as String()
            Dim EXT as String ' file extension
            Dim MT as String ' MIME type.
            inputs = Console.ReadLine().Split(" ")
            EXT = inputs(0)
            MT = inputs(1)
            jEXT(i)=LCASE(EXT)
            jMT(i)=MT
            

        Next

       Console.Error.WriteLine(N & " " & Q)

        Dim j as integer
        Dim kon as String
        For i as Integer = 0 To Q-1
            Dim FNAME as String
            FNAME = Console.ReadLine() ' One file name per line.
           
            j = FNAME.LastIndexOf(".")
            If (j=-1) THEN
              kon=""
            ELSE
              kon = LCASE(FNAME.SubString(j+1,FNAME.Length-j-1))
            END IF
     
           Dim a as Integer =0 
            For k as Integer = 0 To N-1
              IF kon=jEXT(k) THEN
                Console.WriteLine(jMT(k))
                a=1
                EXIT FOR
             END IF
           NEXT
           IF a=0 THEN
             Console.WriteLine("UNKNOWN")
           END IF
    
        Next


    End Sub
End Module
