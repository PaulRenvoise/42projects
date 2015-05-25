require_relative 'utils'

class Computor
  NAMES = [
        "constant",
        "linear",
        "quadratic",
        "cubic",
        "quartic",
        "quintic",
        "sextic",
        "septic",
        "octic",
        "nonic",
        "decic"
  ]

  def run(exp)
    self.solve(self.reduct(self.tokenize(self.analyze(exp))))
  end

  def analyze(exp)
    if (exp[/\^-\d+/] || exp[/\^.?\d+\.\d*/])
      abort("Powers must be positives integers, aborting.")
    end

    exp
  end

  def tokenize(exp)
    left = true
    hash = Hash.new(0)

    for side in exp.split('=')
      side.scan(/[\+\-]?\s*\d+\.?\d*\s+\*\s+X\^?\d+|\s+\=|[\+\-]?\s*\d+/) do |token|
        token.strip!
        if (!left)
          if (token[0] == '+')
            token[0] = '-'
          elsif (token[0] == '-')
            token[0] = ''
          else
            token.prepend('-')
          end
        end
        token.delete!(' ')
        if (hash[token[/\d+$/].to_i])
          hash[token[/\d+$/].to_i] += token[/[^\^]?[\+\-]?\d+\.?\d*/].to_f
        else
          hash[token[/\d+$/].to_i] = token[/[^\^]?[\+\-]?\d+\.?\d*/].to_f
        end
      end
      left = false
    end

    hash
  end

  def reduct(hash)
    exp = String.new()
    deg = 0
    first = true

    hash.keys.sort.each_with_index do |key, index|
      if (hash[key] != 0 && key > deg)
        deg = key
      end

      if (hash[key] != 0)
        if (hash[key] < 0)
          if (!first)
            exp.concat("- #{hash[key].abs} * X^#{key} ")
          else
            exp.concat("-#{hash[key].abs} * X^#{key} ")
          end
        elsif (hash[key] > 0)
          if (!first)
            exp.concat("+ ")
          end
          exp.concat("#{hash[key]} * X^#{key} ")
        end
        first = false
      end

      if (index == hash.length - 1)
        exp.concat("= 0")
      end
    end

    puts "Reduced form: #{exp}"
    puts "Polynominal degree: #{deg} (#{NAMES[deg]})"

    if (deg > 2 && hash[deg] != 0)
      abort ("Polynominal degree is strictly greater than 2, aborting.")
    end

    [hash, deg]
  end

  def solve(array)
    hash, deg = array

    if (deg == 0)
      puts (hash[0] == 0) ? "Every number is a solution." : "No solution."
      return
    elsif (deg == 1)
      puts "One solution:"
      puts -(hash[0] / hash[1])
    else
      delta = hash[1] ** 2 - 4 * hash[2] * hash[0]

      if (delta > 0)
        puts "Delta is strictly positive, two solutions:"
        puts ((-hash[1]) + Utils.sqrt(delta)) / (2 * hash[2])
        puts ((-hash[1]) - Utils.sqrt(delta)) / (2 * hash[2])
      elsif (delta < 0)
        puts "Delta is strictly negative, two solutions:"
        puts "#{-hash[1] / (2 * hash[2])} + #{Utils.sqrt(-delta) / (2 * hash[2])}i"
        puts "#{-hash[1] / (2 * hash[2])} - #{Utils.sqrt(-delta) / (2 * hash[2])}i"
      else
          puts "Delta equals zero, one solution:"
          puts -hash[1] / (2 * hash[2])
      end
    end

  end
end
