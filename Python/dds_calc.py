

OFFSET = 0b001000110000
AKKU =   0b000000000000

for i in range(50):
    AKKU = (AKKU+OFFSET)%0b1000000000000
    AKKUSTR = bin(AKKU)
    AKKUSTR = AKKUSTR[2:]
    for j in range(12-len(AKKUSTR)):
        AKKUSTR = '0'+AKKUSTR
    print (AKKUSTR,end="")
    print ('\t\t',end="")
    POINTER = AKKU//0b100000000
    print (POINTER,end="")
    print ('\t\t',end="")
    print (POINTER+1)