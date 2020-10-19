# Question 1 | Parallel Implementation of Mergesort

```
S. Bhuvanesh
2018113002
```

The details of the run are given here 


| Number of inputs | Normal Mergesort | Multiprocess Mergesort | Multithread Mergesort |
| ---------------- | ---------------- | ---------------------- | --------------------- |
| 10               | 0.000058         | 0.001147               | 0.001007              |
| 100              | 0.000109         | 0.005905               | 0.022951              |
| 1000             | 0.000648         | 0.109993               | 0.140048              |
| 10000            | 0.004643         | 1.051259               | 0.488984              |

This is because, regardless of the implementation, the order of the running time remains the same. ie. $O(n * log(n))$.
I believe  that the parallel implementations take more time because of the overhead of creating the threads and processes which gives us an addional constant factor in the time complexity. 

---

## Logic :

- For n <= 5, do selection sort.
- In general create another thread/process for the left part of the array and the right part of the array.
  - Call the merge sort function recursively.


---
The End