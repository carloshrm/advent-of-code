namespace aoc2025;

internal class Program
{
    private static void Main(string[] args)
    {
        var input = File.ReadAllLines(@"./input.txt");

        var junctionBoxes = input.Select(ln => new JunctionBox(ln.Split(',', StringSplitOptions.RemoveEmptyEntries).Select(int.Parse))).ToList();

        var distanceMap = new List<CircuitMapping>();
        for (int i = 0; i < junctionBoxes.Count; i++)
        {
            for (int j = i + 1; j < junctionBoxes.Count; j++)
                distanceMap.Add(new() { Base = junctionBoxes[i], Target = junctionBoxes[j] });
        }

        var sortedDistances = distanceMap.OrderBy((entry) => entry.Base.DistanceTo(entry.Target));

        int id = 0;
        bool stop = false;
        var circuitMap = new Dictionary<int, HashSet<JunctionBox>>();
        while (!stop)
        {
            foreach (var pair in sortedDistances)
            {
                (JunctionBox baseBox, JunctionBox targetBox) = pair;

                if (baseBox.CircuitId == -1)
                {
                    if (targetBox.CircuitId == -1)
                    {
                        int newCircuit = id++;
                        circuitMap.Add(newCircuit, [baseBox, targetBox]);
                        baseBox.CircuitId = newCircuit;
                        targetBox.CircuitId = newCircuit;
                    }
                    else
                    {
                        baseBox.CircuitId = targetBox.CircuitId;
                        circuitMap[targetBox.CircuitId].Add(baseBox);
                    }
                }
                else
                {
                    if (targetBox.CircuitId == -1)
                    {
                        circuitMap[baseBox.CircuitId].Add(targetBox);
                        targetBox.CircuitId = baseBox.CircuitId;
                    }
                    else
                    {
                        if (!circuitMap[targetBox.CircuitId].Contains(baseBox))
                        {
                            var mergeTargetId = baseBox.CircuitId;
                            foreach (var box in circuitMap[mergeTargetId])
                            {
                                circuitMap[targetBox.CircuitId].Add(box);
                                box.CircuitId = targetBox.CircuitId;
                            }
                            circuitMap.Remove(mergeTargetId);
                        }
                    }
                }

                if (circuitMap.Any(entry => entry.Value.Count == junctionBoxes.Count))
                {
                    Console.WriteLine(baseBox.Coords.x * targetBox.Coords.x);
                    stop = true;
                    break;
                }
            }
        }

        var result = circuitMap
            .Select(entry => entry.Value.Count)
            .OrderDescending()
            .Take(3)
            .Aggregate(1l, (a, b) => a * b);

        Console.WriteLine(result);
    }
}

public class JunctionBox(IEnumerable<int> vals)
{
    public (long x, long y, long z) Coords { get; set; } = (vals.ElementAt(0), vals.ElementAt(1), vals.ElementAt(2));
    public int CircuitId { get; set; } = -1;

    public long DistanceTo(JunctionBox box)
    {
        long x = Coords.x - box.Coords.x;
        long y = Coords.y - box.Coords.y;
        long z = Coords.z - box.Coords.z;

        return (x * x) + (y * y) + (z * z);
    }
}

public class CircuitMapping
{
    public required JunctionBox Base { get; set; }
    public required JunctionBox Target { get; set; }

    public void Deconstruct(out JunctionBox baseBox, out JunctionBox targetBox)
    {
        baseBox = Base;
        targetBox = Target;
    }
}
