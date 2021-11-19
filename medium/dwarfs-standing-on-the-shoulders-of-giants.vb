' https://www.codingame.com/training/medium/dwarfs-standing-on-the-shoulders-of-giants

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.
   ' Recursive search through the tree
   Sub Travel(ByVal jaz As Integer, ByVal tree() As Integer, ByVal sons(,) As Integer, ByVal ns() As Integer, ByVal CurDepth As Integer, ByRef MaxDepth As Integer)

       ' Travel to my sons
           For j as Integer = 0 To ns(jaz)-1
               Call Travel(sons(jaz,j),tree,sons,ns,CurDepth+1,MaxDepth)
           Next

       if  CurDepth>MaxDepth then ' remember max tree depth
         MaxDepth= CurDepth
       end if
    
    End Sub


    Sub Main ()
        
        Dim n as Integer
        n = Console.ReadLine() ' the number of relationships of influence
        Dim x(n-1) as Integer ' a relationship of influence between two people (x influences y)
        Dim y(n-1) as Integer

        Dim tree(20000) As Integer
        Dim ntree As Integer = 0
        Dim sons(20000,100) As Integer
        Dim ns(20000) As Integer

        For i as Integer = 0 To n-1
            Dim inputs as String()

            inputs = Console.ReadLine().Split(" ")
            x(i) = inputs(0)
            y(i) = inputs(1)
            
            ' check if already in tree
            Dim FoundX As Integer = -1
            Dim FoundY As Integer = -1
      
            For j As Integer =0 to ntree-1
              If x(i)=tree(j) then
                FoundX=j
              End if
              If y(i)=tree(j) then
                FoundY=j
              End if
            Next
            
            IF FoundX=-1 then
              tree(ntree)=x(i)
              FoundX=ntree
              ntree=ntree+1
              ns(FoundX)=0
            End if

            IF FoundY=-1 then
              tree(ntree)=y(i)
              FoundY=ntree
              ntree=ntree+1
              ns(FoundY)=0
            End if     
            
            sons(FoundX,ns(FoundX))=FoundY
            ns(FoundX)=ns(FoundX)+1
            
        Next

        ' display tree
        ' For i as Integer = 0 To ntree-1
           '  Console.Error.WriteLine(i & "tree " &   tree(i) & " ns " & ns(i))
         '     For j as Integer = 0 To ns(i)-1
             '   Console.Error.WriteLine(sons(i,j))
        '   Next
        ' Next   

        
        Dim MaxDepth as Integer = 0
        ' let us travel trough the tree
         For i as Integer = 0 To ntree-1
             Call Travel(i,tree,sons,ns,1,MaxDepth)
         Next  
        


        ' The number of people involved in the longest succession of influences
        Console.WriteLine(MaxDepth)
    End Sub
End Module
