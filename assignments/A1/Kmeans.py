from sklearn.cluster import KMeans
import numpy as np
def conv(f):
    return float(f)
file1 = np.loadtxt("data1.data",delimiter= ',', usecols=(0,1,2,3), converters={0: conv, 1:conv, 2:conv, 3:conv}, skiprows=0)
X = np.zeros(shape=(150,4), dtype=float)
index =0
for i in file1:
    X[index] = i
    index = index+1
    
# print(X)
kmeans = KMeans(n_clusters=6, random_state=1,init='k-means++', max_iter=1000000, tol=0.00000001).fit(X)
kmeans.predict([[0, 0, 0, 0], [12, 3, 3, 4]])
print(kmeans.labels_,  kmeans.cluster_centers_)
num0 = 0
num1 = 0
num2 = 0
for i in kmeans.labels_:
    if i==0:
        num0=num0+1
    elif i==1:
        num1=num1+1
    elif i==2:
        num2=num2+1                                                                                                           

print(num0, num1, num2)
