' https://www.codingame.com/training/medium/winamax-battle

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim n as Integer
        n = Console.ReadLine() ' the number of cards for player 1

        Dim cardp1(n) as String
        For i as Integer = 0 To n-1
            cardp1(i) = Console.ReadLine() ' the n cards of player 1
        Next

        Dim m as Integer
        m = Console.ReadLine() ' the number of cards for player 2

        Dim cardp2(m) as String
        For i as Integer = 0 To m-1
            cardp2(i) = Console.ReadLine() ' the m cards of player 2
        Next

        Dim cp1(20*(m+n)) as integer
        Dim cp2(20*(m+n)) as integer
        
        For i as Integer = 0 To n-1
          if cardp1(i).substring(0,1)="2" then 
            cp1(i)=2 
            end if
          if cardp1(i).substring(0,1)="3" then 
          cp1(i)=3 
          end if
          if cardp1(i).substring(0,1)="4" then 
          cp1(i)=4 
          end if
          if cardp1(i).substring(0,1)="5" then 
          cp1(i)=5 
          end if
          if cardp1(i).substring(0,1)="6" then 
          cp1(i)=6 
          end if
          if cardp1(i).substring(0,1)="7" then 
          cp1(i)=7 
          end if
          if cardp1(i).substring(0,1)="8" then 
          cp1(i)=8 
          end if
          if cardp1(i).substring(0,1)="9" then 
          cp1(i)=9
          end if
          if cardp1(i).substring(0,2)="10" then 
          cp1(i)=10 
          end if
          if cardp1(i).substring(0,1)="J" then 
          cp1(i)=11
          end if
          if cardp1(i).substring(0,1)="Q" then
          cp1(i)=12
          end if
          if cardp1(i).substring(0,1)="K" then
          cp1(i)=13 
          end if
          if cardp1(i).substring(0,1)="A" then
          cp1(i)=14
          end if
   '     Console.Error.WriteLine(cp1(i))
        next
        For i as Integer = 0 To m-1
          if (cardp2(i).substring(0,1)="2") then 
          cp2(i)=2
          end if
          if (cardp2(i).substring(0,1)="3") then
          cp2(i)=3
          end if
          if (cardp2(i).substring(0,1)="4") then
          cp2(i)=4 
          end if
          if (cardp2(i).substring(0,1)="5") then 
          cp2(i)=5 
          end if
          if (cardp2(i).substring(0,1)="6") then 
          cp2(i)=6 
          end if
          if (cardp2(i).substring(0,1)="7") then 
          cp2(i)=7
          end if
          if (cardp2(i).substring(0,1)="8") then 
          cp2(i)=8
          end if
          if (cardp2(i).substring(0,1)="9") then 
          cp2(i)=9 
          end if
          if (cardp2(i).substring(0,2)="10") then
          cp2(i)=10
          end if
          if (cardp2(i).substring(0,1)="J") then 
          cp2(i)=11
          end if
          if (cardp2(i).substring(0,1)="Q") then 
          cp2(i)=12
          end if
          if (cardp2(i).substring(0,1)="K") then 
          cp2(i)=13
          end if
          if (cardp2(i).substring(0,1)="A") then
          cp2(i)=14
          end if
  '     Console.Error.WriteLine(i & " cp2 " & cp2(i) & " " & cardp2(i))
        next

        
        dim nr as integer =0
        dim wc as integer =-1
'       begin round
        while n>0 and m>0
        
        nr=nr+1
        
       ' Console.Error.WriteLine(nr & " " & n & " " & m  & " " & cp1(0) & " " & cp2(0) & " " & cp1(4) & " " & cp2(4)  )
'       player 1 wins round
        if cp1(0)>cp2(0) THEN
          n=n+1
          cp1(n-1)=cp1(0)
          n=n+1
          cp1(n-1)=cp2(0)
         '  Console.WriteLine(cp1(n-1) & " n " & n) 
          
          for i as integer=0 to n-2
            cp1(i)=cp1(i+1)
          next
          n=n-1
    '      for i as integer=0 to n-1
    '        Console.WriteLine(cp1(i)) 
     '     next
          
          for i as integer=0 to m-2
            cp2(i)=cp2(i+1)
          next
          m=m-1
          

'       player 2 wins round
        else if cp1(0)<cp2(0) THEN
          m=m+1
          cp2(m-1)=cp1(0)
          m=m+1
          cp2(m-1)=cp2(0)

          for i as integer =0 to n-2
            cp1(i)=cp1(i+1)
          next
          n=n-1

          for i as integer=0 to m-2
            cp2(i)=cp2(i+1)
          next
          m=m-1            

'            war
          else if cp1(0)=cp2(0) THEN
           '   Console.Error.WriteLine("WAR")
              ' card 0 on the table
              ' cards 1,2,3 on the side
              ' card 4 fights
              wc=4
              dim konec as integer = 1
              while konec=1
              '      check if they have enough cards
                  if n>wc and m>wc then
              '       player 1 wins war
                        if cp1(wc)>cp2(wc) THEN
                        konec=0
                         for j as integer =0 to wc
                            n=n+1
                            cp1(n-1)=cp1(j)
                         next
                         for j as integer =0 to wc                            
                            n=n+1
                            cp1(n-1)=cp2(j)
                          next
          
                          for i as integer=0 to n-2-wc
                            cp1(i)=cp1(i+1+wc)
                          next
                          n=n-1-wc
 
                          for i as integer=0 to m-2-wc
                            cp2(i)=cp2(i+1+wc)
                          next
                          m=m-1-wc
          

'                      player 2 wins waar
                     else if cp1(wc)<cp2(wc) THEN
                       konec=0
                       for j as integer =0 to wc
                         m=m+1
                         cp2(m-1)=cp1(j)
                       next
                       for j as integer =0 to wc                       
                         m=m+1
                         cp2(m-1)=cp2(j)
                       next

                       for i as integer =0 to n-2-wc
                         cp1(i)=cp1(i+1+wc)
                       next
                       n=n-1-wc

                       for i as integer=0 to m-2-wc
                         cp2(i)=cp2(i+1+wc)
                       next
                       m=m-1-wc            

           '          there is another  war
                    else if cp1(wc)=cp2(wc) THEN
                  '  Console.Error.WriteLine("ANOTHER WAR") 
                    wc=wc+4
                    end if
                else ' pat
                  n=-1
                  m=-1
                  konec=0
                end if
                
                end while
          end if

'Console.Error.WriteLine(nr & " " & n & " " & m  )
        end while
        
          

 
        if n=-1 then Console.WriteLine("PAT")
        if n=0 then Console.WriteLine("2 " & nr)
        if m=0 then Console.WriteLine("1 " & nr)

    End Sub
End Module
