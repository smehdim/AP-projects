## Assignment 6: Permit Request System

### Overview
In this project, we aim to build a system for requesting permits. The purpose of this assignment is to practice Object-Oriented Programming (OOP) concepts such as polymorphism and inheritance.

### Description
This project involves building a system for issuing permits. To request a permit, users must prepare and submit all required forms. Once a user confirms a form, it is processed immediately to issue the necessary permits. To achieve this functionality, we have implemented the Observer and Composite design patterns.

Two CSV files are required for the program to run properly. The first file, `organizations.csv`, provides information about each permit, including which organization issues the permit and what requirements must be met for the permit to be issued. The second file, `forms.csv`, provides information about the forms that must be submitted.

Forms only require user confirmation to be issued and do not have any dependencies like permits do.

### Input/Output Example
A sample input file is provided with the code. Here is an example of the output:
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
