using System.Numerics;

namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var batteries = File.ReadAllText(@"./input.txt").Split('\n').Select(s => s.TrimEnd('\r'));
        //Console.WriteLine($"total {batteries.Aggregate(0, (total, bank) => total + GetJoltage(bank))}"); // part 1

        ulong result = 0;
        foreach (var bank in batteries)
        {            
            var selectedBatteries = new Stack<int>();
            selectedBatteries.Push(0);

            for (int i = 1; i < bank.Length; i++)
            {
                int remainingBatteries = bank.Length - i;

                if (remainingBatteries < 12 - selectedBatteries.Count || selectedBatteries.Count == 0)
                    selectedBatteries.Push(i);
                else
                {
                    while (selectedBatteries.Count != 0 && remainingBatteries > 12 - selectedBatteries.Count && bank[i] > bank[selectedBatteries.Peek()])
                        selectedBatteries.Pop();

                    if (selectedBatteries.Count != 12)
                        selectedBatteries.Push(i);
                }
            }
            
            ulong joltageValue = ulong.Parse(string.Join("", selectedBatteries.Reverse().Select((i) => bank[i])));            
            result += joltageValue;
        }

        Console.WriteLine($" joltage {result}");
    }

    private static int GetJoltage(string bank)
    {
        int firstIndex = 0;
        for (int i = 1; i < bank.Length - 2; i++)
        {
            if (bank[firstIndex] < bank[i])
                firstIndex = i;
        }

        int secndIndex = firstIndex + 1;
        for (int i = firstIndex + 1; i < bank.Length - 1; i++)
        {
            if (bank[secndIndex] < bank[i])
                secndIndex = i;
        }

        return int.Parse($"{Char.GetNumericValue(bank[firstIndex])}{Char.GetNumericValue(bank[secndIndex])}");
    }
}
