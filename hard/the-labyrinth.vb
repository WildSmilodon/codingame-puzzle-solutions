' https://www.codingame.com/training/hard/the-labyrinth

Module Player
' Auto-generateid code below aims at helping you parse
' the standard input according to the problem statement.


    
    Public Sub FindPath(ByVal tree(,) As Integer, ByVal myIndex As Integer, ByVal exitIndex As Integer, ByRef ninst As Integer, ByRef instList() As String)
 
    
              ' myIndex = start node     
              ' exitIndex = end node                   
    
              ' make a tree, try to find paths
              ' use breath first search
              'https://en.wikipedia.org/wiki/Breadth-first_search
          '    Console.Error.WriteLine("myIndex=" & myIndex & " exitI=" & exitIndex)


              Dim dist(20000) As Integer
              For i as Integer = 0 To 20000
                   dist(i)=100000
              Next              

              
              ' set up start of tree search
              Dim nToDoList As Integer = 1


              Dim ToDoList(20000) As Integer
              Dim CurDist As Integer = 0
              ToDoList(0)=exitIndex
              dist(ToDoList(0))=0
              
              Dim done As Integer = 0
              

              
              While nToDoList>0 and done=0
                 ' do the first in list
                 Dim node As Integer = ToDoList(0)
                 CurDist=CurDist+1
                 
                '  Console.Error.WriteLine("nToDoList=" & nToDoList & " node=" & node)  
                 
                 For i As Integer = 0 To 3  ' I have max 4 sons
                   Dim son As Integer = tree(node,i)
                   If son>0 Then
                     If CurDist < dist(son) then ' imam sina in moja pot tja je hitrejsa
                       ToDoList(nToDoList)=son
                       nToDoList=nToDoList+1
                       dist(son)=CurDist
                     End If
                   End if
                 Next
                 ' delete done node from the ToDoList
               '   Console.Error.WriteLine("nToDoList=" & nToDoList & " tdl=" & ToDoList(nToDoList-1))  
                 For i As Integer = 0 To nToDoList-2
                   ToDoList(i)=ToDoList(i+1)
                 Next
                 ' one less node to do
                 nToDoList=nToDoList-1
                 
              End While


             Ninst=0
             Console.Error.WriteLine("myIndex=" & myIndex  & " dist(myIndex)=" &  dist(myIndex) )
             If dist(myIndex)<100000 Then

             ' start from myIndex until you find the exit

             Dim CurIndex As Integer = myIndex
             Dim tmpIndex As Integer = -1
             While CurIndex <> ExitIndex 
               Dim MinD As Integer = 10000
               For i As Integer = 0 To 3  ' I have max 4 sons
                   Dim son As Integer = tree(CurIndex,i)
                   If son>0 Then
                  '    Console.Error.WriteLine("son=" & son & " " & dist(son) & " ci " & CurIndex & " i " & i)  
                     If dist(son)<MinD then 
                       MinD=dist(son)
                       tmpIndex=son
                       If i=0 Then
                         instList(Ninst)="RIGHT" 'tree (i,0)=son right, down,left up
                       else If i=1 Then
                         instList(Ninst)="DOWN" 'tree (i,0)=son right, down,left up
                       else If i=2 Then
                         instList(Ninst)="LEFT" 'tree (i,0)=son right, down,left up
                       else If i=3 Then
                         instList(Ninst)="UP" 'tree (i,0)=son right, down,left up
                       End If                       
                     End If
                   End if
               Next
               CurIndex=tmpIndex
               Ninst=Ninst+1
             '  Console.Error.WriteLine("nsinst=" & Ninst & " " & CurIndex)  
               End While 
             
             End If
    
    End Sub



    Public Sub FindVprasaj(ByVal tree(,) As Integer, ByRef myIndex As Integer, ByVal exitIndex As Integer)
 
    

              Dim dist(20000) As Integer
              For i as Integer = 0 To 20000
                   dist(i)=100000
              Next              

              
              ' set up start of tree search
              Dim nToDoList As Integer = 1


              Dim ToDoList(20000) As Integer
              Dim CurDist As Integer = 0
              ToDoList(0)=exitIndex  ' we start here
              dist(ToDoList(0))=0
              
              Dim done As Integer = 0
              Dim ikan As Integer = 0
              Dim kan(1000) As Integer
              

              
              While nToDoList>0 and done=0
                 ' do the first in list
                 Dim node As Integer = ToDoList(0)
                 CurDist=CurDist+1
                 
                
                   ' make a list of ? 
                   If tree(node,0)=-2 or tree(node,1)=-2 or tree(node,2)=-2 or tree(node,3)=-2 then
                     kan(ikan)=node
                     ikan=ikan+1
                   end if


                 For i As Integer = 0 To 3  ' I have max 4 sons
                   Dim son As Integer = tree(node,i)
                   If son>0 Then
                     If CurDist < dist(son) then ' imam sina in moja pot tja je hitrejsa
                       ToDoList(nToDoList)=son
                       nToDoList=nToDoList+1
                       dist(son)=CurDist
                     End If
                   End if
                 Next
                 ' delete done node from the ToDoList
               '   Console.Error.WriteLine("nToDoList=" & nToDoList & " tdl=" & ToDoList(nToDoList-1))  
                 For i As Integer = 0 To nToDoList-2
                   ToDoList(i)=ToDoList(i+1)
                 Next
                 ' one less node to do
                 nToDoList=nToDoList-1
                 
              End While
              
              
              Dim minD As Integer =10000
              For i As Integer = 0 To ikan-1
                Console.Error.WriteLine("ikan=" & i & " kan" & kan(i) & " dist " & dist(kan(i)))  
                If dist(kan(i))<minD then
                  minD=dist(kan(i))
                  myIndex=kan(i)
                End if
              Next
                  

    End Sub



    Sub Main ()
        Dim inputs as String()

        Dim R as Integer ' number of rows.
        Dim C as Integer ' number of columns.
        Dim A as Integer ' number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
        inputs = Console.ReadLine().Split(" ")
        R = inputs(0)
        C = inputs(1)
        A = inputs(2)

        Dim ROW as String
        Dim mapa(R-1,C-1) As String
        Dim TR As Integer =-1
        Dim TC As Integer =-1
        Dim CR As Integer =-1
        Dim CC As Integer =-1
        DIm dir as String
        Dim EscapeMode As Integer = 0
        Dim Ninst As Integer = 0
        Dim instList(1000) As String        
        
        Dim tree(20000,3) As Integer ' tree (i,0)=son right, down,left up
        Dim ctree(20000,3) As Integer ' tree (i,0)=son right, down,left up


         'init both trees (one with control room, one without)
            For i as Integer = 0 To R*C
                For j As Integer = 0 To 3
                   tree(i,j)=-1
                   ctree(i,j)=-1
                Next
            Next   
            
            TR=-1 ' don know yet where the target is
            TC=-1
            Dim exitIndex As Integer = -1
            Dim ccIndex As Integer = -1
            Dim tmpIndex As Integer = -1
        ' game loop
        While True
            Dim KR as Integer ' row where Kirk is located.
            Dim KC as Integer ' column where Kirk is located.
            inputs = Console.ReadLine().Split(" ")
            KR = inputs(0)
            KC = inputs(1)
            


            For i as Integer = 0 To R-1
                ROW = Console.ReadLine() ' C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
                Console.Error.WriteLine(ROW)
                For j As Integer = 0 To C-1
                   mapa(i,j)=ROW.Substring(j,1)
                   if mapa(i,j)="C" then 
                     CR=i
                     CC=j
                     ccIndex = CR*C+CC
                   else if mapa(i,j)="T" then
                     TR=i
                     TC=j
                     exitIndex = TR*C+TC
                   end if
                Next
            Next
            
            ' I dont know where I am going, so just explore
         Dim myIndex As Integer =KR*C+KC

