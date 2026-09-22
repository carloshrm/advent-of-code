require "./elves"

input_elf = InputHelper.new
raw_input = input_elf.get_input(1)

# Part 1
total_distance = 0
left_nums, right_nums = raw_input.split("\n").map { |line| line.split.map(&:to_i) }.transpose.each(&:sort!)
left_nums.each_index do |i|
    total_distance += (left_nums[i] - right_nums[i]).abs
end
puts total_distance

# Part 2
similarity_map = {}
similarity_score = 0
left_nums.each do |n|
    unless similarity_map.has_value?(n)
        occurences = right_nums.select { |rn| rn == n }.length
        similarity_map[n] = occurences
    end

    similarity_score += (similarity_map[n] * n)
end
puts similarity_score