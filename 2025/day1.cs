namespace aoc2025;

internal readonly record struct Rotation(char Direction, int Count);

internal class Program
{
    private static void Main(string[] args)
    {
        var rawInstructions = File.ReadAllText(@"./input.txt").Split("\n");
        
        var rotationList = rawInstructions.Select(
            (dir) => new Rotation(
                dir[0], 
                int.Parse(dir.Substring(1))
            )
        );

        int currentPosition = 50;
        int password = 0;

        foreach (var rotation in rotationList)
        {
            password += (int)Math.Floor(rotation.Count / 100.0); // +n full spins

            int clicks = rotation.Count % 100;

            int nextPosition = (currentPosition + (rotation.Direction == 'L' ? -clicks : clicks)) % 100;
            if (nextPosition < 0)
                nextPosition += 100;

            bool crossedZero = rotation.Direction == 'L' 
                ? (nextPosition > currentPosition) 
                : (nextPosition < currentPosition);

            if (nextPosition == 0 || (crossedZero && !(currentPosition == 0)))
                password++;
            
            currentPosition = nextPosition;                  
        }

        Console.WriteLine($"Password: {password}");
    }
}
