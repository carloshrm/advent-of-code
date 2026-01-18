namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var manifoldDiagram = File.ReadAllLines(@"./input.txt").Select(ln => ln.ToCharArray()).ToArray();

        var splittersTriggered = new HashSet<(int i, int j)>();
        var traversalMemo = new Dictionary<(int i, int j), ulong>();
        ulong pathCount = 1Ul;
        
        for (int i = 0; i < manifoldDiagram.Length; i++)
        {
            for (int j = 0; j < manifoldDiagram[i].Length; j++)
            {
                if (manifoldDiagram[i][j] == 'S')
                {
                    pathCount = TraverseDiagram(i, j, pathCount);
                    break;
                }
            }
        }               

        Console.WriteLine(splittersTriggered.Count());
        Console.WriteLine(pathCount);

        ulong TraverseDiagram(int row, int col, ulong n)
        {
            int nextRow = row + 1;

            if (traversalMemo.ContainsKey((nextRow, col)))
                return traversalMemo[(nextRow, col)];

            if (nextRow >= manifoldDiagram.First().Length)
                return 1;

            if (manifoldDiagram[nextRow][col] == '^')
            {
                splittersTriggered.Add((nextRow, col));
                var result = TraverseDiagram(nextRow, col + 1, n) + TraverseDiagram(nextRow, col - 1, n); 
                traversalMemo[(nextRow, col)] = result;
                return result;
            } else
                return TraverseDiagram(nextRow, col, n);
        }
    }    
}
