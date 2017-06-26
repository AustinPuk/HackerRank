import math

class Calculator:
  def power (self, n, p):
    if n < 0 or p < 0:
      raise Exception("n and p should both be positive")
      return
    else:
      return int(math.pow(n, p))
      

myCalculator=Calculator()
T=int(raw_input())
for i in range(T):
    n,p = map(int, raw_input().split())
    try:
        ans=myCalculator.power(n,p)
        print ans
    except Exception,e:
        print e    
    