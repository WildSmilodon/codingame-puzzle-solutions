' https://www.codingame.com/multiplayer/bot-programming/ghost-in-the-cell

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.
 
     Public Sub FindBestMove(ByVal factoryCount As Integer, _
                             ByVal factoryNumLinks()  As Integer, _ 
                             ByVal factoryLinks(,) As Integer, _
                             ByVal factoryDistaces(,) As Integer, _
                             ByVal factoryOwner(,) As Integer, _
                             ByVal factoryCyborgs(,) As Integer, _
                             ByVal factoryProduction(,) As Integer, _
                             ByVal troopOwner() As Integer, _
                             ByVal troopStart() As Integer, _
                             ByVal troopEnd() As Integer, _
                             ByVal troopCyborgs() As Integer, _
                             ByVal troopETA() As Integer, _
                             ByVal troopNumber As Integer, _
                             ByVal moveStart() As Integer, _
                             ByVal moveTarget() As Integer, _
                             ByVal moveETA() As Integer, _
                             ByVal moveCyborgs() As Integer, _
                             ByVal moveNumber As Integer, _
                             ByVal moveCombosList(,) As Integer, _
                             ByVal moveCombosNumber() As Integer, _
                             ByVal moveCombos As Integer, _
                             ByRef moveBest As Integer)


            moveBest = -1
            Dim maxScore As Integer = 0
            Dim score(20) As Integer
            
            For i As Integer = 0 To moveCombos-1
            
              ' add troops for chosen move combo
               For j As Integer = 0 To moveCombosNumber(i)-1
               
                 troopNumber = troopNumber +1 ' will add a troop according to move
                 troopOwner(troopNumber-1)=1
                 troopStart(troopNumber-1)=moveStart(moveCombosList(i,j))
                 troopEnd(troopNumber-1)=moveTarget(moveCombosList(i,j))
                 troopCyborgs(troopNumber-1)=moveCyborgs(moveCombosList(i,j))
                 troopETA(troopNumber-1)=moveETA(moveCombosList(i,j))
                 factoryCyborgs(moveStart(moveCombosList(i,j)),0)=factoryCyborgs(moveStart(moveCombosList(i,j)),0)-moveCyborgs(moveCombosList(i,j))
                 
               Next
       
               ' estimate move combo impact
               Call ForeseeFuture(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction,troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber)
               Call EstimateMyScore(score,factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction,troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber)
               
               ' return now to normal state
               For j As Integer = 0 To moveCombosNumber(i)-1

                 factoryCyborgs(moveStart(moveCombosList(i,j)),0)=factoryCyborgs(moveStart(moveCombosList(i,j)),0)+moveCyborgs(moveCombosList(i,j))
                 troopNumber = troopNumber -1
            
               Next
            
            
               If score(20)>MaxScore Then
                 MaxScore = score(20)
                 moveBest = i
               End if

               Console.Error.WriteLine(i & " " & score(20) & " " & score(0) & " best=" & moveBest )

            Next
            
            
    End Sub
            

 
 
    Public Sub DisplayMoves( ByVal moveStart() As Integer, _
                             ByVal moveTaget() As Integer, _
                             ByVal moveCyborgs() As Integer, _
                             ByVal moveNumber As Integer, _
                             ByVal moveCombosList(,) As Integer, _
                             ByVal moveCombosNumber() As Integer, _
                             ByVal moveCombos As Integer)
                             
 
    Console.Error.WriteLine("moveNumber=" & moveNumber )
    For i As Integer = 0 To moveNumber-1    
       Console.Error.WriteLine("MOVE f=" & moveStart(i) & " to= " & moveTaget(i) & " cy=" & moveCyborgs(i)  )    
    Next
    
    Console.Error.WriteLine("moveCombos=" & moveCombos )
    For i As Integer = 0 To moveCombos-1
       For j As Integer = 0 To moveCombosNumber(i)-1
         Console.Error.WriteLine(i & " COMBO=" & moveCombosList(i,j) )
       Next
    Next
    
    
    End Sub
 



 
    Public Sub ListMoves    (ByVal factoryCount As Integer, _
                             ByVal factoryNumLinks()  As Integer, _ 
                             ByVal factoryLinks(,) As Integer, _
                             ByVal factoryDistaces(,) As Integer, _
                             ByVal factoryOwner(,) As Integer, _
                             ByVal factoryCyborgs(,) As Integer, _
                             ByVal factoryProduction(,) As Integer, _
                             ByVal troopOwner() As Integer, _
                             ByVal troopStart() As Integer, _
                             ByVal troopEnd() As Integer, _
                             ByVal troopCyborgs() As Integer, _
                             ByVal troopETA() As Integer, _
                             ByVal troopNumber As Integer, _
                             ByRef moveStart() As Integer, _
                             ByRef moveTarget() As Integer, _
                             ByRef moveETA() As Integer, _
                             ByRef moveCyborgs() As Integer, _
                             ByRef moveNumber As Integer, _
                             ByRef moveCombosList(,) As Integer, _
                             ByRef moveCombosNumber() As Integer, _
                             Byref moveCombos As Integer)

     
    moveNumber=0

    ' go through my factories
    For myFactory as Integer = 0 To factoryCount-1
       If factoryOwner(myFactory,0)=1 Then
          For myLink as Integer = 0 To  factoryNumLinks(myFactory)-1
             Dim TargetFactory As Integer = factoryLinks(myFactory,myLink)
             Dim TimeStep As Integer =  factoryDistaces(myFactory,myLink)
             'If factoryOwner(TargetFactory,TimeStep)<>1 Then ' this is not my factory
             If factoryOwner(TargetFactory,0)<>1 Then ' this is not my factory
               If factoryCyborgs(myFactory,0) > factoryCyborgs(TargetFactory,TimeStep)+2 Then
                 moveStart(moveNumber)=myFactory
                 moveTarget(moveNumber)=TargetFactory
                 moveCyborgs(moveNumber)=factoryCyborgs(TargetFactory,TimeStep)+2
                 moveETA(moveNumber)=TimeStep
                 moveNumber=moveNumber+1
               End If
             End If
          Next
        End iF
    Next

    ' make move combos
    moveCombos=0
    ' first try single moves
    For i As Integer = 0 To moveNumber-1
       moveCombosList(i,0)=i
       moveCombosNumber(i)=1
       moveCombos=moveCombos+1
    Next
    
    ' next try comobos of 2 moves
    For  i As Integer = 0 To moveNumber-1
       For j As Integer = i+1 To moveNumber-1
          Dim moveOK As Integer = 0
          If moveStart(i)<>moveStart(j) Then ' not from the same factory
            moveOK = 1
          Else ' two moves from the same factory
             If factoryCyborgs(moveStart(i),0) > moveCyborgs(i)+moveCyborgs(j)+2 Then
               moveOK = 1
             End If
          End if
          If moveOK = 1 Then
            moveCombosList(moveCombos,0)=i
            moveCombosList(moveCombos,1)=j
            moveCombosNumber(moveCombos)=2
            moveCombos=moveCombos+1
          End If
       Next
    Next

    
    ' next try comobos of 3 moves
    For  i As Integer = 0 To moveNumber-1
       For j As Integer = i+1 To moveNumber-1
          For k As Integer = j+1 To moveNumber-1
          Dim moveOK As Integer = 0
            If moveStart(i)<>moveStart(j) and moveStart(i)<>moveStart(k) and moveStart(k)<>moveStart(j) Then ' not from the same factory
              moveOK = 1
            Else If moveStart(i)=moveStart(j) and moveStart(i)=moveStart(k) and moveStart(k)=moveStart(j) Then
               If factoryCyborgs(moveStart(i),0) > moveCyborgs(i)+moveCyborgs(j)+moveCyborgs(k)+2 Then
                 moveOK = 1
               End If
            Else If moveStart(i)=moveStart(j) Then      
               If factoryCyborgs(moveStart(i),0) > moveCyborgs(i)+moveCyborgs(j)+2 Then
                 moveOK = 1
               End If
            Else If moveStart(i)=moveStart(k) Then      
               If factoryCyborgs(moveStart(i),0) > moveCyborgs(i)+moveCyborgs(k)+2 Then
                 moveOK = 1
               End If
            Else If moveStart(j)=moveStart(k) Then      
               If factoryCyborgs(moveStart(j),0) > moveCyborgs(j)+moveCyborgs(k)+2 Then
                 moveOK = 1
               End If
            End if
            If moveOK = 1 Then
              moveCombosList(moveCombos,0)=i
              moveCombosList(moveCombos,1)=j
              moveCombosList(moveCombos,2)=k
              moveCombosNumber(moveCombos)=3
              moveCombos=moveCombos+1
            End If
         Next
       Next
    Next
    
    
    ' add thid
    
    End Sub
 
 

 
     Public Sub EstimateMyScore(ByRef Score() As Integer, _
                             ByVal factoryCount As Integer, _
                             ByVal factoryNumLinks()  As Integer, _ 
                             ByVal factoryLinks(,) As Integer, _
                             ByVal factoryDistaces(,) As Integer, _
                             ByRef factoryOwner(,) As Integer, _
                             ByRef factoryCyborgs(,) As Integer, _
                             ByVal factoryProduction(,) As Integer, _
                             ByVal troopOwner() As Integer, _
                             ByVal troopStart() As Integer, _
                             ByVal troopEnd() As Integer, _
                             ByVal troopCyborgs() As Integer, _
                             ByVal troopETA() As Integer, _
                             ByVal troopNumber As Integer)


         Score(0)=0
         For TimeStep As Integer = 0 To 20 ' now and twenty steps into the future
            If TimeStep>0 Then
              Score(TimeStep)=0 'Score(TimeStep)-1
            End if
            For i as Integer = 0 To factoryCount-1
                 If factoryOwner(i,TimeStep)=1 Then
                     Score(TimeStep)=Score(TimeStep)+(factoryProduction(i,TimeStep)+1)
                 End If            
            Next         
         Next
         
    End Sub



 
    Public Sub ForeseeFuture(ByVal factoryCount As Integer, _
                             ByVal factoryNumLinks()  As Integer, _ 
                             ByVal factoryLinks(,) As Integer, _
                             ByVal factoryDistaces(,) As Integer, _
                             ByRef factoryOwner(,) As Integer, _
                             ByRef factoryCyborgs(,) As Integer, _
                             ByVal factoryProduction(,) As Integer, _
                             ByVal troopOwner() As Integer, _
                             ByVal troopStart() As Integer, _
                             ByVal troopEnd() As Integer, _
                             ByVal troopCyborgs() As Integer, _
                             ByVal troopETA() As Integer, _
                             ByVal troopNumber As Integer)


         For TimeStep As Integer = 1 To 20 ' twenty steps into the future
    
            ' Produce new cyborgs in all factories
            For i as Integer = 0 To factoryCount-1
                 factoryOwner(i,TimeStep)=factoryOwner(i,TimeStep-1)
                 factoryProduction(i,TimeStep)=factoryProduction(i,TimeStep-1)
                 If factoryOwner(i,TimeStep)<>0 Then
                    factoryCyborgs(i,TimeStep)=factoryCyborgs(i,TimeStep-1)+factoryProduction(i,TimeStep-1)  
                 Else
                    factoryCyborgs(i,TimeStep)=factoryCyborgs(i,TimeStep-1)
                 End if
            Next
            ' Execute user orders

            ' check for simulateus arrival of troops

            ' Move existing troops
            For i as Integer = 0 To troopNumber-1
             ' Console.Error.WriteLine(" ETa " & troopETA(i) & " ts=" & TimeStep )
              If TimeStep=troopETA(i) Then
                  ' Solve battles                  
                 'Console.Error.WriteLine(" arrival at f= " & troopEnd(i) & " ts=" & TimeStep )
                  If troopOwner(i)=factoryOwner(troopEnd(i),TimeStep) Then  ' reinforcements have arrived
                    factoryCyborgs(troopEnd(i),TimeStep)=factoryCyborgs(troopEnd(i),TimeStep)+troopCyborgs(i)
                  Else If troopOwner(i)<>factoryOwner(troopEnd(i),TimeStep) Then  ' battle
                    IF troopCyborgs(i) > factoryCyborgs(troopEnd(i),TimeStep) Then ' troop wins 
                      factoryOwner(troopEnd(i),TimeStep)=troopOwner(i)
                      factoryCyborgs(troopEnd(i),TimeStep)=troopCyborgs(i)-factoryCyborgs(troopEnd(i),TimeStep)
                      ' Console.Error.WriteLine(" win at f= " & troopEnd(i) )
                    Else IF troopCyborgs(i) < factoryCyborgs(troopEnd(i),TimeStep) Then ' troop loses
                      factoryCyborgs(troopEnd(i),TimeStep)=factoryCyborgs(troopEnd(i),TimeStep)-troopCyborgs(i)                
                    Else ' draw
                      factoryOwner(troopEnd(i),TimeStep)=0
                      factoryCyborgs(troopEnd(i),TimeStep)=0
                    End If
                  End If' missing for joint arrival
                 
              End If
            Next

            
            
            

    
         Next
         
                                 
    End Sub
 
 
 
 
    Public Sub DisplayFactoryTree(ByVal factoryCount As Integer, _
                                  ByVal factoryNumLinks()  As Integer, _ 
                                  ByVal factoryLinks(,) As Integer, _
                                  ByVal factoryDistaces(,) As Integer, _
                                  ByVal factoryOwner(,) As Integer, _
                                  ByVal factoryCyborgs(,) As Integer, _
                                  ByVal factoryProduction(,) As Integer )

        For i as Integer = 0 To factoryCount-1
          Console.Error.WriteLine("f=" & i & " o=" & factoryOwner(i,0) & " cy=" & factoryCyborgs(i,0) & " prod= " & factoryProduction(i,0)  )
          For j as Integer = 0 To factoryNumLinks(i)-1
            Console.Error.WriteLine("l=" & factoryLinks(i,j) & " d= " & factoryDistaces(i,j) )
          Next
        Next

    End Sub

    Public Sub DisplayFactories(  ByVal factoryCount As Integer, _
                                  ByVal factoryNumLinks()  As Integer, _ 
                                  ByVal factoryLinks(,) As Integer, _
                                  ByVal factoryDistaces(,) As Integer, _
                                  ByVal factoryOwner(,) As Integer, _
                                  ByVal factoryCyborgs(,) As Integer, _
                                  ByVal factoryProduction(,) As Integer, _
                                  ByVal TimeStep As Integer)

        For i as Integer = 0 To factoryCount-1
          Console.Error.WriteLine("f=" & i & " o=" & factoryOwner(i,TimeStep) & " cy=" & factoryCyborgs(i,TimeStep) & " prod= " & factoryProduction(i,TimeStep)  )
        Next

    End Sub

 
    Public Sub DisplayTroopTree(ByVal troopOwner() As Integer, _
                                ByVal troopStart() As Integer, _
                                ByVal troopEnd() As Integer, _
                                ByVal troopCyborgs() As Integer, _
                                ByVal troopETA() As Integer, _
                                ByVal troopNumber As Integer)

        For i as Integer = 0 To troopNumber-1                                
             Console.Error.WriteLine("tr=" & i & " o=" & troopOwner(i) & " cy=" & troopCyborgs(i) & " st= " & troopStart(i) & " en= " & troopEnd(i) & " ETA= " & troopETA(i)  )
        Next
                                
    End Sub


    Public Sub DisplayBombs    (ByVal bombStart() As Integer, _
                                ByVal bombTarget() As Integer, _
                                ByVal bombOwner() As Integer, _
                                ByVal bombETA() As Integer, _
                                ByVal bombNumber As Integer)


        For i as Integer = 0 To bombNumber-1                                
             Console.Error.WriteLine("bomb=" & i & " o=" & bombOwner(i) &  " st= " & bombStart(i) & " en= " & bombTarget(i) & " ETA= " & bombETA(i)  )
        Next
                                
    End Sub


    Public Sub  ReadTurnInputData(ByRef factoryOwner(,) As Integer, _ 
                                  ByRef factoryCyborgs(,) As Integer, _
                                  ByRef factoryProduction(,) As Integer, _
                                  ByRef troopOwner() As Integer, _
                                  ByRef troopStart() As Integer, _
                                  ByRef troopEnd() As Integer, _
                                  ByRef troopCyborgs() As Integer, _
                                  ByRef troopETA() As Integer, _
                                  ByRef troopNumber As Integer, _
                                  ByRef bombStart() As Integer, _
                                  ByRef bombTarget() As Integer, _
                                  ByRef bombOwner() As Integer, _
                                  ByRef bombETA() As Integer, _                                  
                                  ByRef bombNumber As Integer)


            Dim inputs as String()
            Dim entityCount as Integer
            entityCount = Console.ReadLine() ' the number of entities (e.g. factories and troops)

            troopNumber=0
            bombNumber=0

            For i as Integer = 0 To entityCount-1
                Dim entityId as Integer
                Dim entityType as String
                Dim arg1 as Integer
                Dim arg2 as Integer
                Dim arg3 as Integer
                Dim arg4 as Integer
                Dim arg5 as Integer
                inputs = Console.ReadLine().Split(" ")
                entityId = inputs(0)
                entityType = inputs(1)
                arg1 = inputs(2)
                arg2 = inputs(3)
                arg3 = inputs(4)
                arg4 = inputs(5)
                arg5 = inputs(6)
                
                If entityType="FACTORY" Then
                   factoryOwner(entityId,0)=arg1
                   factoryCyborgs(entityId,0)=arg2
                   factoryProduction(entityId,0)=arg3
                End If
                
                If entityType="TROOP" Then
                  troopOwner(troopNumber)=arg1
                  troopStart(troopNumber)=arg2
                  troopEnd(troopNumber)=arg3
                  troopCyborgs(troopNumber)=arg4
                  troopETA(troopNumber)=arg5
                  troopNumber=troopNumber+1
                End If

                If entityType="BOMB" Then
                  bombOwner(bombNumber)=arg1
                  bombStart(bombNumber)=arg2
                  bombTarget(bombNumber)=arg3
                  bombETA(bombNumber)=arg4
                  bombNumber=bombNumber+1
                End If

            Next

    End Sub

    Sub Main ()
        Dim inputs as String()
        Dim factoryCount as Integer
        factoryCount = Console.ReadLine() ' the number of factories
        
        Dim factoryNumLinks(factoryCount-1) As Integer  ' number of links for each factory
        For i as Integer = 0 To factoryCount-1
          factoryNumLinks(i)=0
        Next
        Dim factoryLinks(factoryCount-1,15) As Integer  ' links for each factory
        Dim factoryDistaces(factoryCount-1,15) As Integer  ' links for each factory
        Dim factoryOwner(factoryCount-1,20) As Integer  ' current owner (0) and future owners 1->20
        Dim factoryCyborgs(factoryCount-1,20) As Integer  ' current owner (0) and future owners 1->20
        Dim factoryProduction(factoryCount-1,20) As Integer  ' current owner (0) and future owners 1->20

        Dim linkCount as Integer
        linkCount = Console.ReadLine() ' the number of links between factories

        Dim factory1(linkCount-1) as Integer
        Dim factory2(linkCount-1) as Integer
        Dim distance(linkCount-1) as Integer

        Dim troopOwner(100) As Integer
        Dim troopStart(100) As Integer
        Dim troopEnd(100) As Integer
        Dim troopCyborgs(100)  As Integer
        Dim troopETA(100) As Integer
        Dim troopNumber As Integer ' number of troop on map


        Dim moveStart(100) As Integer
        Dim moveTarget(100) As Integer
        Dim moveETA(100) As Integer
        Dim moveCyborgs(100) As Integer
        Dim moveNumber As Integer
        Dim moveBest As Integer

        Dim moveCombos As Integer
        Dim moveCombosList(1000,15) As Integer
        Dim moveCombosNumber(1000) As Integer

        Dim bombLeft As Integer = 2
        Dim bombNumber As Integer
        Dim bombStart(4) As Integer
        Dim bombTarget(4) As Integer
        Dim bombOwner(4) As Integer
        Dim bombETA(4) As Integer

        For i as Integer = 0 To linkCount-1

            inputs = Console.ReadLine().Split(" ")
            factory1(i) = inputs(0)
            factory2(i) = inputs(1)
            distance(i) = inputs(2)
            
            factoryLinks(factory1(i),factoryNumLinks(factory1(i)))=factory2(i)
            factoryLinks(factory2(i),factoryNumLinks(factory2(i)))=factory1(i)
            
            factoryDistaces(factory1(i),factoryNumLinks(factory1(i)))=distance(i)
            factoryDistaces(factory2(i),factoryNumLinks(factory2(i)))=distance(i)         
            
            factoryNumLinks(factory1(i))=factoryNumLinks(factory1(i))+1
            factoryNumLinks(factory2(i))=factoryNumLinks(factory2(i))+1

        Next
        
        

        ' game loop
        While True
        
            ' Read Input Data for the current turn
            Call ReadTurnInputData(factoryOwner,factoryCyborgs,factoryProduction, _
                                   troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber, _
                                   bombStart,bombTarget,bombOwner,bombETA,bombNumber)
        
            Call DisplayBombs(bombStart,bombTarget,bombOwner,bombETA,bombNumber)

             

            ' Debug displays
            'Call DisplayFactoryTree(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction)
            'Call DisplayTroopTree(troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber)

            ' Foresee future based on current situation
            Call ForeseeFuture(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction,troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber)

            ' List Possible moves
            Call ListMoves(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction, _
                         troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber, _
                         moveStart,moveTarget,moveETA,moveCyborgs,moveNumber, _
                         moveCombosList,moveCombosNumber,moveCombos)


            Call DisplayMoves(moveStart,moveTarget,moveCyborgs,moveNumber,moveCombosList,moveCombosNumber,moveCombos)

            Call FindBestMove(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction, _
                              troopOwner,troopStart,troopEnd,troopCyborgs,troopETA,troopNumber, _
                              moveStart,moveTarget,moveETA,moveCyborgs,moveNumber,moveCombosList,moveCombosNumber,moveCombos,moveBest)

      
            'Call DisplayFactories(factoryCount,factoryNumLinks,factoryLinks,factoryDistaces,factoryOwner,factoryCyborgs,factoryProduction,2)

            Dim output As String = "WAIT"
            
            If moveBest>=0 Then
            
              For i As Integer = 0 To moveCombosNumber(moveBest)-1
                   Output = Output & " ; " & "MOVE " & moveStart(moveCombosList(moveBest,i)) & " " & moveTarget(moveCombosList(moveBest,i)) & " " & moveCyborgs(moveCombosList(moveBest,i))  
              Next
            
            End If
            
            Console.WriteLine(Output)    
            
            ' Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
            'Console.WriteLine("MOVE " & moveStart(moveBest) & " " & moveTarget(moveBest) & " " & moveCyborgs(moveBest)  )    
            'Console.WriteLine("WAIT")
        End While
    End Sub
End Module
