###學號：
B02901001

###姓名：
鍾勝隆

###使用之程式語言：
< C++ >

###使用之編譯器：
g++ (GCC) 6.2.1 20160830

###檔案壓縮方式: 

     tar -cvf b02901001-p2.tar.gz b02901001-p2/

###各檔案說明：    
*   **b02901001-p1/maxPlanarSubset.cpp:** Main source code for finding the max planar subset of a circle
*   **b02901001-p1/maxPlanarSubset:** Executable binary file
*   **b02901001-p1/README.md:** Documentation for each file
*   **b02901001-p1/Makefile:** Makefile for compiling file easily

###編譯方式說明：
Under the directory **b02901001-p2** enter the command:

    make

Makefile would compile the source code with **g++** automatically

###執行、使用方式說明：
After compile is done, there will be an executable binary file, named **maxPlanarSubset**.
The command format of this binary file:

    ./maxPlanarSubset < input file name > < output file name >

For example, if you want to find the max planar subset of the input file, 500.in,
and save the result to the output file, 500.out. You need to use the this
command in the terminal:

    ./maxPlanarSubset 500.in 500.out
