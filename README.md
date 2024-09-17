# ImageProcessor v1.0.0 — Простейший инструмент для цветовой обработки изображения на чистом Qt C++
- Это приложение разрабатывается как песочница для тестирования и изучения алгоритмов обработки растровых данных.
- На сентябрь 2024 реализованы методы изменения экспозиции изображения (exposure), светлых участков (highlights), теней (shadows),
  температуры (temperature), оттенка(tint), уровня размытия (blur).
- Repo также содержит папку "testImages" с изображениями для тестирования работы приложения
# Как использовать приложение
1) После запуская приложения нажмите кнопку "Open" и выберите изображение (*.png, *jpeg).
  	- Для лучшей работы приложения рекомендуется использовать небольшие изображения (до 5000px) или же сразу изменить масштаб на более мелкий
2) Сразу после успешного открытия изображения станут доступны элементы навигации и слайдеры.
  	- Для перемещения по холсту используйте WASD, для изменения масштаба изображения используйте кнопки "+" и "-"
  	- Слайдер можно вернуть в исходное значение с помощью двойного клика мышью (почти)
	- Чем больше масштаб - тем больше ресурсов и времени будет уходить на отрисовку.
	- Навигация WASD работает на двух раскладках (en/ru)
3) После настройки изображения его можно будет сохранить посредством нажатия на кнопку "Save".
	- На данный момент поддерживается сохранение только в формате .png.
# Что дальше?
- Необходимо переделать текущую реализацию отрисовки и расчета изображения. Текущая реализация жестко связывает уровень масштаба и время обработки
изображения (чем больше зум - тем больше ресурсов требуется), что указывает на неверную логику построения процесса расчета и отрисовки.
- Текущий алгоритм размытия слишком медлителен, его стоит заменить на более оптимальный, например на размытие по Гауссу (также оно визуально приятнее).
- В скором будущем будут добавлены другие алгоритмы обработки изображения (усиление резкости, реализация "уровней" rgb каналов [как в photoshop] через слайдеры)
  
![Screenshot 2024-09-17 105503](https://github.com/user-attachments/assets/22c32f89-a3f7-40c8-96ac-bcc6cf041c0b)
