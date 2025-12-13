namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var rawIdRanges = File.ReadAllText(@"./input.txt").Split(',').Select((ln) => ln.Split('-'));

        Int64 invalidIdSum = 0;
        foreach (var range in rawIdRanges)
        {
            Console.WriteLine($"range {range[0]}-{range[1]}");
            for (var i = Convert.ToInt64(range.First()); i <= Convert.ToInt64(range.Last()); i++)
            {
                var id = i.ToString();
                if (CheckIdParts(id, 1))
                {
                    Console.WriteLine($"\t invalid id {id}");
                    invalidIdSum += i;
                }
            }
        }

        Console.WriteLine($"id sum {invalidIdSum}");

    }

    // part 1
    private static bool CheckId(string id)
    {
        var middleIndex = id.Length / 2;

        var firstPart = id.Substring(0, middleIndex);
        var secondPart = id.Substring(middleIndex);

        return (firstPart == secondPart);
    }

    // part 2
    private static bool CheckIdParts(string id, int chunkSize)
    {
        if (id.Length == 2)
            return id[0] == id[1];

        if (chunkSize >= id.Length)
            return false;

        if (id.Length % chunkSize != 0)
            return CheckIdParts(id, chunkSize + 1);

        bool isValid = true;
        string? chunk = id.Substring(0, chunkSize);
        for (int i = chunkSize; i < id.Length && isValid; i += chunkSize)
        {
            var part = id.Substring(i, chunkSize);
            if (i % chunkSize == 0 && part != chunk)
                isValid = false; 
        }        
        
        return isValid ? true : CheckIdParts(id, chunkSize + 1);
    }
}
