## Assignment 2

### Description of assignmnet
This assignment consists of three different parts and must be done via recursive methods.
#### **part 1**
##### description
in this part we must find index of the biggest element of list using recursion. it is guranteed that till reaching the biggest element ,list is strictly increasing and after that it is strictly decreasing.inputs of program are count of elements and elements and we must return index of the biggest number in list.
##### example
| Input  | Output |
| ------------- | ------------- |
| 5 <br>1 4 5 7 2|4 | 
| 6 <br>5 20 19 17 13 1 |2 | 
| 2 <br>1 2|2 | 
#### **part 2**
##### description
in the second part we must create all possible numbers consists of `n` digits where difference of each two consecutive digit must be `k`
##### example
| Input  | Output |
| ------------- | ------------- |
| 3   7|181<br>292<br>707<br>818<br>929 |


as we see in output the difference between each two consecutive digit is 7 and each number consists of 3 digit
#### **part 3**
##### description
in third part we are given a grid and we can jump between two adjacent cells of this grid only if the difference of height between two adjacent cell is exactly 1.
we must determine a possible path with lenght = 3 and longest path possible .firtst line of input gives us the `n` and `m` which are number of rows and columns in grid and following lines are elements of grid.
##### example
first part
| Input  | Output |
| ------------- | ------------- |
| 2  3<br>1 2<br>3 4<br>5 6<br>|-1 |
| 3  3<br>1 2 3<br>3 3 5<br>1 4 5<br>|2 3 4 |

second part
| Input  | Output |
| ------------- | ------------- |
| 3  3<br>1 2 7<br>3 3 6<br>1 4 2<br>|1 2 3 4 5 6 7|
| 5  5<br>7 5 2 3 1<br>3 4 1 4 4<br>1 5 6 7 8<br>3 4 5 8 9<br>3 2 2 7 6|5 4 5 4 5 6 7 8 9 8 7 6|

