' https://www.codingame.com/training/easy/temperatures

Module Solution
' Auto-generated code below aims at helping you parse
' the standard input according to the problem statement.


    Sub Main ()
        dim mincifra as integer = 10000
        Dim n as Integer
        n = Console.ReadLine() ' the number of temperatures to analyse

        Dim temps as String
        temps = Console.ReadLine() ' the n temperatures expressed as integers ranging from -273 to 5526

        ' Write an action using Console.WriteLine()
        ' To debug: Console.Error.WriteLine("Debug messages...")
        Console.Error.WriteLine(n)
        Console.Error.WriteLine(temps)
        
        Dim T() As String = Split(temps)
'        Dim iT() = T.ConvertAll(Function(T) Int32.Parse(T))

       dim i as integer
       dim cifra as integer
       
       if n=0 then
         mincifra=0
       else
       
        for i=0 to n-1
          cifra = CInt(T(i))
             
         if math.Abs(cifra)<math.abs(mincifra) then
           mincifra=cifra
         else if math.Abs(cifra)=math.abs(mincifra) then
           if cifra>0 then
             mincifra=cifra
           end if
         end if
        
        next
      end if
          Console.WriteLine(mincifra)
    End Sub
End Module
