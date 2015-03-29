require_relative 'lexer'
require_relative 'parser'
require_relative 'reductor'
require_relative 'solver'

class Computor
  attr_accessor :exp

  def initialize(exp)
    @exp = exp
  end

  def run()
    l = Lexer.new()
    p = Parser.new()
    r = Reductor.new()
    s = Solver.new()

    result = s.solve(r.reduct(p.parse(l.lexe(exp))))

    puts result
  end
end
