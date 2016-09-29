1. 學號：B02901001
2. 姓名：鍾勝隆
3. 使用之程式語言：< C++ >
4. 使用之編譯器：< GNU g++ >
5. 檔案壓縮方式: <tar -cvf b02901001-p1.tar.gz b02901001-p1/>
6. 各檔案說明：
b02901001-p1/sort.cpp: Main source code for dealing with data by different sorting way
b02901001-p1/report.doc: Report for programming performance and analysis
b02901001-p1/README.md: Documentation for each file
b02901001-p1/sort: Executable binary file
b02901001-p1/Makefile: Makefile for compiling file easily
b02901001-p1/parser.cpp: For parsing data
b02901001-p1/parser.h:  For parsing data

7. 編譯方式說明：          
Under the directory b02901001-p1 enter the command:

make

Makefile would compile the source code with "g++" automatically

8. 執行、使用方式說明：
After compile is done, there will be an executable binary file, named "sort".
The command format of this binary file:

./sort <input file name> <which kind of sort> <output file name>

For example, if you want to use quicksort to sort the input file, case1.dat,
and save the result to the output file, case1-q.dat. You need to use the this
command in the terminal:

./sort case1.dat -quick case1-q.dat

There are FOUR different sorting method:
    
    -insert : Insertion sort
    -merge  : Merge sort
    -heap   : Heap sort
    -quick  : Quicksort

9. 執行結果說明（說明執行結果的觀看方法，及解釋各項數據等）：
