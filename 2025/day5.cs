namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var input = File.ReadAllText(@"./input.txt").Split(new string[] { "\r\n\r\n" }, StringSplitOptions.RemoveEmptyEntries);
        var validRanges = input.First().Split('\n').Select(ln =>
        {
            var numbers = ln.Split('-');
            return (start: ulong.Parse(numbers.First()), end: ulong.Parse(numbers.Last()));
        });

        int freshIngredients = 0;
        foreach (var ingredient in input.Last().Split('\n').Select(ulong.Parse))
        {
            foreach (var range in validRanges)
            {
                if (ingredient >= range.start && ingredient <= range.end)
                {
                    freshIngredients++;
                    break;
                }

            }
        }
        Console.WriteLine(freshIngredients); // part 1

        var sortedRanges = validRanges.OrderBy((a) => a.start);
        var mergedRange = sortedRanges.First();

        ulong idCount = 0;
        foreach (var range in sortedRanges.Skip(1))
        {
            if (range.start > mergedRange.end)
            {
                idCount += (mergedRange.end - mergedRange.start) + 1;
                mergedRange = range;
                continue;
            }

            if (range.end > mergedRange.end)
                mergedRange.end = range.end;   
        }
        idCount += (mergedRange.end - mergedRange.start) + 1;

        Console.WriteLine($"ids {idCount}");
    }
}
