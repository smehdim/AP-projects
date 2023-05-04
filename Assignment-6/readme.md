## Assignment 6
In this project we aim to build a for asking permits.the purpose of this assignment is to practice OOP concepts like polymorphism and inheritance.
### Description
As said in this project we want to build a system to give permits. in order to give permits user should prepare all needed forms. when a user confirms a form it will be processed immediately to make the possible permits.due to this matter i used observer and the composite design patterns. two csv files will be provided for program to run properly.first one is organizitations which will provide the necessary informations about each permit such that which organization give each permit and what is required for a permit to be issued.the other one is forms which as it sounds gives information about what is in the forms. as said forms only need confirmation of the user to be issued and there is no dependency like there was for permits. 
### I/O example
there is a sample file beside the codes and the output is:

```
Name: pWork  
This permit consists of:{
  #1
  Name: pBehdasht 
  This permit consists of: {
    #1
    Name: fGoodInfo
    Content: expiration date: 2020/05/11
  }
  Signature: name2
  #2
  Name: fSalahiat
  Content:
  name: Changiz Mostofi DOB: 2000/05/11
 }
 Signature: Li Wei
 ```
