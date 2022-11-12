# College Allotment using vEB Trees
Analysis and Implementation of van Emde Boas Trees for our course CS201: Data Structures and Algorithms

During this project, we worked with the data structure van Emde Boas (vEB) Trees. We chose to implement the JOSAA admission procedure with sample data.

vEB Tree: vEB Tree is a priority queue. Compared to other priority queues, it is much more optimised (in terms of time) for large amounts of data. Size of universe is static O(u). Any dynamic set operation can be carried out in O(lg lg u) time.

Data: The sample data we used to test our implementation was random data we generated. We took a total of xxx random students. Their name, roll number, marks scored, and college/stream preference was stored. The number of seats available in each college/stream was also stored. Using this data, the students were allocated seats following the same procedure as that of JOSAA. 

JOSAA: Stands for Joint Seat Allocation Authority. After students give the competitive examinations, their names, roll numbers and marks are stored. They are then asked to give their preferences of college/streams. Based on marks (rank), they are allocated a seat in their highest preferred college/stream- with the constraint of number of seats available in the college/stream. In the case where students have the same marks, the student with the lower roll number is assigned a better rank.

Sample Data Template: https://docs.google.com/spreadsheets/d/1WxYvlta2jwyDuRmctZeTJt4TIgS5obZxTd5qI3PE-ww/edit?usp=sharing

Data Instructions: Using the template given above, create your own .csv file containing student & college data.

1. The number of students (n) must be a power of 2.
2. The roll numbers of students ranges from 1 to n-1.
3. Do not delete or edit the data of the sample student.
4. Marks and Roll Numbers do not have to be in order.
5. College codes do not have to be in order.
6. After exporting a .csv file, convert the file to a .txt file.
7. Change the name of the file in the code according to your file's name.
8. The program will output "Successful Execution." after execution.


FINAL PROJECT REPORT:
[report_pdf_Group_14.pdf](https://github.com/n1ti/cs201project/files/9994674/report_pdf_Group_14.pdf)
