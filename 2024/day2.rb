require "./elves"
require "pry"

input_elf = InputHelper.new
raw_input = input_elf.get_input(2)

levels = raw_input.split("\n").map { |ln| ln.split.map(&:to_i) }

def is_level_safe(level)
  direction = level[1] > level[0] 
  level.each_cons(2) do |x, y| 
    return false if (x == y) or (y > x != direction) or ((x - y).abs > 3)
  end

  return true
end

def safety_dampener(level)
  return true if is_level_safe(level)

  (0..(level.length - 1)).each do |i|
    dampened_level = level.dup
    dampened_level.delete_at(i)
    return true if is_level_safe(dampened_level)
  end

  return false
end

def calc_safety(all_levels, evaluator)
  return all_levels.inject(0) do |safety_val, level| 
    safety_val + (evaluator.call(level) ? 1 : 0)
  end
end

# Part 1
puts calc_safety(levels, method(:is_level_safe))

# Part 2
puts calc_safety(levels, method(:safety_dampener))