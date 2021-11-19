'  https://www.codingame.com/training/medium/mars-lander-episode-2

Module Player
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.


 Private function IncRot(rotate As Integer, inc as Integer,ma as Integer)
               rotate=rotate+inc
               if rotate<-ma then 
                 rotate=-ma
               end if
               if rotate>ma then 
                 rotate=ma
               end if
               return rotate
 end function

    Private function SetRotatetoZero(rotate As Integer)
    
     if rotate<>0 then
     
              if rotate>15 then
                  rotate=rotate-15
               else if rotate<-15 then
                  rotate=rotate+15
               else 
                  rotate=0
               end if
                    
     end if

    Console.Error.WriteLine(rotate & " ee")   
    return rotate
    end function

    Sub Main ()
        Dim inputs as String()
        Dim surfaceN as Integer
        surfaceN = Console.ReadLine() ' the number of points used to draw the surface of Mars.

            Dim landX(surfaceN) as Integer ' X coordinate of a surface point. (0 to 6999)
            Dim landY(surfaceN) as Integer ' Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.

        For i as Integer = 0 To surfaceN-1

            inputs = Console.ReadLine().Split(" ")
            landX(i) = inputs(0)
            landY(i) = inputs(1)

        Next

        '  find target
        Dim tarX as Integer
        Dim tarY as Integer
        
        For i as Integer = 0 To surfaceN-1
           If landY(i)=landY(i+1) then
              tarX=(landX(i)+landX(i+1))/2
              tarY=landY(i)
           end if
        Next

        Console.Error.WriteLine("target = " & tarX & " " & tarY)     


        ' game loop
        While True
            Dim ma as integer = 40
            Dim X as Integer
            Dim Y as Integer
            Dim hSpeed as Integer ' the horizontal speed (in m/s), can be negative.
            Dim vSpeed as Integer ' the vertical speed (in m/s), can be negative.
            Dim fuel as Integer ' the quantity of remaining fuel in liters.
            Dim rotate as Integer ' the rotation angle in degrees (-90 to 90).
            Dim power as Integer ' the thrust power (0 to 4).
            inputs = Console.ReadLine().Split(" ")
            X = inputs(0)
            Y = inputs(1)
            hSpeed = inputs(2)
            vSpeed = inputs(3)
            fuel = inputs(4)
            rotate = inputs(5)
            power = inputs(6)

            dim oldr as integer = rotate
     
             ' check for height
       ma=35
       For i as Integer = 0 To surfaceN-1
           If tarX>landX(i) and x<landX(i) then
             if Y-landY(i)<1000 then
               ma=20
             end if
           end if
           If tarX<landX(i) and x>landX(i) then
             if Y-landY(i)<1000 then
               ma=20
             end if
           end if
        Next
         
             

             if x<tarX then ' need to go right
               if hspeed>0 then ' ok I am going right
                 if hspeed>18 then ' am I to fast? 
                   rotate = IncRot(rotate,+15,ma)
                 else if hspeed<15 then ' am I to slow?
                   rotate = IncRot(rotate,-15,ma)
                 else ' I am perfect, let glide
                   rotate=SetRotatetoZero(rotate)
                 end if
               else ' ok I should turn to right
                   rotate = IncRot(rotate,-15,ma)
               end if
             end if
             
             
             if x>tarX then ' need to go left
               if hspeed<0 then ' ok I am going left
                 if hspeed<-18 then ' am I to fast? 
                   rotate = IncRot(rotate,-15,ma)
                  else if hspeed>-15 then ' am I to slow?
                   rotate = IncRot(rotate,+15,ma)
                 else ' I am perfect, let glide
                   rotate=SetRotatetoZero(rotate)
                 end if
               else ' ok I should turn to left
                   rotate = IncRot(rotate,+15,ma)
               end if
             end if
         
             if vSpeed>-20 then 
               power=power-1
             else 
               power=power+1
             end if
             
             if power>4 then 
               power=4
             else if power<3 then
               power=3
             end if
             
             if Y<tary+500 then
               power=4
             end if
             
             
     


           'Console.Error.WriteLine("visina = " & y & " " & tarY & " ma " & ma)  
            if (y-tarY<200) then
              rotate=SetRotatetoZero(oldr)
            end if

        

            ' rotate power. rotate is the desired rotation angle. power is the desired thrust power.
            Console.WriteLine( rotate & " " & power)
        End While
    End Sub
End Module
