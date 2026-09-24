Открывать сайт Doxygen через:
```sh
open docs/html/index.html
```

Обновление сайта Doxygen:
```sh
doxygen Doxyfile
```

Проверка что Doxygen нашёл нужные файлы:
```sh
doxygen Doxyfile 2>&1 | grep -i "parsing"
```

Проверка что получилось:
```sh
grep '^INPUT' Doxyfile
```
