* isspace
```
C 库函数 int isspace(int c) 检查所传的字符是否是空白字符。

标准的空白字符包括：

' '     (0x20)    space (SPC) 空格符
'\t'    (0x09)    horizontal tab (TAB) 水平制表符    
'\n'    (0x0a)    newline (LF) 换行符
'\v'    (0x0b)    vertical tab (VT) 垂直制表符
'\f'    (0x0c)    feed (FF) 换页符
'\r'    (0x0d)    carriage return (CR) 回车符

参数
c -- 这是要检查的字符。
返回值
如果 c 是一个空白字符，则该函数返回非零值（true），否则返回 0（false）。

```

* strnmp
```
描述
C 库函数 int strncmp(const char *str1, const char *str2, size_t n) 把 str1 和 str2 进行比较，最多比较前 n 个字节。

声明
下面是 strncmp() 函数的声明。

int strncmp(const char *str1, const char *str2, size_t n)
参数
str1 -- 要进行比较的第一个字符串。
str2 -- 要进行比较的第二个字符串。
n -- 要比较的最大字符数。
返回值
该函数返回值如下：

如果返回值 < 0，则表示 str1 小于 str2。
如果返回值 > 0，则表示 str1 大于 str2。
如果返回值 = 0，则表示 str1 等于 str2。
```
