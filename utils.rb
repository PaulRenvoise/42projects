class Utils
  def self.sqrt(n)
    n = n.abs
    res = 1.0;
    for i in 0..n do
      res = 0.5 * (res + n / res)
    end
    res
  end
end
