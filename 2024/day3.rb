require "./elves"

input_elf = InputHelper.new
raw_input = input_elf.get_input(3) 

def parse_mul(string_slice)
    string_slice
        .scan(/mul\({1}\d+,\d+\){1}/)
        .map{ |op| op
                    .match(/(\d+),(\d+)/)
                    .captures
                    .map(&:to_i)
                    .inject(1, :*) }
                    .sum
end

# Part 1
p parse_mul(raw_input)

# Part 2
enabled_i = 0
disabled_i = 0
total_result = 0
loop do
    disabled_i = raw_input.index(/don't\(\)/, enabled_i)    
    total_result += parse_mul(raw_input[enabled_i..disabled_i])    
    break if disabled_i.nil?
    
    enabled_i = raw_input.index(/do(\(\))/, disabled_i)
    break if enabled_i.nil?
end


p total_result