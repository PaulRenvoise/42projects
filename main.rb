if __FILE__ == $0
  require_relative 'computor'
  if (!ARGV.first.nil? && !ARGV.first.strip.empty?)
    c = Computor.new()
    c.run(ARGV.first)
  else
    abort("Please provide a correctly formated polynominal as first argument.")
  end
end
