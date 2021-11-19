' https://www.codingame.com/multiplayer/optimization/codingame-sponsored-contest

Module Player

' Pacman
' score is number of visited tiles * 2

' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

Public Function GetDanger(ByVal target As Integer , _
                          ByVal targetNode() aS Integer, _
                          ByVal targetCost() aS Integer ) As Integer
                    
For i As Integer = 0 To 3
  If targetNode(i)=target Then
    return targetCost(i)
  End if
Next

End Function


Public Sub CalculateNodeCostAroundMe _
                         (ByVal map(,) aS Integer, _
                          ByRef targetNode() aS Integer, _
                          ByRef targetCost() aS Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal monRow() As Integer , _                         
                          ByVal MonCol() As Integer, _
                          ByVal nMonsters As Integer)

Dim Tree(10000,4) As Integer ' nodes in tree
Dim TreeNumber(10000) As Integer ' number of links for this node
Dim myNode As Integer = nodeID(MeRow,MeCol,nCol)
Dim ninst As Integer
Dim instList(1000) As Integer

' where are nodes around me
Dim iRow(3) As Integer
Dim iCol(3) As Integer
Dim levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC As Integer 

Call GetNeighbours(MeRow,MeCol,nRow,nCol,levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC)
iRow(0)=levoR
iCol(0)=levoC
iRow(1)=dolR
iCol(1)=dolC
iRow(2)=desnoR
iCol(2)=desnoC
iRow(3)=gorR
iCol(3)=gorC


Call CreateTree(map,nrow,ncol,MeRow,MeCol,Tree,TreeNumber)

'Dim targetNode(3) As Integer 
Dim targetCost(3) As Integer

For i As Integer = 0 To 3
  IF map(iRow(i),iCol(i)) = 0 Then ' free node
       targetNode(i) =  NodeID(iRow(i),iCol(i),nCol) 
    
       ' how far away are monsters
       Dim MinDist As Integer = 10000
       For k As Integer =0 to nMonsters-1
             Dim monsterNode As Integer = nodeID(monRow(k),monCol(k),nCol)
             Call FindPath(Tree,TreeNumber,monsterNode,targetNode(i),ninst,instList)
             If ninst<MinDist and ninst>-1 Then
               MinDist=ninst
             End If           
       Next
       If MinDist>1000 Then ' this node is not accesible to monster at current state of map
          For k As Integer =0 to nMonsters-1
             Dim EulerDist As Integer = Math.SQRT ( (iRow(i)-monRow(k))^2 + (iCol(i)-monCol(k))^2 )
             If EulerDist<MinDist Then
               MinDist=EulerDist
             End If               
          Next
       End If
       targetCost(i)=MinDist
  Else
    targetNode(i) =  -1
    targetCost(i) = -1000000
  End If
 ' Console.Error.WriteLine("tn=" & targetNode(i) & " tc=" & targetCost(i) & " ir=" & iRow(i) & " " & iCol(i) )
Next

' sort nodes by cost
Array.Sort(targetCost, targetNode)
Array.Reverse(targetCost)
Array.REverse(targetNode)


End Sub

Public Sub CalculateNodeCost(ByVal map(,) aS Integer, _
                          ByRef mapCost(,) aS Integer, _
                          ByRef treeCost() aS Integer, _
                          ByRef LowCostTarget As Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal monRow() As Integer , _                         
                          ByVal MonCol() As Integer, _
                          ByVal nMonsters As Integer)

Dim Tree(10000,4) As Integer ' nodes in tree
Dim TreeNumber(10000) As Integer ' number of links for this node
Dim myNode As Integer = nodeID(MeRow,MeCol,nCol)
Dim ninst As Integer
Dim instList(1000) As Integer

Dim lCost As Integer = 10000000


Call CreateTree(map,nrow,ncol,MeRow,MeCol,Tree,TreeNumber)


