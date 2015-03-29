if __FILE__ == $0
  require_relative 'computor'

  if (defined? ARGV.first)
    c = Computor.new(ARGV.first)
    c.run()
  end
end
