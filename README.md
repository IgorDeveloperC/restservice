# restservice
This solving task for testing skills

Folder x64 contains binary files and lib.
Folder Linux contains binary file. 
For Run this service in unix you need the install library:

$ sudo apt-get install libcpprest-dev

Folder test contains project VS. 2022 with source files.

Instruction(Rus)
Запуск сервиса:
Windows:
В папке x64 находится бинарный файл и библиотека.
Запуск происходит через командную строку с обязательным условием передачи
параметров, первы параметр - это количество потоков, второй - это максимальная размер кэша
(examl.test.exe 5 2)

Linux:
Для линукс требуется установка библиотеки libcpprest-dev.
После установки, запустить файл из папки Linux - restserver,
с параметрами, как в случае с windows.(examl. ./restserver 5 2)

Тестирование проводилось через postman.
Для тестирования необходимо запустить сервис через командную строку с параметрами.
При успешном запуске в консоль будет выведено сообщение:

Listening for requests at: http://127.0.0.1:8080/
Press ENTER to exit.  

Адрес и порт установлены и изменить их нельзя.
В случае запуска без необходимого количества параметров, будет выведено сообщение:

Please restart service with parameters: threads count, max cache capacity

и программа завершится.

Сервис согласно заданию обрабатывает два типа запросов GET и POST.
GET запрос формируется через имя и значение аргумента.
Во вкладке Param программы Postman пишем ключевое слово "key" как имя аргумента(поле key)
В поле value пишем значение ключа, который мы хотим найти.
В случае отсутствия ключа в кэше, будет возращено значение -1 в формате json.

POST запрос формируется в формате json. В postman выбираем тип запроса POST, во вкладке "body"
выбираем тип "raw" и правее меняем тип на json. Тело выглядит следующим образом:
{
	"key":key_value, "value":value
}
Example:
{
	"key": 10, "value" : 12
}
Что соответсвует запросу key=10, value=12. После отправки запроса при успешном добавлении в кэш будет 
возращено body  в текстовом формате с сообщением:

Added key and value to cache

и статус код 200. В противном случае вернёт статус код 400 Bad Request.

 

