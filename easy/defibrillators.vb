' https://www.codingame.com/training/easy/defibrillators

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.

    Sub Main ()
        
        Dim LON as String
        LON = Console.ReadLine()

        ' convert lon to number
        Dim fLON as Double = Convert.ToDouble(REPLACE(LON,",","."))*3.141592/180.0
       
        

        Dim LAT as String
        LAT = Console.ReadLine()

        ' convert lon to number
        Dim fLAT as Double = Convert.ToDouble(REPLACE(LAT,",","."))*3.141592/180.0


        Dim N as Integer
        N = Console.ReadLine()

       dim num(N) as string
       dim name(N) as string
      dim addr(N) as string
      dim phone(N) as string
       dim dlon(N) as Double
      dim dlat(N) as Double
      dim x as double
      dim y as double
      dim d as double
      dim mind as double = 10000
      dim j as integer

        For i as Integer = 0 To N-1
            Dim DEFIB as String
            DEFIB = Console.ReadLine()
            Dim Array() As String = Split(DEFIB,";")
           num(i)=Array(0)
            name(i)=Array(1)
            addr(i)=Array(2)
           phone(i)=Array(3)
          dlon(i)=Convert.ToDouble(REPLACE(Array(4),",","."))*3.141592/180.0
         dlat(i)=Convert.ToDouble(REPLACE(Array(5),",","."))*3.141592/180.0
       
         x=(dlon(i)-flon)*Math.cos(0.5*(dlon(i)+flon))
         y=dlat(i)-flat
         d=math.sqrt(x*x+y*y)*6371
       
         if d<mind then
           j=i
           mind=d
         end if
       
       '  Console.Error.WriteLine(name(j))
       
        Next

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")

        Console.WriteLine(name(j))
    End Sub
End Module
