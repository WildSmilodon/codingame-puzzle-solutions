' https://www.codingame.com/training/medium/there-is-no-spoon-episode-1

Module Player
' Don't let the machines win. You are humanity's last hope...

    Sub Main ()
        
        Dim width as Integer
        width = Console.ReadLine() ' the number of cells on the X axis

        Dim height as Integer
        height = Console.ReadLine() ' the number of cells on the Y axis

        Dim grid(height,width) as integer
        

        For i as Integer = 0 To height-1
            Dim line as String
            line = Console.ReadLine() ' width characters, each either 0 or .

            for j as integer =0 to line.Length-1

              if line.substring(j,1)="0" then
                grid(i,j)=0
              else
                grid(i,j)=1
              end if
              
             next
        Next
        
        dim jdol as integer
        dim idol as integer
        dim ides as integer
        dim jdes as integer        
        
        
         For i as Integer = 0 To height-1
          For j as Integer = 0 To width-1
            
            if grid(i,j)=0 then
              
              'down
              idol=-1
              jdol=-1
              for ii as integer =i+1 to height-1
                if grid(ii,j)=0 then
                  jdol=j
                  idol=ii
                  Exit For
                end if
              next
       
              ' right
              ides=-1
              jdes=-1       
             for jj as integer =j+1 to width-1
                if grid(i,jj)=0 then
                  jdes=jj
                  ides=i
                  Exit For
                end if
              next 
          ' Three coordinates: a node, its right neighbor, its bottom neighbor
            Console.WriteLine( j & " " & i & " " & jdes & " " & ides & " " &jdol & " " & idol)
            
            end if            
            
            
            
           next
         next
         

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")


   

    End Sub
End Module
