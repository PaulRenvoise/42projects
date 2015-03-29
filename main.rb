if __FILE__ == $0
  require_relative 'computor'

  if (!ARGV.first.nil?)
    c = Computor.new(ARGV.first)
    c.run()
  end
end
