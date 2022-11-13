# Bankers_algorithm_in_C
本代码来自作业题的作答  
题目要求：  

可用资源向量Available,这是一个一维数组Available[j],j=1,…m，表示第j种资源的可用数量，其中m为资源的种类个数  
最大资源需求矩阵Max,这是一个n*m的二维数组，其中n为进程个数。单元Max[i,j]存储的数值表示第i个进程最多需要多少单位的第j种资源  
分配矩阵Allocation，这是一个n*m的二维数组。单元Allocation[i,j]存储的是已经分配给第i个进程的第j种资源的数量  
需求矩阵Need，这也是一个n*m的矩阵，单元Need[i,j]存储的数值表示进程i还需要多少个单位的第j种资源才能运行完成退出。  
假设系统中有n=5个进程和m=3种资源。这m种资源每一种资源的最大可用数量Available[i],i=1,…,m，用随机数生成，取值范围为[1,10]。  

每个进程i对资源j的最大需求Max[i,j],i=1,…,n,j=1,…m，也用随机数生成，其取值范围为从1到Available[j]。  

初始分配矩阵Allocation[i,j]也用随机数生成，其中，有50%的概率Allocation[i,j]取值为0，有50%的概率Allocation[i,j]随机从[1,Max[i,j]]中取值。  

如果在给第i个进程生成初始分配矩阵Allocation时，发现任何一种资源j的最大可用数量已经分配光了，那么从第i+1个进程开始所有的进程都分配不到该资源j，也就是说Allocation[k,j]=0,k=i+1,…,n。  
