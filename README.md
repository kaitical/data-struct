##ds/vector+complex中含四个文件：1、vector.h 2、vector_fun.h 3、complex.h 4、main.cpp
##1、
在vector.h中主要编写了Vector类，以书p30的代码为范本声明了关于vector对象的构造、排序、置乱、唯一化、插入等函数。
##2、
而在vector_fun.h文件中主要是对vector.h的函数的具体实现。
##3、
在complex.h中编写了Complex类定义了成员实部和虚部，重载了=、！=、==、>、<等复数的运算法则并用getModulus获取复数的模。
##4、
在main函数中引用了vector.h和complex.h，并随机生成了一个复数向量组Vector v(10)，以v了测试无序向量的置乱、查找（实部和虚部均相同）、插入、删除和唯一化的操作，这些操作都是利用vector.h的函数所实现的（这也是第一部分）。 而第二部分包括在main.cpp中编写的对于复数向量组Vector的气泡排序：bubble_sort(Vector& v)（从大到小）bubble_sortdif(Vector& v)(从小到大)和归并排序： merge_sort(Vector& v, int l, int r)（从大到小） merge_sortdif(Vector& v, int l, int r)（从小到大）。我先随机生成了含4000个复数的Vector v1，并让v2=v1，然后依次对它们进行乱序、顺序以及逆序的排序测试并cout了它们的所用时间以比较。 在第三部分我先定义了一个查找模在[m1,m2)之间并按序存于一个子向量中作为返回值的函数Vector findRange(const Vector& v, double m1, double m2)，利用它对新生成并排序过的 Vector v3(10)来操作res = findRange(v3, 0, 4)返回了一个模在[0,4)有序子向量res。
##PS:发现下载完代码后放在devc++中部分文件（main.cpp）的中文注释会变成乱码，而在Visual Studio上没有这个问题。第二版： From Xie 2023/3/30
