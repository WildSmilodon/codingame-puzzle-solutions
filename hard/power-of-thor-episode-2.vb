' https://www.codingame.com/training/hard/power-of-thor-episode-2

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.


    '***********************************************************************
    '***********************************************************************

  Public Sub FindPath(  ByVal Tree(,) As Integer, _                   
                        ByVal myIndex As Integer, _ 
                        ByVal exitIndex As Integer, 
                        ByRef ninst As Integer, _                          
                        ByRef instList() As Integer)
 
    
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
              
              
          '    Console.Error.WriteLine("start=" & myIndex & " end=" & exitIndex)  

              
              While nToDoList>0 
                 ' do the first in list
                 Dim node As Integer = ToDoList(0)
                 CurDist=dist(node)+1
                 
                '  Console.Error.WriteLine("nToDoList=" & nToDoList & " node=" & node & " curdi=" & CurDist)  
                ' Console.Error.WriteLine(" n son=" & Tree(node,0))
                 Dim nSons As Integer = Tree(node,0)
                 For i As Integer = 1 To nSons  ' I have several links
                   Dim son As Integer = Tree(node,i)

                     If CurDist < dist(son) then ' imam sina in moja pot tja je hitrejsa
                       ToDoList(nToDoList)=son
                       nToDoList=nToDoList+1
                       dist(son)=CurDist
                     End If
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
   

           if dist(myIndex)>1000 then ' path not found
              Ninst=-1
           else
             ' start from myIndex until you find the exit

             Dim CurIndex As Integer = myIndex
             Dim tmpIndex As Integer = -1
             While CurIndex <> ExitIndex 
               Dim MinD As Integer = 10000
               For i As Integer = 1 To Tree(CurIndex,0)  ' I have  sons
                   Dim son As Integer = Tree(CurIndex,i)
                  '    Console.Error.WriteLine("son=" & son & " " & dist(son) & " ci " & CurIndex & " i " & i)  
                     If dist(son)<MinD then 
                       MinD=dist(son)
                       tmpIndex=son
                       instList(Ninst)=son                    
                     End If
               Next
               CurIndex=tmpIndex
               Ninst=Ninst+1
               'Console.Error.WriteLine("nsinst=" & Ninst & " " & CurIndex)  
               End While 
             end if
    
    End Sub




    '***********************************************************************
    '***********************************************************************
    Public Sub GetRowCol (ByVal id As Integer, _
                          ByRef MeRow As Integer, _
                          ByRef MeCol As Integer, _
                          ByVal nCol As Integer )
    
             ' if no targets are accesible
              MeCol  = id mod ncol
              MeRow  =(id- MeCol)/ncol
    
    End Sub


'***********************************************************************
'***********************************************************************
     Public Function NodeID(ByVal iRow As Integer, ByVal iCol As Integer, ByVal nCol As Integer) As Integer
     
       Return iRow*nCol+iCol
     
     End Function

'***********************************************************************
'***********************************************************************
    Public Function AmIn(ByVal iRow As Integer, ByVal iCol As Integer, _
                         ByVal nRow As Integer, ByVal nCol As Integer) As Integer

    If iRow<0 or iRow>nRow-1 or iCol<0 or iCol>nCol-1 Then
      Return 1
    Else
      Return 0
    End If


    End Function

'***********************************************************************
'***********************************************************************
    Public Sub GotoDir (ByVal fR As Integer, _
                        ByVal fC As Integer, _
                        ByVal tR As Integer, _
                        ByVal tC As Integer, _
                        ByRef dir As String)

    
        ' N
        If fR>tR and fC=tC Then
          dir="N"
        Else  If fR>tR and fC<tC Then
            dir="NE"
        Else  If fR=tR and fC<tC Then
            dir="E" 
        Else  If fR<tR and fC<tC Then
            dir="SE" 
        Else  If fR<tR and fC=tC Then
            dir="S"
        Else  If fR<tR and fC>tC Then
            dir="SW" 
        Else  If fR=tR and fC>tC Then
            dir="W"   
        Else  If fR>tR and fC>tC Then
            dir="NW" 
        Else
          dir="WAIT"
        End If

    End Sub



'***********************************************************************
'***********************************************************************
    Public Sub MakeTree(ByRef Tree(,) As Integer, _
                        ByVal nRow As Integer, _
                        ByVal nCol As Integer)
    
    ' set number of links per node to 0
    For i As Integer = 0 To nRow*nCol
      Tree(i,0)=0 ' number of links for this node 
    Next
    
    
    For i As Integer = 0 To nRow-1
      For j As Integer = 0 To nCol-1
        Dim node As Integer = NodeID(i,j,nCol)
        
        ' N
        If AmIn(i-1,j,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i-1,j,nCol)
        End If


        ' S
        If AmIn(i+1,j,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i+1,j,nCol)
        End If



        ' W
        If AmIn(i,j-1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i,j-1,nCol)
        End If

        ' NE
        If AmIn(i-1,j+1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i-1,j+1,nCol)
        End If

        ' SE
        If AmIn(i+1,j+1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i+1,j+1,nCol)
        End If

        ' E
        If AmIn(i,j+1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i,j+1,nCol)
        End If


        ' SW
        If AmIn(i+1,j-1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i+1,j-1,nCol)
        End If



        ' NW
        If AmIn(i-1,j-1,nRow,nCol)=0 Then
          Tree(node,0)=Tree(node,0)+1
          Tree(node,Tree(node,0))=nodeID(i-1,j-1,nCol)
        End If
        
      
      Next
    Next
    
    End Sub


