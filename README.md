# KevinSort

KevinSort is a sorting algorithm that I designed to be as slow as possible. It is a combination of 
[SleepSort](https://www.geeksforgeeks.org/sleep-sort-king-laziness-sorting-sleeping/) and 
[BogoSort](https://en.wikipedia.org/wiki/Bogosort). 

The algorithm is:
1. For each element in the input collection, spawn a new thread. Sleep that thread for a random time interval. 
2. After each thread wakes up, insert the element into a result collection.
3. After all threads have completed, check to see if the collection is sorted. If it is, return the sorted collection.
If not, repeat starting from step 1.
