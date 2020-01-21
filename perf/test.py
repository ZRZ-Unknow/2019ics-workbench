import matplotlib.pyplot as plt
import numpy as np
import sys
from scipy.stats import kstest
func_mul=['multimod_p1','multimod_p2','multimod_p3']
attr=['norm','uniform','expon']

f=open("./data.txt","r")
filename=f.readline().strip()
print('func is '+filename)
data=[]
for line in f.readlines():
    for d in line.split():
        data.append(float(d))
data=np.array(data)
index=np.array(range(len(data)))
plt.ylim(min(data),max(data))
plt.plot(index,data)
plt.xlabel("index")
plt.ylabel("run time(ms)")
plt.title("run time of "+filename)
plt.show()

dom=np.zeros(50)
inter=float(max(data))/50
for i in range(len(data)):
    n=int(float(data[i])/inter)-1
    dom[n]=dom[n]+1
plt.bar(range(50),dom)
plt.xlabel("index")
plt.ylabel("count")
plt.title("run time count of "+filename)
plt.show()

result=[0,0]
str=""
for i in range(len(attr)):
    tmp=kstest(dom,attr[i])
    if(i==0):
        result=tmp
        str=attr[i]
        continue
    if(result[1]<tmp[1]):
        result=tmp
        str=attr[i]
print("平均数是",np.mean(data))
print("标准差是",np.std(data))
print("分布检验结果为"+str)
print(result)


if(filename in func_mul):
    a=[]
    b=[]
    m=[]
    fp=open("./multimod_num.txt","r")
    for line in fp.readlines():
        temp=line.split()
        a.append(int(temp[0]))
        b.append(int(temp[1]))
        m.append(int(temp[2]))
    plt.ylim(min(data),max(data))
    plt.scatter(a,data,label="a")
    plt.scatter(b,data,label="b")
    plt.scatter(m,data,label="m")
    plt.xlabel("number size")
    plt.ylabel("run time(ms)")
    plt.legend(loc="upper left")
    plt.title("number size and run time of "+filename)
    plt.show()
    
    num_a=[]
    num_b=[]
    num_m=[]
    for i in range(len(a)):
        num_a.append(bin(a[i]).count('1'))
        num_b.append(bin(b[i]).count('1'))
        num_m.append(bin(m[i]).count('1'))
    plt.ylim(min(data),max(data))
    plt.scatter(num_a,data,label="a")
    plt.scatter(num_b,data,label="b")
    plt.scatter(num_m,data,label="m")
    plt.xlabel("number of binary 1")
    plt.ylabel("run time(ms)")
    plt.legend(loc="upper left")
    plt.title("num of binary 1 and run time of "+filename)
    plt.show()




