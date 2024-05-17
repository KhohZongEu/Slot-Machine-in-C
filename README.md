# SlotMachine in C
### A simple project to learn to code in C
This project was inspired by the javascript version by [Tech with Tim](https://www.youtube.com/watch?v=E3XxeE7NF30)

Note: Gambling is bad, this project is only for the purpose of learning to code and does not promote gambling in any capacity.

## How it works
1. You need to input the amount you want to deposit
2. Input the number of lines you want to bet on (The number starts from the top of the bar)
3. Input the amount you want to bet on each line
An output like this will be created:
``` 
Reels: 
B | D | C
D | B | B
A | A | A
```
4. You will then receive "money" based on the type of letter that is in a row and the amount you bet

### How the reels work
Each reel/column contains 20 letters in total. However, only 3 letters are displayed and used to determine win-loss.

The type of letters and the number of them in reach reel:
```
A: 2
B: 4
C: 6
D: 8
```
Out of these there will be 3 letters selected for each row and column which are displayed.


### How winning works
The rows which are accounted for are based on the number of rows you bet on, starting from the top.

If the rows which you bet on are all the same letters, you will receive "money"

The values are multiplied by the rarity of the letter displayed
```
A - x5
B - x4
C - x3
D - x2
```

## Try it out
1. Navigate to the ```output``` folder
2. Download the ```slotmachine.exe``` file and run.

# To compile
## Prerequisites
Command line tools  ```gcc``` and ```make``` have to be installed
## Commands
Run ```make``` in terminal
# To Run
Run ```./output/slotmachine``` in terminal