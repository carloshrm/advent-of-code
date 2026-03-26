using System.Numerics;
using System.Linq;

namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var input = File.ReadAllLines(@"./input.txt");

        var junctionBoxes = input.Select(ln => new JunctionBox(ln.Split(',', StringSplitOptions.RemoveEmptyEntries).Select(int.Parse))).ToList();

        var distanceMap = new Dictionary<JunctionBox, CircuitMapping?>();
        foreach (var targetBox in junctionBoxes)
        {
            CircuitMapping? circuitCandidate = null;
            foreach (var innerBox in junctionBoxes)
            {
                if (innerBox == targetBox) continue;

                var distance = targetBox.DistanceTo(innerBox);
                if (circuitCandidate == null || (distance != 0 && distance <= targetBox.DistanceTo(circuitCandidate.Box)))
                    circuitCandidate = new CircuitMapping { Distance = distance, Box = innerBox };
            }
            distanceMap[targetBox] = circuitCandidate;
        }

        var orderedMap = distanceMap.Where(entry => entry.Value != null).OrderBy(entry => entry.Value!.Distance);
        int limit = 10;
        for (int i = 0; i < limit; i++)
        {
            var (keyBox, targetBox) = orderedMap.ElementAt(i);
            if (keyBox.Circuit == null)
            {
                if (targetBox!.Box.Circuit != null)
                {
                    keyBox.Circuit = targetBox.Box.Circuit;
                    keyBox.Circuit.Add(keyBox);
                }
                else
                {
                    keyBox.Circuit = [targetBox.Box, keyBox];
                    targetBox.Box.Circuit = keyBox.Circuit;
                }
            } else
            {
                if (keyBox.Circuit.Contains(targetBox!.Box))
                {
                    // noop
                }
                else
                    keyBox.Circuit.Append(targetBox.Box);
            }
        }

        var circuits = orderedMap.Select(mapEntry => mapEntry.Value.Box.Circuit).ToList();
        Console.WriteLine(0);
    }    
}

public class JunctionBox(IEnumerable<int> vals)
{
    public (int x, int y, int z) Coords { get; set; } = (vals.ElementAt(0), vals.ElementAt(1), vals.ElementAt(2));
    public HashSet<JunctionBox>? Circuit { get; set; } = null;

    public double DistanceTo(JunctionBox box)
    {
        return Math.Sqrt(Math.Pow(box.Coords.x - Coords.x, 2) + Math.Pow(box.Coords.y - Coords.y, 2) + Math.Pow(box.Coords.z - Coords.z, 2));
    }
}

public record CircuitMapping
{
    public double Distance { get; set; } = 0.0;
    public JunctionBox Box { get; set; }
}

