using System.Numerics;

namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var paperMap = File.ReadAllText(@"./input.txt").Split('\n').Select(s => s.TrimEnd('\r').Select(icon => icon == '@').ToArray()).ToArray();
        int lineCount = paperMap.Length;
        int lineLength = paperMap.First().Length;

        var rollsToClear = new List<(int x, int y)>();
        ulong rollsRemoved = 0;
        do
        {
            rollsToClear.ForEach(roll => paperMap[roll.x][roll.y] = false);
            rollsToClear.Clear();

            for (int i = 0; i < lineCount; i++)
            {
                for (int j = 0; j < lineLength; j++)
                {
                    if (paperMap[i][j] && CountAdjacentRolls(i, j) < 4)
                        rollsToClear.Add((i, j));
                }
            }
            rollsRemoved += (ulong)rollsToClear.Count;

        } while (rollsToClear.Count != 0);


        Console.WriteLine($" rolls {rollsRemoved}");

        int CountAdjacentRolls(int line, int col)
        {
            int rollCount = 0;
            for (int x = -1; x <= 1; x++)
            {
                int xOffset = line + x;
                if (xOffset < 0 || xOffset >= lineCount)
                    continue;

                for (int y = -1; y <= 1; y++)
                {
                    int yOffset = col + y;
                    if (yOffset < 0 || yOffset >= lineLength || (x == 0 && y == 0))
                        continue;

                    if (paperMap[xOffset][yOffset])
                        rollCount++;
                }
            }

            return rollCount;
        }

        List
    }
}
