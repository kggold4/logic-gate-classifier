# Systems praogramming with C++ - Assignments 2

### <i> By Kfir Goldfarb </i>

This assignment is to implement a 2D messegeboard class called Board

## How to use:

### creating a board:
```ariel::Board board;```

the board class have 3 main methods:
1. ```post```
2. ```read```
3. ```show```

### post:
<i> posting a text on the messegeboard: </i>

for example:


```board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");```


```board.post(/*row=*/99, /*column=*/202, Direction::Vertical, "xyz");```


the results:


```
98:  _________
99:  ____x____
100: __abyd___
101: ____z____
102: _________
```

### read:
<i> reading a text from the messeageboard: </i>

for example:


```cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/6) << endl;```


the results:


```
"abyd__"
```

### show:
<i> will print the all borad </i>

for example:


```board.show();```


the results:


```
98:  _________
99:  ____x____
100: __abyd___
101: ____z____
102: _________
```