'***********************************************************************
'***********************************************************************

    Sub Main ()
        Dim inputs as String()

        ' build a tree, map size is 40x18
        Dim nRow As Integer = 18
        Dim nCol As Integer = 40
        
        Dim ninst As Integer
        Dim instList(100) As Integer
        
        Dim map(nRow-1,nCol-1) As Integer
        Dim Tree(nRow*nCol,8) As Integer
       
        CAll MakeTree(tree,nRow,nCol)
       
        Dim TX as Integer
        Dim TY as Integer
        inputs = Console.ReadLine().Split(" ")
        TX = inputs(0)
        TY = inputs(1)

        ' game loop
        While True
            Dim H as Integer ' the remaining number of hammer strikes.
            Dim N as Integer ' the number of giants which are still present on the map.
            inputs = Console.ReadLine().Split(" ")
            H = inputs(0)
            N = inputs(1)

            Dim X(N-1) as Integer
            Dim Y(N-1) as Integer
            For i as Integer = 0 To N-1

                inputs = Console.ReadLine().Split(" ")
                X(i) = inputs(0)
                Y(i) = inputs(1)
               ' Console.Error.WriteLine(X(i) & " " & Y(i))
            Next


            Dim myID As Integer = NodeID(Ty,Tx,nCol)

            ' only one monster left
            IF N=1 Then

                
                Dim moID As Integer = NodeID(Y(0),X(0),nCOl)
                Call FindPath(Tree,myId,moId,ninst,instList)               

                Console.Error.WriteLine(myID & " " & moID & " " & ninst)

                IF ninst=2 Then
                  Console.WriteLine("STRIKE")
                Else
                  Console.WriteLine("WAIT")
                End if
             Else
             ' more then one monster
                ' find centroid
                 Dim cenR As Integer = 0
                 Dim cenC As Integer = 0
                 For j As Integer = 0 To N-1
                   cenR=cenR+Y(j)
                   cenC=cenC+X(j)
                 Next
                 cenR=cenR/N
                 cenC=cenC/N
                 Dim cenID As Integer = NodeID(cenR,cenC,nCol)
                 Call FindPath(Tree,myID,cenID,ninst,instList)
                 
              '    For i As Integer = 0 To ninst-1
              '    Console.Error.WriteLine(instList(i))
              '   Next
                 
                 Dim nSons As Integer = Tree(myID,0)
                 Dim ceni As Integer = -1
                 For i As Integer = 1 To nSons
                   If instList(0)= Tree(myID,i) Then
                     ceni=i
                   End If
                 Next
                 Console.Error.WriteLine(cenR & " cen " & cenC & " ceni " & ceni & " myid " & myId & " cenid " & cenid  )
                
                 
                 DIm minD As Integer = 10000000
                 Dim minI As Integer = -1
                 dim fire As Integer = 0
                 Dim dif(8) As Integer
                 Dim minDist(8) As Integer
                 For i As Integer = 1 To nSons  ' I have several links
                   Dim son As Integer = Tree(myID,i)    
                   Dim vs As Integer = 0
                   Dim vs2 As Integer = 0
                   minDist(i)=10000
                   For j As Integer = 0 To N-1
                     Dim moDis As Integer = (Y(j)-ty)^2+(X(j)-tx)^2
                     IF moDis<25 or N<50 Then
                        Dim moID As Integer = NodeID(Y(j),X(j),nCOl)
                        Call FindPath(Tree,son,moId,ninst,instList)
                        vs=vs+ninst
                        vs2=vs2+ninst^2
                   '      Console.Error.WriteLine(vs & " " & vs2 )
                        If ninst<minDist(i) Then
                            minDist(i)=ninst
                        End if
                      End If
                   Next
                   dif(i)=N*vs2-vs^2
                   
                   If dif(i) < minD and minDist(i)>1 Then  ' to poptavi
                     minD=dif(i)
                     minI=i
                   End If
                   Console.Error.WriteLine(i & " dif " & dif(i) & " mdist " & minDist(i) & " mini " & mini)
                 Next
                 

                 ' try to go towards centroid
                 If ceni>-1 then
                   If minDist(ceni)>1 Then
                    minI=ceni
                   End If
                 End If

                 If minI=-1 then ' optimal path is safe go
                   fire=1
                 End if
                 
                 
                 If fire=1 Then
                   Console.WriteLine("STRIKE")
                 Else
                    Dim tRow As Integer
                    Dim tCol As Integer
                    Call GetRowCol (Tree(myID,minI),tRow,tCol,nCol)
                    Dim dir As String
                    Call GoToDir(ty,tx,tRow,tCol,dir)
                
                    Console.Error.WriteLine(ty & " " & tx & " " & tRow & " " & tCol & " " & dir)
                 
                    ' update Thors position
                    ty=tRow
                    tx=tCol
                 
                   Console.WriteLine(dir)
                 End if
             End if
            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")


            ' The movement or action to be carried out: WAIT STRIKE N NE E SE S SW W or N
            
        End While
    End Sub
End Module
