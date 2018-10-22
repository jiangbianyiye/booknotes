#
## 第 2 章 变量和简单数据类型

### 2.2 变量

声明 VARIABLE_NAME = SOMETHING

变量名使用错误时会报错

```python
Traceback (most recent call last):
  File "hello_world.py", line 2, in <module>
  print(mesage)
  NameError: name 'mesage' is not defined
```

### 2.3 字符串

""、''号括起来的都是字符串

```python
"This is a string."
'This is also a string.'


message = 'One of Python's strengths is its diverse community.'
						^
SyntaxError: invalid syntax
```

混用时

```python
print('I told my friend, "Python is my favorite language!"')
print("The language 'Python' is named after Monty Python, not the snake.")
print("One of Python's strengths is its diverse and supportive community.")

"""output:
I told my friend, "Python is my favorite language!"
The language 'Python' is named after Monty Python, not the snake.
One of Python's strengths is its diverse and supportive community.
"""
```

修改字符串

```python
name = "ada lovelace"
print(name.title()) # 以首字母大写方式显示每个单词
print(name.upper()) # 全部字母大写
print(name.lower()) # 全部字母小写

"""output:
Ada Lovelace
ADA LOVELACE
ada lovelace
"""
```

拼接字符串

```python
first_name = "ada"
last_name = "lovelace"
# 使用 + 号拼接字符
full_name = first_name + " " + last_name
print(full_name)

message = "Hello, " + full_name.title() + "!"
print(message)

"""output:
ada lovelace
Hello, Ada Lovelace!
"""
```

空白符，制表符：\t，换行符：\n

### 2.4数字

整数、浮点数，加（+）减（-）乘（*）除（/）及其运算优先级

乘方（**）：

```
>>> 2 + 3
5
>>> 3 - 2
1
>>> 2 * 3
6
>>> 3 / 2
1.5
>>> 3 ** 3
27
>>> 10 ** 6
1000000
>>> 3 * 2 ** 2
12
>>> 0.2 + 0.1
0.30000000000000004
>>> 3 * 0.1
0.30000000000000004
```

str()将非字符串表示为字符串

```python
age = 23
message = "Happy " + str(age) + "rd Birthday!"
print(message)

"""output:
Happy 23rd Birthday!
"""
```

python2中的整数除法

```python
>>> 3 / 2
1
>>> 3.0 / 2
1.5
>>> 3 / 2.0
1.5
>>> 3.0 / 2.0
1.5
```

### 2.5注释

```python
# 单行注释

```



## 第 3 章 列表简介

### 3.1 列表是什么





