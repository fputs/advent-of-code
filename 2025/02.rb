def valid(str, p2)
  (1..str.size / 2).each do |i|
    sub = str[0, i]
    return false if str[i..] == sub

    if p2 && str.size > 2
      chunks = str[i..].chars.each_slice(sub.size).map(&:join)
      puts chunks
    end
  end
  true
end

input = File.read('input/test').split(',')
p1 = 0
p2 = 0

input.each do |line|
  sp = line.split('-')
  a = sp[0].to_i
  b = sp[1].to_i

  (a..b).each do |i|
    p1 += i unless valid(i.to_s, false)
    p2 += i unless valid(i.to_s, true)
  end
end

puts p1
puts p2
