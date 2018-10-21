print("\tPython")
print("Languages:\nPython\nC\nJavaScript")
print("Languages:\n\tPython\n\tC\n\tJavaScript")

favorite_language = ' python '
print(favorite_language)
print(favorite_language.rstrip()) #删除末尾的空白符
print(favorite_language)
print(favorite_language.lstrip()) #删除开头的空白符
print(favorite_language.strip())  # 删除两端的空白符
favorite_language = favorite_language.lstrip()
print(favorite_language)

"""output
        Python
Languages:
Python
C
JavaScript
Languages:
        Python
        C
        JavaScript
 python
 python
 python
python
python
python
"""