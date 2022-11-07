# cs201project
Analysis and Implementation of van Emde Boas Trees for our course CS201: Data Structures and Algorithms

During this project, we worked with the data structure van Emde Boas (vEB) Trees. We chose to implement the JOSAA admission procedure with sample data.

vEB Tree: vEB Tree is a priority queue. Compared to other priority queues, it is much more optimised (in terms of time) for large amounts of data. Size of universe is static (u). Any dynamic set operation can be carried out in O(lg lg u) time.

Data: The sample data we used to test our implementation was random data we generated. We took a total of xxx random students. Their name, roll number, marks scored, and college/stream preference was stored. The number of seats available in each college/stream was also stored. Using this data, the students were allocated seats following the same procedure as that of JOSAA. 
