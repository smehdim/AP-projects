## Assignment-1
### Description
In this assignment, we wanted to code a program that creates a schedule for presentaion times of assignments. 
Projects get done in groups of three people. We want to schedule presentaion times in a way that ensures:
* there is not more than one presentaion per group.
* there is no pattern about who is going to be present the next assignment.
* and all students must present at least once.

It is guaranteed that [3k/a]+1<a<k where k is count of groups, a is count of assignments and s is count of presentations for each assignment

### Example 
in the first line of input we take k,a,s respectively and in next line we take id of each individual.
| Input  | Output |
| ------------- | ------------- |
| 5 5 4<br> S11 S12 S13<br>S21 S22 S23<br>S31 S32 S33<br>S41 S42 S43 <br>S51 S52 S53|S13 S22 S31 S53<br>S11 S23 S42 S53<br>S21 S33 S41 S51<br>S12 S23 S33 S52<br>S11 S32 S43 S51  |

