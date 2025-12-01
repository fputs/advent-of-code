input = File.readlines('input/01')
pos = 50
p1 = 0
p2 = 0

input.each do |line|
  dir = line[0]
  n = line[1..].to_i
  (1..n).each do
    if dir == 'R'
      pos = (pos - 1 + 100) % 100
    else
      pos = (pos + 1) % 100
    end
    if pos.zero?
      p2 += 1
    end
  end
  if pos.zero?
    p1 += 1
  end
end

puts p1
puts p2