For i As Integer = 0 to nRow-1
  For j As Integer = 0 to nCol-1
    If map(i,j)=0 Then  ' this is a free node
       Dim targetNode As Integer = nodeID(i,j,nCol)
       ' how far away are monsters
       Dim MinDist As Integer = 10000
       For k As Integer =0 to nMonsters-1
           Dim EulerDist As Integer = Math.SQRT ( (i-monRow(k))^2 + (j-monCol(k))^2 )
           If EulerDist<10 Then ' to aviod too long computation times
             Dim monsterNode As Integer = nodeID(monRow(k),monCol(k),nCol)
             Call FindPath(Tree,TreeNumber,monsterNode,targetNode,ninst,instList)
             If ninst<MinDist and ninst>-1 Then
               MinDist=ninst
             End If           
           End if
       Next
       If MinDist>1000 Then ' this node is not accesible to monster at current state of map
          For k As Integer =0 to nMonsters-1
             Dim EulerDist As Integer = Math.SQRT ( (i-monRow(k))^2 + (j-monCol(k))^2 )
             If EulerDist<MinDist Then
               MinDist=EulerDist
             End If               
          Next
          'Console.Error.WriteLine("ninst=" & ninst & " MinDist=" & MinDist)  
       End If
      mapCost(i,j)=nRow*nCol-MinDist ' higer cost = closer to monster
      TreeCost(targetNode)=mapCost(i,j)
    
      If TreeCost(targetNode)<lcost Then
        lcost=TreeCost(targetNode)
        LowCostTarget=targetNode
      End If
    
    End if 
  Next
Next

End Sub

 Public Function GetPathCost(ByVal treeCost() As Integer, _
                             ByVal ninst As Integer, _
                             ByVal instList() As Integer) As Integer                             

