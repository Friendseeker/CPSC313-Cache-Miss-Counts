# CPSC313-Cache-Miss-Counts

In UBC CPSC 313, there is a certain type of question, that is simple to do, but annoying to do it correctly.

<img width="796" alt="Screen Shot 2022-03-10 at 5 45 38 PM" src="https://user-images.githubusercontent.com/66892505/157786054-78a56cfc-e621-4b18-95b9-b40dcddad4e8.png">

Such problem is higher mechanical & repetitive. Therefore, I built a script, that automates the process of solving such problem.

<img width="364" alt="Screen Shot 2022-03-10 at 5 47 08 PM" src="https://user-images.githubusercontent.com/66892505/157786193-07ac55e4-d5f4-40d9-9a80-bef46ee929ee.png">

By simply opening the script and sending in your query. It automatically counts number of hits and misses.

## How to use

- Clone the repository
- Open the repository in any C++ IDE
- Click the run button
- Type in the query in the following form:
    - \[Cache type\] \[Access Sequence\]
- Press Enter

### Example query:

Input:
```
LRU B,E,B,B,E,C,D,E,A,A,A,D,B,G,C,D,C,E,C,D
```
Output:
```
Number of hits: 11
Number of misses: 9
```

## Types of cache replacement policies supported

- LRU
- MRU
- FIFO
- LFU
