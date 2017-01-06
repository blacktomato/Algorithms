###學號：
B02901001

###姓名：
鍾勝隆

###使用之程式語言：
< C++ >

###使用之編譯器：
g++ (GCC) 6.2.1 20160830

###檔案壓縮方式: 

     tar -cvf b02901001-p3.tar.gz b02901001-p3/

###各檔案說明：    
*   **b02901001-p3/router.cpp:** Main source code for global routing problem 
*   **b02901001-p3/router:** Executable binary file
*   **b02901001-p3/README.md:** Documentation for each file
*   **b02901001-p3/Makefile:** Makefile for compiling file easily

###編譯方式說明：
Under the directory **b02901001-p3** enter the command:

    make

Makefile would compile the source code with **g++** automatically

###執行、使用方式說明：
After compile is done, there will be an executable binary file, named **router**.
The command format of this binary file:

    ./router < input file name > < output file name >

For example, if you want to solve the global routing problem of the input file, gr60x60.in,
and save the result to the output file, gr60x60.out. You need to use the this
command in the terminal:

    ./router gr60x60.in gr60x60.out
