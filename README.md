# Assignment 2 - Shogi in C (with Linked List)

## **Compile**

```bash
gcc -g main.c rule.c data.c -o Chess
```
## **Run**

* Use -n -s <file_name.txt> for a new game and game saving.
* Use -l <file_name.txt> for loading a game
```bash
./Chess -n -s game1.txt
./Chess -l game0.txt
```
## **Game Method**

To play this the game. Player 1 will control the chess on the upper half of the chessboard, and Player 2 will control the lower half.

What you need to do is **TYPE IN THE X Y COORDINATE** on the chessboard to move the chess.  
```
- 輪到上方玩家 -
輸入目標的座標X與Y:
5 3
輸入下一步的座標X與Y:
5 4

- 輪到下方玩家 -
輸入目標的座標X與Y:
2 7
輸入下一步的座標X與Y:
2 6
```
Each chess has different moving rule, please check out **[here](https://shogi-classroom.blogspot.com/2012/09/blog-post.html)**.
### **Special Command**
When you are in the playing mode, you can type in **0 to regret the move**, type in **S or s to save the current game**, and type in **E or e to save and exit the game**.
* Regret
    ```bash
    上方玩家: 0:25
    下方玩家: 0:39

    ９ ８ ７ ６ ５ ４ ３ ２ １
    香 桂 銀 金 王 金 銀 桂 ． 一
    ． 飛 ． ． ． ． ． ． ． 二
    ． 步 步 ． 步 步 步 步 角 三
    步 ． ． 步 ． ． ． ． 香 四
    ． ． ． ． 角 ． ． ． 步 五
    ． 步 步 ． ． ． 步 步 步 六
    步 ． ． 步 步 步 ． ． ． 七
    ． ． ． ． ． ． ． 飛 ． 八
    香 桂 銀 金 玉 金 銀 桂 香 九

    - 輪到上方玩家 -
    輸入目標的座標X與Y:
    > 0

    上方玩家: 0:57
    下方玩家: 0:39

    ９ ８ ７ ６ ５ ４ ３ ２ １
    香 桂 銀 金 王 金 銀 桂 ． 一
    ． 飛 ． ． ． ． ． ． ． 二
    ． 步 步 ． 步 步 步 步 角 三
    步 ． ． 步 ． ． ． ． 香 四
    ． ． ． ． ． ． ． ． 步 五
    ． 步 步 ． ． ． 步 步 步 六
    步 ． ． 步 步 步 ． ． ． 七
    ． 角 ． ． ． ． ． 飛 ． 八
    香 桂 銀 金 玉 金 銀 桂 香 九

    - 輪到下方玩家 -
    輸入目標的座標X與Y:
    > 
    ```
* Save
    ```bash
    上方玩家: 0:01
    下方玩家: 0:04

    ９ ８ ７ ６ ５ ４ ３ ２ １
    香 桂 銀 金 王 金 銀 桂 香 一
    ． 飛 ． ． ． ． ． 角 ． 二
    步 步 步 步 步 步 步 步 ． 三
    ． ． ． ． ． ． ． ． 步 四
    ． ． ． ． ． ． ． ． ． 五
    ． ． ． ． ． ． ． ． 步 六
    步 步 步 步 步 步 步 步 ． 七
    ． 角 ． ． ． ． ． 飛 ． 八
    香 桂 銀 金 玉 金 銀 桂 香 九

    - 輪到上方玩家 -
    輸入目標的座標X與Y:
    > s  
    Game Save!
    ```
* Exit
    ```bash
    上方玩家: 2:08
    下方玩家: 0:04

    ９ ８ ７ ６ ５ ４ ３ ２ １
    香 桂 銀 金 王 金 銀 桂 香 一
    ． 飛 ． ． ． ． ． 角 ． 二
    步 步 步 步 步 步 ． 步 ． 三
    ． ． ． ． ． ． 步 ． 步 四
    ． ． ． ． ． ． ． ． ． 五
    ． ． ． ． ． ． ． ． 步 六
    步 步 步 步 步 步 步 步 ． 七
    ． 角 ． ． ． ． ． 飛 ． 八
    香 桂 銀 金 玉 金 銀 桂 香 九

    - 輪到下方玩家 -
    輸入目標的座標X與Y:
    > e
    Save and exit the game!
    ```
### **How To Win**
As either side eat their opponent's **王** chess. They will be the winner!

## **Game Mode**
1. **Playing Mode ( -n -s )**
2. **Game Reading Mode ( -l )**  
    - After loading a game, you can type in 4 different type of command:  
        (1) **F**: To make the game *move forward*.  
        (2) **B**: To make the game *move backward*.  
        (3) **P**: To *entering the playing mode*.  
        (4) **E**: *Exit* the read mode.

## **Current Bugs and Future**
1. After loading a game and type in P to enter the playing mode. The move making is fine, but when saving the game, the game CAN rewrite the data to the right position in the saving file, but it CANNOT erase the rest of the data that is originally in the file.
     - **Current Thought** *(Solved)*:   
        Detect the "count" to see if it is smaller than "maxcount", if it does, then fprintf "-1" into the file. When loading the file, if it detect "-1", then the function will break to end the loading process and update the new "maxcount".
2. **Functions not test yet**:  
(1) Some functions after dropping the chess.
3. **Lack function**: Timer(Libev), 升變-強制升變
## **Reference**

(1) [Shogi Rule](https://shogi-classroom.blogspot.com/2012/09/blog-post.html)  
(2) getopt( ) function :  
　　- [getopt的用法與optarg](https://www.796t.com/content/1550615426.html)  
　　- [Example of Parsing Arguments with getopt](https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html)  