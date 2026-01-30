# 📘 Day 02 Lecture Practices

## 💻 Pass by Reference Coding Practice

### 🧩 Part B-1.1: Add a method *declaration*
1. Open `Day2.h`
2. Add a declaration for a method called GetLights to the Day2.h file
   - It should not return anything.
   - It should have 1 vector parameter that is passed by reference.

### 🧩 Part B-1.2: Add a method *definition*

1. Open the `Day2.cpp` file
2. Add the GetLights definition to the Day2.cpp file
   - fill the vector with Target objects.
   - There should be 48 rows with 48 Target objects per row.
   - Give each target a random color.

### 🧩 Part B-1.3: call the method
1. Open the `Day2.cpp` file
2. In the PartB_1() method, call the GetLights method passing the “lights” variable to it.


---

## 💻 Const Parameters Coding Practice

### 🧩 Part B-2.1: create a *declaration*
1. Open `Day2.h`
2. Add a method declaration for a method called DrawLights.
   - It should not return anything.
   - It should have 2 parameters: a vector of Targets parameter and a Map parameter.

### 🧩 Part B-2.2: create a *definition*
1. Open `Day2.cpp`
2. Add a method definition for DrawLights.
   - In the method definition, call DrawCell for each Target. (see PartB_1() for an example).

### 🧩 Part B-2.3: call the method
1. Open `Day2.cpp`.
2. In the PartB_2() method, call the DrawLights method after the call to engine.ClearScreen.


> NOTE: you’ll need to call your GetLights method in the correct place (look for the comments in the code where you should call it  in the PartB_2() method)

---

## 💻 Const Methods Coding Practice
1. Open the `Player.h` and `Player.cpp` files.
3. Evaluate the methods and add const to the ones that do not modify the fields of the Player.


---

## 💻 Erasing in a Loop Coding Practice

### 🧩 Part B-3.1: create a declaration
1. Open `Day2.h`
2. Add a method declaration for a method called EraseLights.
   - It should not return anything.
   - It should have 1 parameters vector of Targets parameter
   
### 🧩 Part B-3.2: create a definition
1. Open `Day2.cpp`
2. Add a method definition for EraseLights.
   - Inside the method, erase any light from the vector whose red value is less than 100.

### 🧩 Part B-3.3: call a method
1. Open `Day2.cpp`
2. Call your EraseLights after the call to GetLights.

> NOTE: you’ll need to call your GetLights method and DrawLights method in the correct places (look for the comments in the code where you should call them in the PartB_3() method)


![Footer Separator](../../Shared/Images/separator01.png)

## 🔭 Markdown Viewer

How to view the markdown files in a browser...
- [Markdown Viewer](../../Shared/0_Setup.md)

---

## 🧠 Lecture Practices

Here are the lecture Practices...
- [Day 1](./Day01.md)
- [Day 2](./Day02.md)
- [Day 3](./Day03.md)

---

## 🔍 Lecture Quizzes

Here are the lecture quizzes...
- [Day 1](https://forms.office.com/r/CSJQvCM0fD)
- [Day 2](https://forms.office.com/r/SmyXe3ufa3)
- [Day 3](https://forms.office.com/r/fcPX1HHfRD)

---

## ⚙️ Weekly Topics

Here are the topics for the week...
- [Calling Methods](./1_CallingMethods.md)
- [Calling Methods 2](./2_CallingMethods2.md)
- [Creating Methods](./3_CreatingMethods.md)
- [Iterators](./4_Iterators.md)
- [Vectors](./5_Vectors.md)
- [References](./6_References.md)
- [Const](./7_Const.md)
- [Erasing in a Loop](./8_ErasingInALoop.md)
- [Default Parameters](./9_DefaultParameters.md)