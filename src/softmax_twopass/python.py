import math

Ln2Hi = 6.93147180369123816490e-01
Ln2Lo = 1.90821492927058770002e-10

def round(x):
    """
    Round to nearest int
    """
    return int(x + 0.5)

def exp(x):
    C0 = 1.0
    C1 = -0.99999970197677612304687500000000
    C2 = 0.49999150633811950683593750000000
    C3 = 0.16667652130126953125000000000000
    C4 = 0.04189782217144966125488281250000
    C5 = 0.00828929059207439422607421875000
    n = round(x / math.log2(2.)) 
    t = x - n * math.log2(2.)
    p = 1 + t*(C1 + t*(C2 + t*(C3 + t*(C4 + t*C5))))
    return p

val = -0.2
print(exp(val), " ", math.exp(val))
