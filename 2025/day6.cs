namespace aoc2025;

internal class Program
{
    static Dictionary<char, (Func<ulong, ulong, ulong> func, ulong initialVal)> operatorMap = new() {
        {'*', ((a, b) => a * b, 1UL)},
        {'+', ((a, b) => a + b, 0UL)},
    };

    private static void Main(string[] args)
    {
        var inputLines = File.ReadAllLines(@"./input.txt");        

        var operators = inputLines.Last().Split(' ', StringSplitOptions.RemoveEmptyEntries);
        var values = inputLines.SkipLast(1).Select(ln => ln.Split(' ', StringSplitOptions.RemoveEmptyEntries).Select(ulong.Parse));
                
        ulong total = 0;
        for (int i = 0; i < operators.Length; i++)
            total += values.Aggregate(operatorMap[operators[i][0]].initialVal, (res, val) => operatorMap[operators[i][0]].func(res, val.ElementAt(i)));

        Console.WriteLine(total); // part 1

        var fullOps = inputLines.Last();
        var fullDigits = inputLines.SkipLast(1);

        int startIndex = fullOps.Length - 1;
        total = 0;
        for (int i = fullOps.Length - 1; i >= 0; i--)
        {
            if (fullOps[i] != ' ')
            {
                var problemNumbers = new List<ulong>();
                for (int j = startIndex; j >= i; j--)
                {
                    string currentNumber = fullDigits.Aggregate("", (num, digitLn) => num += digitLn[j]).Trim();
                    problemNumbers.Add(ulong.Parse(currentNumber));
                }
                total += problemNumbers.Aggregate(operatorMap[fullOps[i]].initialVal, (res, val) => operatorMap[fullOps[i]].func(res, val));

                startIndex = i - 2; // -1 == empty col
            }

        }

        Console.WriteLine(total);
    }
}
