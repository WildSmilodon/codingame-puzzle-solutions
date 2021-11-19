' https://www.codingame.com/training/medium/telephone-numbers

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Private Sub AddDigit(ByRef trie(1000) as Integer, ByRef father(1000) as Integer, ByRef nt as Integer,ByRef sons(1000,10) As Integer,ByRef ns(1000) As Integer ,ByVal digit As Integer, ByVal Id As Integer)
       ' Console.Error.WriteLine(digit & " " & id)
        
        Dim Ifound As Integer = 0
        
        For i As Integer = 0 to ns(id)
          If trie(sons(id,i))=digit Then
            ' found this in the trie, go deeper
            Console.Error.WriteLine(digit & " xxx " & id)
            Call  AddDigit(trie,father,nt,sons,ns,digit,sons(id,i))
            iFound=1
          End if
        Next
        
        if iFound=0 then ' didn find a son, add a son
          nt=nt+1
          trie(nt)=digit
          father(nt)=id
          ns(id)=ns(id)+1
          sons(id,ns(id))=nt
        end if
        
    End Sub

    Sub Main ()
        
        Dim N as Integer
        N = Console.ReadLine()

'       set up array to remember phone numbers
        Dim a(N-1,29) as Integer
        Dim na(N-1) as Integer

        For i as Integer = 0 To N-1
            Dim telephone as String
            telephone = Console.ReadLine()
            ' Console.Error.WriteLine(telephone)
            For j as Integer = 0 To telephone.length-1
              na(i)=telephone.length
              a(i,j)=Convert.toInt32(telephone.substring(j,1))
            '  Console.Error.WriteLine(telephone.substring(j,1) & " " & a(i,j) & " " & na(i))
            Next
        Next
        
'       build a TRIE tree (https://en.wikipedia.org/wiki/Trie)
        Dim trie(100000) As Integer ' number stored in tire
        Dim nt As Integer ' number of nodes in tree
        Dim father(100000) AS integer ' father of ith node
        Dim sons(100000,10) As integer ' sons
        Dim ns(100000)As Integer 'number of sons
        
        trie(0)=-1 '  first node has no data
        father(0)=-1
        ns(0)=0
        nt=0
        
       
      
        For i as Integer = 0 To N-1  ' loop throug all phone numbers 
            Dim id As Integer = 0
            For j as Integer = 0 To na(i)-1   ' loop throug all  digits 
              Dim digit as Integer = a(i,j)
              Dim Ifound As Integer = 0
                
              ' look at sons if my digit is already there
              For k As Integer = 0 to ns(id)-1
                If trie(sons(id,k))=digit Then
                 ' found this in the trie, go deeper
                  id=sons(id,k) ' my current position in the tree
                  iFound=1
                  Exit For  ' I can find it again so stop looking
                End if
              Next

              if iFound=0 then ' didn find a son, add a son
                nt=nt+1
                trie(nt)=digit
                father(nt)=id
                ns(id)=ns(id)+1
                sons(id,ns(id)-1)=nt
                id=nt
              end if

            Next ' digit
        Next 'phone number
        
   '     For i as Integer = 0 To nt
    '       Console.Error.WriteLine(i & " i ns " & ns(i) & " " & trie(i))
    '    Next        
      '  Console.Error.WriteLine(nt)

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")


        ' The number of elements (referencing a number) stored in the structure.
        Console.WriteLine(nt)
    End Sub
End Module
