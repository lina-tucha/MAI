# Сочувствую, если у вас практика с Семеновым.

### Управление виртуальной памятью

Небольшой гайд для тех, у кого Windows:

0. Установить VirtualBox: https://www.virtualbox.org/wiki/Downloads. Видео в помощь: https://www.youtube.com/watch?v=PilOxHmTx4I.
1. Скачать Ubuntu 16.04(18.04 - ... не подойдут): https://old-releases.ubuntu.com/releases/16.04.2/. 
   ![image](https://user-images.githubusercontent.com/71285415/125404841-c9460500-e3bf-11eb-95d7-5d61f9087e07.png)
2. Установить Ubuntu на VB и создать общую папку с Windows: https://www.youtube.com/watch?v=vY9QNwX_IsY&t=1087s.
3. Ввести команды:
   - sudo apt-get install nasm qemu cgdb make gcc
   - sudo apt-get update && sudo apt-get upgrade
   - sudo grub-install /dev/sda
   - sudo apt-get install grub
   - sudo apt-get install qemu
4. Создать файл “.gdbinit” с содержанием “set auto-load safe-path /” в пааке с проектом.
5. Проверить makefile в папке с проектом(нам дали нерабочий). Заменить 10p на 9p.
6. Запустить проект: 
   - sudo make compile
   - sudo make image
   - sudo make
   - bash run_qemu.sh   

По самой работе:

8. Готовые модули по некоторым темам можно взять здесь: http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html.
9. Любимая схема Семенова: https://makelinux.github.io/kernel/map/.
10. Работу с флешкой можно не проводить, он не проверит.
11. Самое главное - это схема и алгоритм к ней. Они должны быть максимально подробными. 
12. Нужно ходить на каждую консультацию и мучать его, точнее терпеть, как он мучает вас.
13. При сдаче говорить уверенно и без пауз, чтобы он не успел вставить и слова. Просто закидывать его информацией по теме. Всегда знать, как это сделано в linux.  
14. Будет просить объяснить что-то и говорить, что не понимает. И так раз 10.
15. К первым командам сильно докапывается.
