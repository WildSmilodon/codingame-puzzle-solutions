' https://www.codingame.com/training/medium/conway-sequence

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim R as Integer
        R = Console.ReadLine()

        Dim L as Integer
        L = Console.ReadLine()

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

        Dim o(200*L) As Integer
        Dim n(200*L) As integer
        
        Dim no As Integer
        Dim nn As Integer
        Dim vold As Integer
        Dim c As Integer = 0
        
        no=1
        o(0)=R
        nn=1
        n(0)=R
      
        
        for k as integer = 0 to L-2
        c=0
        ' make new list
        nn=0
        vold=o(0)
        For i as Integer = 0 to no-1
          ' count same values
          if o(i)=vold then
            c=c+1
          else
            n(nn)=c
            nn=nn+1
            n(nn)=o(i-1)
            nn=nn+1

            c=1            
            vold=o(i)
          end if
        next
        ' last one
        n(nn)=c
        nn=nn+1
        n(nn)=o(no-1)
        nn=nn+1
        ' make new line old
        no=nn
        for i as integer  = 0 to nn-1
          o(i)=n(i)      
        next

   '     Dim s As String = n(0).ToString
    '    for i as integer  = 1 to nn-1
     '     s=s+" "+n(i).ToString          
      '  next
      '   Console.Error.WriteLine(s)
        next

        
        
        Dim s As String = n(0).ToString
        for i as integer  = 1 to nn-1
          s=s+" "+n(i).ToString          
        next


        Console.WriteLine(s)
    End Sub
End Module