Console.Error.WriteLine("EscapeMode=" & EscapeMode & " me=" & myIndex) 
 ' if in escape mode, I know where I am going
  If EscapeMode=0 Then
            
            
            ' start making tree at T point
            ' look around my location


            ' build entire tree
            For i as Integer = 1 To R-2
                For j As Integer = 1 To C-2
                  Dim tIndex As Integer =i*C+j

                 ' tree where control room is passable
                 if mapa(i,j+1)="." or mapa(i,j+1)="C" or mapa(i,j+1)="T" then
                    tree(tIndex,0)=i*C+j+1
                 else if mapa(i,j+1)="?" then
                   tree(tIndex,0)=-2
                 else 
                   tree(tIndex,0)=-1
                 end if
                  if mapa(i+1,j)="." or mapa(i+1,j)="C" or mapa(i+1,j)="T"  then
                    tree(tIndex,1)=(i+1)*C+j
                 else if mapa(i+1,j)="?" then
                   tree(tIndex,1)=-2
                 else 
                   tree(tIndex,1)=-1                   
                  end if
                  if mapa(i,j-1)="." or mapa(i,j-1)="C" or mapa(i,j-1)="T"  then
                    tree(tIndex,2)=i*C+j-1
                 else if mapa(i,j-1)="?" then
                   tree(tIndex,2)=-2                    
                 else 
                   tree(tIndex,2)=-1                   
                  end if
                  if mapa(i-1,j)="." or mapa(i-1,j)="C" or mapa(i-1,j)="T"  then
                    tree(tIndex,3)=(i-1)*C+j
                 else if mapa(i-1,j)="?" then
                   tree(tIndex,3)=-2                    
                 else 
                   tree(tIndex,3)=-1                   
                  end if            


                 ' tree where control room is NOT passable
                 if mapa(i,j+1)="."  or mapa(i,j+1)="T" then
                    ctree(tIndex,0)=i*C+j+1
                 else if mapa(i,j+1)="?" then
                    ctree(tIndex,0)=-2
                 else 
                    ctree(tIndex,0)=-1
                 end if
                  if mapa(i+1,j)="."  or mapa(i+1,j)="T"  then
                    ctree(tIndex,1)=(i+1)*C+j
                 else if mapa(i+1,j)="?" then
                    ctree(tIndex,1)=-2
                 else 
                    ctree(tIndex,1)=-1                   
                  end if
                  if mapa(i,j-1)="." or  mapa(i,j-1)="T"  then
                    ctree(tIndex,2)=i*C+j-1
                 else if mapa(i,j-1)="?" then
                    ctree(tIndex,2)=-2                    
                 else 
                    ctree(tIndex,2)=-1                   
                  end if
                  if mapa(i-1,j)="."  or mapa(i-1,j)="T"  then
                    ctree(tIndex,3)=(i-1)*C+j
                 else if mapa(i-1,j)="?" then
                    ctree(tIndex,3)=-2                    
                 else 
                    ctree(tIndex,3)=-1                   
                  end if            



                Next
            Next



            Console.Error.WriteLine("myIndex=" & myIndex)
            Console.Error.WriteLine("exitIndex=" & exitIndex)
            Console.Error.WriteLine("ccIndex=" & ccIndex)
          '  Console.Error.WriteLine(tree(myIndex,0)  & " " & tree(myIndex,1)  & " " & tree(myIndex,2)  & " " & tree(myIndex,3)  )

            ' I am in Control room, so plan my way out
            if KR=CR and KC=CC then

              Call FindPath(tree,myIndex,exitIndex,ninst,instList)
               EscapeMode=1              


            else if ccIndex>0 then ' I see the control room lets go there

 
             ' are we going to make it from control room to exit?
             Call FindPath(tree,ccIndex,exitIndex,ninst,instList)
            ' Console.Error.WriteLine("nist=" & ninst & " A=" & A)
             
             If ninst=0 or ninst>A Then ' Failed to find path to control room or is too far away
                Call FindVprasaj(ctree,tmpIndex,myIndex)
                Call FindPath(ctree,myIndex,tmpIndex,ninst,instList)
             Else ' try to find path to control room
                Call FindPath(tree,myIndex,ccIndex,ninst,instList)  
 
                If ninst=0 Then ' Failed to find path to control room
                  Call FindVprasaj(ctree,tmpIndex,myIndex)
                  Call FindPath(ctree,myIndex,tmpIndex,ninst,instList)
                End If
              End If
  
              EscapeMode=1     

            
            
            else  ' lets explore, find closest ?

              Call FindVprasaj(ctree,tmpIndex,myIndex)
              Call FindPath(ctree,myIndex,tmpIndex,ninst,instList)
              EscapeMode=1     

              'Console.Error.WriteLine("jaz=" & myIndex & " ? "  & tmpIndex )  
            end if
            
End If            
            
            If EscapeMode>0 Then

              'Console.Error.WriteLine("EscapeMode=" & EscapeMode & " "  & instList(EscapeMode) & " ninst=" & ninst)  
              dir=instList(EscapeMode-1)
              EscapeMode=EscapeMode+1
              If EscapeMode>ninst Then  ' turn off escape mode
                EscapeMode=0
              End If

            End if

  
            Console.WriteLine(dir) ' Kirk's next move (UP DOWN LEFT or RIGHT).
        End While
    End Sub
End Module
