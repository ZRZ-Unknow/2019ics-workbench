import random
import os

with open("./data.txt","w") as f:
    for i in range(1000000):
        a=random.randint(1,2**63-1)
        b=random.randint(1,2**63-1)
        m=random.randint(1,2**63-1)
        res=a*b%m
        f.writelines(str(a)+' '+str(b)+' '+str(c)+' '+str(res)+'\n')
f.close()

with open("./data2.txt","w") as f:
    for i in range(1000000):
        a=random.randint(1,2**31-1)
        b=random.randint(1,2**31-1)
        m=random.randint(1,2**31-1)
        res=a*b%m
        f.writelines(str(a)+' '+str(b)+' '+str(c)+' '+str(res)+'\n')
f.close(