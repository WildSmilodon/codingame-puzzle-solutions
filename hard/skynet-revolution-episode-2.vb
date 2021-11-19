' https://www.codingame.com/training/hard/skynet-revolution-episode-2

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Public Sub RemoveLink(ByRef treeLinks(,) As Integer, _
                         ByRef treeNumber() As Integer, _ 
                         ByVal CutFrom As Integer, _
                         ByVal CutTo As Integer)
                         
             ' remove cut link from tree
             For i As Integer = 0 To TreeNumber(cutFrom)-1
               If TreeLinks(cutFrom,i)=cutTo Then
                 For j As Integer =i To TreeNumber(cutFrom)-2
                   TreeLinks(cutFrom,j)=TreeLinks(cutFrom,j+1)
                 Next
                 TreeNumber(cutFrom)=TreeNumber(cutFrom)-1
                 Exit For
               End If
             Next
             ' remove cut link from tree
             For i As Integer = 0 To TreeNumber(cutTo)-1
               If TreeLinks(cutTo,i)=cutFrom Then
                 For j As Integer =i To TreeNumber(cutTo)-2
                   TreeLinks(cutTo,j)=TreeLinks(cutTo,j+1)
                 Next
                 TreeNumber(cutTo)=TreeNumber(cutTo)-1
                 Exit For
               End If
             Next
                         
                         
    End Sub                         


    Public Sub BuildTree(ByRef treeLinks(,) As Integer, _
                         ByRef treeNumber() As Integer, _ 
                         ByRef treeCost() As Integer, _                          
                         ByVal N As Integer, _
                         ByVal L As Integer, _
                         ByVal N1() As Integer, _
                         ByVal N2() As Integer)
    
           
          For i as Integer = 0 To N-1
             treeNumber(i)=0
             treeCost(i)=1
          Next
         
          For i as Integer = 0 To L-1
            treeLinks(N1(i),treeNumber(N1(i)))=N2(i)
            treeNumber(N1(i))=treeNumber(N1(i))+1
            treeLinks(N2(i),treeNumber(N2(i)))=N1(i)
            treeNumber(N2(i))=treeNumber(N2(i))+1
          Next
    
    
    End Sub


    Public Sub BuildVirusTree(ByRef treeLinks(,) As Integer, _
                         ByRef treeNumber() As Integer, _ 
                         ByRef treeCost() As Integer, _ 
                         ByVal N As Integer, _
                         ByVal L As Integer, _
                         ByVal N1() As Integer, _
                         ByVal N2() As Integer, _
                         ByVal E As Integer, _
                         ByVal EI() As Integer
                         )
    
           
          For i as Integer = 0 To N-1
             treeNumber(i)=0
             treeCost(i)=1
          Next
         
          For i as Integer = 0 To L-1
            ' only consider link, if it is not connected to exit node
            Dim iexit As Integer = 0
            For j as Integer = 0 To E-1
              If N1(i)=EI(j) or N2(i)=EI(j) Then
                iexit=1
                treeCost( N1(i) ) = 0
                treeCost( N2(i) ) = 0
              End if
            Next
            If iExit=0 Then
              treeLinks(N1(i),treeNumber(N1(i)))=N2(i)
              treeNumber(N1(i))=treeNumber(N1(i))+1
              treeLinks(N2(i),treeNumber(N2(i)))=N1(i)
              treeNumber(N2(i))=treeNumber(N2(i))+1
            End if
          Next
    
    
    End Sub



    Public Sub DisplayTree(ByRef treeLinks(,) As Integer, _
                         ByRef treeNumber() As Integer, _ 
                         ByVal N As Integer)


          For i as Integer = 0 To N-1
             Console.Error.WriteLine("node = " & i)
             For j as integer = 0 To treeNumber(i)-1
                Console.Error.WriteLine(treeLinks(i,j))
             Next
          Next
    
    
    End Sub
    
    Public Sub FindPath(ByVal treeLinks(,) As Integer, _
                        ByVal treeNumber() As Integer, _
                        ByVal treeCost() As Integer, _                        
                        ByVal myIndex As Integer, _ 
                        ByVal exitIndex As Integer, 
                        ByRef ninst As Integer, _ 
                        ByRef ncost As Integer, _                         
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
             'Console.Error.WriteLine("myIndex=" & myIndex  & " dist(myIndex)=" &  dist(myIndex) )

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
    
    ' calculate cost
    ncost=0
    For i As Integer = 0 To nInst-1
      ncost = ncost + treeCost(instList(i))
    Next
    
    
    End Sub




    Sub Main ()
        Dim inputs as String()

        Dim N as Integer ' the total number of nodes in the level, including the gateways
        Dim L as Integer ' the number of links
        Dim E as Integer ' the number of exit gateways
        inputs = Console.ReadLine().Split(" ")
        N = inputs(0)
        L = inputs(1)
        E = inputs(2)

        Dim N1(L-1) as Integer ' N1 and N2 defines a link between these nodes
        Dim N2(L-1) as Integer


        For i as Integer = 0 To L-1
            inputs = Console.ReadLine().Split(" ")
            N1(i) = inputs(0)
            N2(i) = inputs(1)
        Next

        Dim EI(E-1) as Integer
        For i as Integer = 0 To E-1            
            EI(i) = Console.ReadLine() ' the index of a gateway node
        Next

         ' create a tree
         Dim treeLinks(N-1,100) As Integer
         Dim treeNumber(N-1) As Integer ' number of liks for each node
         Dim treeCost(N-1) As Integer ' number of liks for each node  
         Dim VirustreeLinks(N-1,100) As Integer
         Dim VirustreeNumber(N-1) As Integer ' number of liks for each node         
         Dim VirusTreeCost(N-1) As Integer ' number of liks for each node  
        ' build tree
        Call BuildTree(treeLinks,treeNumber,treeCost,N,L,N1,N2) 
        Call BuildVirusTree(VirustreeLinks,VirusTreeNumber,VirusTreeCost,N,L,N1,N2,E,EI)
      '  Call DisplayTree(VirustreeLinks,VirusTreeNumber,N) 

     '   For i as Integer = 0 To N-1            
     '       Console.Error.WriteLine(i &" cost= " & VirusTreeCost(i))
     '   Next  

         ' path
         Dim ninst As Integer 
         Dim instList(1000) As Integer
         Dim instCost As Integer
         ' remember paths to exits
         Dim pathNumber(E-1) As Integer 
         Dim path(E-1,1000) As Integer

            Dim cutFrom As Integer
            Dim cutTo As Integer
 

        ' game loop
        While True
            Dim SI as Integer
            SI = Console.ReadLine() ' The index of the node on which the Skynet agent is positioned this turn


           ' Call DisplayTree(treeLinks,treeNumber,N) 

            ' find distances to each exit
            Dim ExitDist(E-1) As Integer
            Dim ShortDist As Integer = 10000
            Dim cex AS Integer = -1
            For i as Integer = 0 To E-1
               ExitDist(i)=1000
               pathNumber(i)=0
               If treeNumber(EI(i))>0 Then
                 ' find path to exit 
                 Call FindPath(treeLinks,treeNumber,treeCost,SI,EI(i),ninst,instCost,instList)
                 
                 ' remember path
                 pathNumber(i)=ninst
                 For j As Integer = 0 To pathNumber(i)-1
                   path(i,j)=instList(j)
                 Next
                 ' find shortest path
                 ExitDist(i)=ninst
                 If ninst<ShortDist then
                   ShortDist=ninst
                   cex=i
                 End if
                 
               End If
            Next
            
            Console.Error.WriteLine("cex=" & cex & " ShortDist=" & ShortDist)  
            
            ' Am i in imidiate danger cut shortest distance
            If ShortDist>1 Then 
               Dim found As Integer = 0
               ' virus is at least two steps away
    '           For i as Integer = 0 To E-1
    '             If pathNumber(i)>0 Then ' not a lone exit

'                   For j as Integer = i+1 To E-1
'                     If pathNumber(j)>0 Then ' not a lone exit
                     
 '                       If Path(i,pathNumber(i)-2) = Path(j,pathNumber(j)-2) Then ' they share a node
  '                        cex=i
   '                       found=1
    '                    End If
                     
'                     End If
 '                  Next
                 
 '                End If
  '            Next
              
              If found=0 Then ' scan tree for links between 
                 Dim mdist As Integer = 10000
                 For i as Integer = 0 To E-1
                   For j As Integer = 0 To TreeNumber(EI(i))-1
                     Dim iSon As Integer = treeLinks(EI(i),j)
                     
                     For k as Integer = i+1 To E-1
                       For l As Integer = 0 To TreeNumber(EI(k))-1
                         Dim kSon As Integer = treeLinks(EI(k),l)  
                         If iSon=kSon Then
                           cex=i
                           ' find cost to get here
                           Call FindPath(VirustreeLinks,VirustreeNumber,VirustreeCost,SI,iSon,ninst,instCost,instList)
                           Console.Error.WriteLine(iSon &" cost= " & instCost)
                           If instCost<mdist Then
                             mdist=instCost                     
                             cutFrom=iSon
                             cutTo=path(cex,pathNumber(cex)-1)
                             Console.Error.WriteLine("fr=" & cutFrom & " to= " & cutTo )  
                           End If
                         '  Console.Error.WriteLine("cex=" & cex & " " & iSon & " d=" & pathNumber(cex))  
                           cex=-1
                         End If
                       Next
                     Next
                     
                   Next
                 Next
              End If
              
            End If

            ' number of shortest distances
            Dim NShort as Integer = 0
            For i as Integer = 0 To E-1
              If ShortDist=ExitDist(i) Then
                nShort=nShort+1
              End if
            Next

            
            ' find path to chosen exit again
          '  Call FindPath(treeLinks,treeNumber,SI,EI(cex),ninst,instList)
            
            
           If cex>-1 then 
            If pathNumber(cex)=1 then
              cutFrom=path(cex,pathNumber(cex)-1)
              CutTo= SI
            Else
              cutFrom=path(cex,pathNumber(cex)-1)
              CutTo= path(cex,pathNumber(cex)-2)        
            End If
            End If 
             ' write command to screen 
             Console.WriteLine(cutFrom & " " & CutTo)
             ' update tree with cut link
             Call  RemoveLink(treeLinks,treeNumber,CutFrom,CutTo)

        End While
    End Sub
End Module
