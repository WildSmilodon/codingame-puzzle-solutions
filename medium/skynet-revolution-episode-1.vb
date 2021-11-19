' https://www.codingame.com/training/medium/skynet-revolution-episode-1

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

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

        ' game loop
        Dim done as integer
        While True
            Dim SI as Integer
            SI = Console.ReadLine() ' The index of the node on which the Skynet agent is positioned this turn

            
            
            done=0

           ' sever links to gateways
            For i as Integer = 0 To E-1 ' loop over gateways
              for j as integer = 0 to L-1
                if EI(i)=N1(j) or EI(i)=N2(j) then
                  if  SI=N1(j) or SI=N2(j)  then
                    if done=0 then
                      Console.WriteLine(N1(j) & " " & N2(j) )
                      done=1
                      Exit For
                    end if
                  end if
                end if
              next
            next
        
           ' sever links to gateways
            if done=0 then
            For i as Integer = 0 To E-1
            ' Console.Error.WriteLine(EI(i))
             for j as integer = 0 to L-1
               if (EI(i)=N1(j) or EI(i)=N2(j)) then
                 if done=0 then
                 Console.WriteLine(N1(j) & " " & N2(j) )
                 done = 1
                 Exit For
                 end if
               end if
             next
            next
            end if

            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")


            ' Example: 0 1 are the indices of the nodes you wish to sever the link between
            'Console.WriteLine("0 1")
        End While
    End Sub
End Module
