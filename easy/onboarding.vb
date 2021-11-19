' /https://www.codingame.com/training/easy/onboarding

Module Player
' CodinGame planet is being attacked by slimy insectoid aliens.
' <---
' Hint:To protect the planet, you can implement the pseudo-code provided in the statement, below the player.

    Sub Main ()
        
        ' game loop
        While True
            Dim enemy1 as String
            enemy1 = Console.ReadLine() ' name of enemy 1

            Dim dist1 as Integer
            dist1 = Console.ReadLine() ' distance to enemy 1

            Dim enemy2 as String
            enemy2 = Console.ReadLine() ' name of enemy 2

            Dim dist2 as Integer
            dist2 = Console.ReadLine() ' distance to enemy 2

            ' Write an action using Console.WriteLine()
            ' To debug: Console.Error.WriteLine("Debug messages...")


            ' You have to output a correct ship name to shoot ("Buzz", enemy1, enemy2, ...)
            Console.WriteLine("name of the enemy")
        End While
    End Sub
End Module