' calculate cost
    Dim ncost As Integer = 0
    For i As Integer = 0 To nInst-1
      ncost = ncost + treeCost(instList(i))
    Next
    
    Return ncost
 
 End Function


  Public Sub FindPath(ByVal treeLinks(,) As Integer, _
                        ByVal treeNumber() As Integer, _
'                        ByVal treeCost() As Integer, _                        
                        ByVal myIndex As Integer, _ 
                        ByVal exitIndex As Integer, 
                        ByRef ninst As Integer, _ 
'                        ByRef ncost As Integer, _                         
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
              
              Dim done As Integer = 0
              
             ' Console.Error.WriteLine("start=" & myIndex & " end=" & exitIndex)  

              
              While nToDoList>0 and done=0
                 ' do the first in list
                 Dim node As Integer = ToDoList(0)
                 CurDist=CurDist+1
                 
                '  Console.Error.WriteLine("nToDoList=" & nToDoList & " node=" & node)  
                 
                 For i As Integer = 0 To treeNumber(node)-1  ' I have several links
                   Dim son As Integer = treeLinks(node,i)
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
           '  Console.Error.WriteLine("myIndex=" & myIndex  & " dist(myIndex)=" &  dist(myIndex) )

           if dist(myIndex)>1000 then ' path not found
              Ninst=-1
           else
             ' start from myIndex until you find the exit

             Dim CurIndex As Integer = myIndex
             Dim tmpIndex As Integer = -1
             While CurIndex <> ExitIndex 
               Dim MinD As Integer = 10000
               For i As Integer = 0 To treeNumber(CurIndex)-1  ' I have  sons
                   Dim son As Integer = treeLinks(CurIndex,i)
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
    ' calculate cost
'    ncost=0
'    For i As Integer = 0 To nInst-1
'      ncost = ncost + treeCost(instList(i))
'    Next
    
    
    End Sub





     Public Function NodeID(ByVal iRow As Integer, ByVal iCol As Integer, ByVal nCol As Integer) As Integer
     
       Return iRow*nCol+iCol
     
     End Function
     
     

    Public Sub GetNeighbours(ByVal iRow As Integer, _
                             ByVal iCol As Integer, _
                             ByVal nRow As Integer, _
                             ByVal nCol As Integer, _
                             ByRef levoR As Integer, ByRef levoC As Integer, _
                             ByRef dolR As Integer, ByRef dolC As Integer, _
                             ByRef desnoR As Integer, ByRef desnoC As Integer, _
                             ByRef gorR As Integer, ByRef gorC As Integer)

           ' left
           levoR=iRow
           If iCol>0 then ' TU DODAJ POGLED PREKO MEJE LABIRINTA
               levoC=iCol-1
           Else
               levoC=nCol-1
           End if
           
           ' right
           desnoR=iRow
           If iCol<nCol-1 then ' TU DODAJ POGLED PREKO MEJE LABIRINTA
               desnoC=iCol+1
           Else
               desnoC=0
           End if
           
           ' up
           gorC=iCol
           If iRow>0 then ' TU DODAJ POGLED PREKO MEJE LABIRINTA
               gorR=iRow-1
           Else
               gorR=nRow-1
           End if
           
           ' Down
           dolC=iCol
           If iRow<nRow-1 then ' TU DODAJ POGLED PREKO MEJE LABIRINTA
               dolR=iRow+1
           Else
               dolR=0
           End if
     
     End Sub     
           
             
















     
     

     Public Sub PutWallsAroundMonsters(ByVal map(,) aS Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal monRow() As Integer , _                         
                          ByVal MonCol() As Integer, _
                          ByVal nMonsters As Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer)

         map(meRow,meCol)=10
' adding walls where monsters are
       for i as integer = 0 to nMonsters-1
         map(MonRow(i),MonCol(i))=-1
         
         'desno
         If MonRow(i)+1<=nRow then 
           If map(MonRow(i)+1,MonCol(i))<>-1 then
              map(MonRow(i)+1,MonCol(i))=-1
              If MonRow(i)+2<=nRow then 
                 If map(MonRow(i)+2,MonCol(i))<>-1 then
                    map(MonRow(i)+2,MonCol(i))=-1
                 End If
              End If
           End If
         End If

         'levo
         If MonRow(i)-1>=0 then 
           If map(MonRow(i)-1,MonCol(i))<>-1 then
              map(MonRow(i)-1,MonCol(i))=-1
              If MonRow(i)-2>=0 then 
                 If map(MonRow(i)-2,MonCol(i))<>-1 then
                    map(MonRow(i)-2,MonCol(i))=-1
                 End If
              End If
           End If
         End If


         'gor
         If MonCol(i)-1>=0 then 
           If map(MonRow(i),MonCol(i)-1)<>-1 then
              map(MonRow(i),MonCol(i)-1)=-1
              If MonCol(i)-2>=0 then 
                 If map(MonRow(i),MonCol(i)-2)<>-1 then
                    map(MonRow(i),MonCol(i)-2)=-1
                 End If
              End If
           End If
         End If

         'dol
         If MonCol(i)+1<=nCol then 
           If map(MonRow(i),MonCol(i)+1)<>-1 then
              map(MonRow(i),MonCol(i)+1)=-1
              If MonCol(i)+2<=nCol then 
                 If map(MonRow(i),MonCol(i)+2)<>-1 then
                    map(MonRow(i),MonCol(i)+2)=-1
                 End If
              End If
           End If
         End If


         
         'diagonale
         if MonRow(i)-1>=0  and MonCol(i)-1>=0 then
           map(MonRow(i)-1,MonCol(i)-1)=-1
         end if

         if MonRow(i)+1<=nRow  and MonCol(i)-1>=0 then
           map(MonRow(i)+1,MonCol(i)-1)=-1
         end if
         
         if MonRow(i)-1>=0  and MonCol(i)+1<=nCol then
           map(MonRow(i)-1,MonCol(i)+1)=-1
         end if
         
         if MonRow(i)+1<=nrow  and MonCol(i)+1<=nCol then
           map(MonRow(i)+1,MonCol(i)+1)=-1
         end if         

         
       Next

     map(meRow,meCol)=0

    End Sub

  Public Sub CreateTree(ByVal map(,) aS Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer, _
                          ByRef Tree(,) As Integer, _
                          byRef TreeNumber() As Integer)

     
     Dim node As Integer
     Dim levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC As Integer 


     For i As Integer = 0 To nRow-1
        For j As Integer = 0 To nCol-1
          node=nodeID(i,j,nCol)
          TreeNumber(node)=0 ' there is zero links for this node      
          If map(i,j)=0 Then ' empty space
           ' where are nodes around me
            Call GetNeighbours(i,j,nRow,nCol,levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC)

            If map(dolR,dolC)=0 Then ' there is a link
              Tree(node,TreeNumber(node))=nodeID(dolR,dolC,nCol)
              TreeNumber(node)=TreeNumber(node)+1
            End if
            If map(gorR,gorC)=0 Then ' there is a link
              Tree(node,TreeNumber(node))=nodeID(gorR,gorC,nCol)
              TreeNumber(node)=TreeNumber(node)+1
            End if
            If map(desnoR,desnoC)=0 Then ' there is a link
              Tree(node,TreeNumber(node))=nodeID(desnoR,desnoC,nCol)
              TreeNumber(node)=TreeNumber(node)+1
            End if
            If map(levoR,levoC)=0 Then ' there is a link
              Tree(node,TreeNumber(node))=nodeID(levoR,levoC,nCol)
              TreeNumber(node)=TreeNumber(node)+1
            End if

          End If
        Next
     Next


     End Sub







     Public Sub ListOfTargets( _
                          ByVal mapTarget(,) aS Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByRef TargetList() As Integer, _
                          Byref TargetNumber As Integer)
                          
       TargetNumber=0

       For i As Integer = 0 To nRow-1   
         For j As Integer = 0 To nCol-1
            if maptarget(i,j)=1 then
              TargetList(TargetNumber)=nodeID(i,j,nCol)
              TargetNumber=TargetNumber+1
            End If
         Next
       Next
    End Sub



     Public Sub DisplayMap(ByVal map(,) aS Integer, _
                          ByVal mapTarget(,) aS Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal monRow() As Integer , _                         
                          ByVal MonCol() As Integer, _
                          ByVal nMonsters As Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer)

       map(meRow,meCol)=9
       for i as integer = 0 to nMonsters-1
         map(MonRow(i),MonCol(i))=1+i
       Next


       Dim row As String = ""
       For j As Integer = -1 To nCol
            row=row & "-"
       Next
       row=row & "  "
       For j As Integer = -1 To nCol
            row=row & "-"
       Next       
       
       Console.Error.WriteLine(row)  

     dim s as String
    For i As Integer = 0 To nRow-1
       row="|"
       For j As Integer = 0 To nCol-1
            if map(i,j)=-2 then
              s="?"
            else if map(i,j)=-1 then
              s="X"
            else if map(i,j)=0 then
              s=" "
            else 
              s=Convert.ToString(map(i,j))
            end if
            row=row & s
       Next
       row=row & "|  |"
       For j As Integer = 0 To nCol-1
            if maptarget(i,j)=1 then
              s="."
            else 
              s=" "
            end if
            row=row & s
       Next       
       row=row & "|"
       
       Console.Error.WriteLine(row)  
    Next
    
    
    
          row=""
       For j As Integer = -1 To nCol
            row=row & "-"
       Next
            row=row & "  "
       For j As Integer = -1 To nCol
            row=row & "-"
       Next


       Console.Error.WriteLine(row)  


      map(meRow,meCol)=0
       for i as integer = 0 to nMonsters-1
         map(MonRow(i),MonCol(i))=0
       Next

    
    End Sub





    Public Sub  UpdateMap(ByRef map(,) aS Integer, _
                          ByRef mapCopy(,) aS Integer, _
                          ByRef mapTarget(,) aS Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer, _                          
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer, _
                          ByVal levo As String , _                         
                          ByVal dol As String , _                         
                          ByVal desno As String , _                         
                          ByVal gor As String)


            Dim levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC As Integer 

            ' where are nodes around me
            Call GetNeighbours(MeRow,MeCol,nRow,nCol,levoR,levoC,dolR,dolC,desnoR,desnoC,gorR,gorC)


            If levo="_" then 
               map(levoR,levoC)=0   ' free space               
               if mapTarget(levoR,levoC)<>-1 Then
                  mapTarget(levoR,levoC)=1 ' becomes a target
                End If               
            Else
               map(levoR,levoC)=-1  ' wall
            End If
            
            If dol="_" then 
               map(dolR,dolC)=0   ' free space
               if mapTarget(dolR,dolC)<>-1 Then
                  mapTarget(dolR,dolC)=1 ' becomes a target
                End If                              
            Else
               map(dolR,dolC)=-1  ' wall
            End If
            
            If desno="_" then 
               map(desnoR,desnoC)=0   ' free space
               if mapTarget(desnoR,desnoC)<>-1 Then
                  mapTarget(desnoR,desnoC)=1 ' becomes a target
                End If                              
            Else
               map(desnoR,desnoC)=-1  ' wall
            End If
            
            If gor="_" then 
               map(gorR,gorC)=0   ' free space
               if mapTarget(gorR,gorC)<>-1 Then
                  mapTarget(gorR,gorC)=1 ' becomes a target
                End If                            
            Else
               map(gorR,gorC)=-1  ' wall
            End If

' copy map
    For i As Integer = 0 To nRow-1
      For j As Integer = 0 To nCol-1
            mapCopy(i,j)=map(i,j)
      Next
    Next
     
         End Sub



     Public Sub GetDirection(ByVal MeRow As Integer, _
                             ByVal MeCol As Integer, _
                             ByVal nRow As Integer, _
                             ByVal nCol As Integer, _
                             ByVal nextRow As Integer, _
                             ByVal nextCol As Integer, _
                             ByRef Dir As String)

            ' A = dol
            ' E = gor
            ' D = desno
            ' C = levo
            ' B = stop   
Dir="WW"

             If nextCol=meCol Then ' going up or down
               If nextRow=meRow+1 Then  ' normal step down
                 Dir="A"
               Else If nextRow=meRow-1 Then ' normal step up
                 Dir="E"
               Else If nextRow=nRow-1 Then ' on the other side
                 Dir="E"
               Else If nextRow=0 Then ' on the other side
                 Dir="A"
               End If
             Else If nextRow=meRow Then  ' left or right
                If nextCol=meCol+1 Then ' right
                  Dir="D"
                Else If nextCol=meCol-1 Then ' left
                  Dir="C"
                Else If nextCol=nCol-1 Then ' on the other side
                  Dir="D"
                Else If nextCol=0 Then ' on the other side
                  Dir="C"
                End if
             Else
                Dir="B"
             End If
             
     End Sub


    Public Sub GoToTarI  (ByVal Tari As Integer, _
                          ByVal MeRow As Integer, _
                          ByVal MeCol As Integer, _
                          ByVal nRow aS Integer, _
                          ByVal nCol As Integer )
    
             Dim dir As String
             ' if no targets are accesible
             Dim nextCol As Integer = tari mod ncol
             Dim nextRow As Integer =(tari- nextCol)/ncol    
    
             Call GetDirection(MeRow,MeCol,nRow,nCol,nextRow,nextCol,Dir)   
             Console.Error.WriteLine("MeRow= " & MeRow & " MeCol= " & MeCol ) 
             Console.Error.WriteLine("dir= " & dir & " tari= " & tari &  " nextRow= " & nextRow & " nextCol= " & nextCol ) 
      
             Console.WriteLine(dir)    
    
    End Sub

    Sub Main ()
        
        Dim nRow as Integer
        Dim nCol as Integer
        nCol = Console.ReadLine()
        nRow = Console.ReadLine()

        Dim Tree(10000,4) As Integer ' nodes in tree
        Dim TreeNumber(10000) As Integer ' number of links for this node
        Dim TreeCost(10000) As Integer ' number of links for this node
        
        Dim TargetList(10000) As Integer
        Dim TargetNumber As Integer
        Dim LowCostTarget AS Integer
        
        Dim ninst As Integer
        Dim instList(1000) As Integer

        Dim map(nRow,nCol) As Integer
        Dim mapCost(nRow,nCol) As Integer
        Dim mapCopy(nRow,nCol) As Integer        
        Dim mapTarget(nRow,nCol) As Integer
        For i As Integer = 0 To nRow-1
          For j As Integer = 0 To nCol-1
            map(i,j)=-2  ' -2 = unknown tile
            mapTarget(i,j)=0 ' nothin is a target
          Next
        Next

        Dim nMonsters as Integer = Console.ReadLine() -1

        Console.Error.WriteLine("fII=" & nRow & " sII=" & nCol & " nMonst=" & nMonsters)
    
    
        
    
        ' game loop
        While True
            Dim levo as String = Console.ReadLine()
            Dim dol as String = Console.ReadLine()
            Dim desno as String = Console.ReadLine()
            Dim gor as String  = Console.ReadLine()

            Console.Error.WriteLine("1I=" & levo & " 2I=" & dol & " 3I=" & desno & " 4I=" & gor)

            Dim MonRow(nMonsters-1) as Integer
            Dim MonCol(nMonsters-1) as Integer
            Dim inputs as String()

            For i as Integer = 0 To nMonsters-1
                
                inputs = Console.ReadLine().Split(" ")
                MonRow(i) = inputs(0)
                MonCol(i) = inputs(1)
                map(MonRow(i),MonCol(i))=0 ' this space is free
                if mapTarget(MonRow(i),MonCol(i))<>-1 Then
                   mapTarget(MonRow(i),MonCol(i))=1
                End If
                        
                Console.Error.WriteLine("iI=" & i & " 5I=" & MonRow(i) & " 6I=" & MonCol(i) )            
            Next

            inputs = Console.ReadLine().Split(" ")
            Dim MeRow As Integer  = inputs(0)
            Dim MeCol As Integer = inputs(1)

            map(MeRow,MeCol)=0  ' open path
            mapTarget(MeRow,MeCol)=-1  ' not a target anymore
            
             ' Update mape based on what I see around me
             Call UpdateMap(map,mapCopy,mapTarget,MeRow,MeCol,nRow,nCol,levo,dol,desno,gor)
    
             ' Calculate node cost around me
             Dim TargetNodes(3) As Integer
             Dim TargetCost(8) As Integer
         '    Call DisplayMap(mapCopy,mapTarget,nrow,ncol,monRow,MonCol,nMonsters,MeRow,MeCol)
             Call CalculateNodeCostAroundMe(map,targetNodes,TargetCost,MeRow,MeCol,nRow,nCol,monRow,MonCol,nMonsters)
             
             ' Calculate cost of each free node 
             Call CalculateNodeCost(map,mapCost,treeCost,LowCostTarget,MeRow,MeCol,nRow,nCol,monRow,MonCol,nMonsters)
             
             CAll PutWallsAroundMonsters(mapCopy,nrow,ncol,monRow,MonCol,nMonsters,MeRow,MeCol)
             Call CreateTree(mapCopy,nrow,ncol,MeRow,MeCol,Tree,TreeNumber)
           '  Call DisplayMap(mapCopy,mapTarget,nrow,ncol,monRow,MonCol,nMonsters,MeRow,MeCol)
             
             Dim myNode As Integer = nodeID(MeRow,MeCol,nCol)
             ' make a list of targets
             Call ListOfTargets(mapTarget,nrow,ncol,TargetList,TargetNumber)
             
             ' find paths to all argets
             Dim DistToTar(TargetNumber-1) As Integer
             Dim DirID(TargetNumber-1) As Integer
             For i as integer = 0 to TargetNumber-1
                Call FindPath(Tree,TreeNumber,myNode,targetlist(i),ninst,instList)
                DirID(i)=instList(0)
                If ninst>=0 Then
                  DistToTar(i)=ninst
                Else
                  DistToTar(i)=100000
                End If
             Next
             Array.Sort(DistToTar,DirID)
             Dim tarI as integer = -1
             For i as integer = 0 to TargetNumber-1
               IF GetDanger(DirID(i),targetNodes,targetCost) > 3  Then
                  Tari = DirID(i)
                  Exit For
               End If
             Next
             If Tari=-1 Then
               Tari = targetNodes(0) ' safest way
             End if
             Console.Error.WriteLine("tari= " & tari )
             
          ' Call GoToTarI(TarI,MeRow,MeCol,nRow,nCol)
             
             Dim mini as integer = 1000000
             tari=-1
             for i as integer = 0 to targetnumber-1
                Call FindPath(Tree,TreeNumber,myNode,targetlist(i),ninst,instList)
                If ninst>=0 Then' path exists
                  'Dim pCost As Integer = GetPathCost(treeCost,ninst,instList)                  
            '      If pCost < mini Then
             '       mini=pCost
                  If ninst < mini then
                    mini=ninst                    
                    tari=instList(0)
                  end if
                End If
             next
 '            Console.Error.WriteLine("min pCost= " & mini )
             
             If tari=-1 Then
               tari=targetNodes(0) 'LowCostTarget ' get away from monsters
 '              Call DisplayMap(mapCopy,mapTarget,nrow,ncol,monRow,MonCol,nMonsters,MeRow,MeCol)
             End if
             
      '       Console.Error.WriteLine("tari= " & tari ) 
             
                       
              Call GoToTarI(TarI,MeRow,MeCol,nRow,nCol)
            
        End While
    End Sub
    

    
End Module
