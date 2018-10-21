#
## 第2章

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





