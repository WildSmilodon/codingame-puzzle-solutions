' https://www.codingame.com/training/medium/bender-episode-1

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim inputs as String()
        Dim L as Integer
        Dim C as Integer
        inputs = Console.ReadLine().Split(" ")
        L = inputs(0)
        C = inputs(1)

        Dim map(L,C) As String

        ' read the map
        For i as Integer = 0 To L-1
            Dim row as String
            row = Console.ReadLine()
            Console.Error.WriteLine(row)
 
            For j as Integer = 0 To C-1
              map(i,j)=row.substring(j,1)
            Next
        Next
        
        Dim row as Integer
        Dim col as Integer
        Dim nt as Integer = 0
        Dim trow(1) as Integer
        Dim tcol(1) as Integer
        
        Dim ListR(1000) As Integer
        Dim ListC(1000) As Integer
        Dim ListDir(1000) As String
        Dim ListN As Integer = 0
        

        ' find starting position
        For i as Integer = 0 To L-1 
            For j as Integer = 0 To C-1
            ' Console.Error.WriteLine(i & "  " & j & " " & map(i,j))
              if map(i,j)="@" then
                row=i
                col=j
             else if map(i,j)="T" then
                trow(nt)=i
                tcol(nt)=j
                nt=nt+1
              end if
            Next
        Next        
        
        Dim dir As String = "SOUTH"
        
       
        
        Dim nrow As Integer = row
        Dim ncol As Integer = col
        Dim found As Integer = 0
        Dim iend As Integer = 0
        Dim iPri As Integer = 0
        Dim iBr As Integer = 0
        Dim iTry As Integer = 0
        Dim odir as string
        Dim tt As Integer = 0
        Dim iLoop As Integer = 0
        Dim lstart As Integer = 0
        Dim iMoves As Integer = 0


     while iend = 0 and iMoves < 990 'and iLoop=0
        ' search for next position 
        iMoves=iMoves+1
        
        while found = 0
        
        
        
        nrow=row
        ncol=col
        ' determine next position
        If dir="SOUTH" then
          nrow=row+1
        else if dir="NORTH" then
          nrow=row-1
        else if dir="EAST" then
          ncol=col+1
        else if dir="WEST" then
          ncol=col-1
        end if
        
       ' Console.Error.WriteLine(nrow & "  " & ncol & " " &  map(nrow,ncol) &  " jure " & dir)
        
        if map(nrow,ncol)="#" or ( map(nrow,ncol)="X" and iBr = 0 ) then
          ' blocked, so choose next direction
          if iTry=0 then
            odir=dir
          end if
          
          iTry=iTry+1
          
          if iPri=0 then
            
            if odir="SOUTH" then
              if iTry=1 then
                dir="EAST"
              else if iTry=2 then
                dir="NORTH"
              else if iTry=3 then
                dir="WEST"
              end if
            else if odir="EAST" then
              if iTry=1 then
                dir="SOUTH"
              else if iTry=2 then
                dir="NORTH"
              else if iTry=3 then
                dir="WEST"
              end if
            else if odir="NORTH" then
              if iTry=1 then
                dir="SOUTH"
              else if iTry=2 then
                dir="EAST"
              else if iTry=3 then
                dir="WEST"
              end if
            else if odir="WEST" then
              if iTry=1 then
                dir="SOUTH"
              else if iTry=2 then
                dir="EAST"
              else if iTry=3 then
                dir="NORTH"
              end if
            end if
             
          
          else if iPri=1 then

            if odir="SOUTH" then
              if iTry=1 then
                dir="WEST"
              else if iTry=2 then
                dir="NORTH"
              else if iTry=3 then
                dir="EAST"
              end if
            else if odir="EAST" then
              if iTry=1 then
                dir="WEST"
              else if iTry=2 then
                dir="NORTH"
              else if iTry=3 then
                dir="SOUTH"
              end if
            else if odir="NORTH" then
              if iTry=1 then
                dir="WEST"
              else if iTry=2 then
                dir="EAST"
              else if iTry=3 then
                dir="SOUTH"
              end if
            else if odir="WEST" then
              if iTry=1 then
                dir="NORTH"
              else if iTry=2 then
                dir="EAST"
              else if iTry=3 then
                dir="SOUTH"
              end if
            end if


          end if
          
          found=0
         
        else if map(nrow,ncol)="X" and iBr = 1  then
          map(nrow,ncol)=" "
          row=nrow
          col=ncol
          lStart=ListN+2
          found=1
         
        ' its free to go forward
        else if map(nrow,ncol)=" " or map(nrow,ncol)="@" then
          row=nrow
          col=ncol
          found=1

        else if map(nrow,ncol)="N" then
          row=nrow
          col=ncol
         ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1
          dir="NORTH"
          found=0
        else if map(nrow,ncol)="S" then
          row=nrow
          col=ncol
         ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1        
          dir="SOUTH"
          found=0
        else if map(nrow,ncol)="E" then
          row=nrow
          col=ncol
         ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1          
          dir="EAST"
          found=0
        else if map(nrow,ncol)="W" then
          row=nrow
          col=ncol
         ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1          
            dir="WEST"
          found=0
        else if map(nrow,ncol)="B" then
          row=nrow
          col=ncol
          found=1
          if iBr=0 then
            iBr=1
          else
            iBr=0
          end if
          
        else if map(nrow,ncol)="T" then
          if nrow=trow(0) and ncol=tcol(0) then
            row=trow(1)
            col=tcol(1)
          else
            row=trow(0)
            col=tcol(0)
          end if
                   ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1
          found=0  
          
        ' priorities inverte
        else if map(nrow,ncol)="I" then
          row=nrow
          col=ncol
          found=1
          if iPri=0 then
            iPri=1
          else
            iPri=0
          end if

        ' its free to go forward
        else if map(nrow,ncol)="$" then
          row=nrow
          col=ncol
          found=1
          iend=1
        end if

        end while
        
         
         Console.Error.WriteLine(row & "  " & col & " - " &  map(row,col) & "  " & dir  & " " & found ) 
         found = 0
         
         
         ListR(ListN)=row
         ListC(ListN)=col
         ListDir(ListN)=dir
         ListN=ListN+1

         for l as integer =lStart to ListN-2
           If ListR(l)=row and ListC(l)=col and ListDir(l)=dir then
             iLoop=1
              Console.Error.WriteLine(row & "  " & col & " - " &  map(row,col) & "  " & dir  & " loop " & l ) 
           end if
         next
         
         iTry=0
       

      end while
        
       Console.Error.WriteLine(lstart & " lstart " & ListN & " iend " & iend & " iloop " & iloop)
      If iend=1 then 
        for i as Integer = 0 To ListN-1
          Console.WriteLine(Listdir(i))
        next
      else 
        If iLoop=0 then
          for i as Integer = 0 To ListN-1
            Console.WriteLine(Listdir(i))
          next
        else
          Console.WriteLine("LOOP")
        end if
       end if
    End Sub
End Module
