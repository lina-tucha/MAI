# Отчет по лабораторным работам №0-1 по машинному обучению.

## Выполнила: Хренникова Ангелина 

## Группа: М8О-308Б-19

### Часть 1: анализ датасета

Используемый датасет: Обнаружение сердечно-сосудистых заболеваний

Ссылка на датасет: https://www.kaggle.com/datasets/bhadaneeraj/cardio-vascular-disease-detection

Задача: Бинарная классификация

Датасет имеет такие характеристики, как: 

-id; 

-возраст в днях; 

-пол; 

-рост; 

-вес;

-физическая активность; 

-употребление алкоголя;

-курение; 

-уровень глюкозы; 

-уровень холестерина; 

-артериальное давление; 

-кровяное давление; 

-наличие сердечно-сосудистых заболеваний.

Датасет состоит из 69301 строк, не имеет пропущенных значений и категориальных признаков.

Данные занимают размер: float: 1.20 MB, int: 0.70 MB, object: 2.54 MB.

Количество уникальных значений для каждого параметра:

![image](https://user-images.githubusercontent.com/71285415/171066874-fc1e2dbe-acc1-4df6-b1ed-b645df51abb5.png)

Распределение значений:

![image](https://user-images.githubusercontent.com/71285415/171067037-60dae69d-350b-4ba1-8165-05e6e489cb7a.png)

![image](https://user-images.githubusercontent.com/71285415/171067057-41c71d75-d0ee-4123-a8f5-8a8cfe651ed4.png)

![image](https://user-images.githubusercontent.com/71285415/171157450-94e99779-4811-479b-b361-61098e16572d.png)

![image](https://user-images.githubusercontent.com/71285415/171157528-6ab28213-3365-4107-b528-b63a4ab9b1e4.png)

![image](https://user-images.githubusercontent.com/71285415/171157589-654bd1ef-ed9e-484a-b5c3-716b96eeeb9f.png)

![image](https://user-images.githubusercontent.com/71285415/171157650-815bba28-7d18-4f38-ba61-14ca4192d3f4.png)

![image](https://user-images.githubusercontent.com/71285415/171157737-523f698c-2bbb-41f4-94e8-62d91961c865.png)

![image](https://user-images.githubusercontent.com/71285415/171157804-4d9236e0-0199-4936-9bef-a9f005d2b68e.png)

![image](https://user-images.githubusercontent.com/71285415/171157875-6727d038-18b5-4592-acbb-74a5d11d2f71.png)

![image](https://user-images.githubusercontent.com/71285415/171157928-fd918b84-a01d-48c6-bf84-d84ecad5ea5c.png)

Зависимости:

![image](https://user-images.githubusercontent.com/71285415/171158067-5a4a3394-10bf-45d4-adb7-cfef87de410a.png)

Корреляция:

![image](https://user-images.githubusercontent.com/71285415/171158190-c41f42c1-4a0a-43b8-8ea6-6716e844b3ed.png)

![image](https://user-images.githubusercontent.com/71285415/171158267-d2dd4b6a-8e10-45f7-b59d-fe496107e221.png)

Соотношение классов:

![image](https://user-images.githubusercontent.com/71285415/171158334-f102c65a-97f9-45b1-a15c-44dc07dec879.png)

![image](https://user-images.githubusercontent.com/71285415/171158472-0ca2df3d-f7dc-428e-ab01-e9c5a4b6e7f1.png)

Данных достаточно много, классы сбалансированны, есть зависимости между сердечно-сосудистыми заболеваниями и другими показателями.

### Часть 2: реализация алгоритмов машинного обучения

#### KNN:

Моя реализаци:

![image](https://user-images.githubusercontent.com/71285415/171170177-e2bb069b-edbc-48c9-9b4f-0c9396f95c8c.png)

```python
Pipeline(steps=[('scaler', StandardScaler()), ('KNN', KNN(k=13))])
```

Коробочная:

![image](https://user-images.githubusercontent.com/71285415/171170572-9e5eea26-bca2-4fb3-a7c2-a7e4234c2672.png)

```python
Pipeline(steps=[('scaler', StandardScaler()), ('knn', KNeighborsClassifier(n_neighbors=13))])
```

#### Naive Bayes:

Моя реализация:

![image](https://user-images.githubusercontent.com/71285415/171170851-4f5eb02a-93a8-4a41-914e-06dcf60f7446.png)

Коробочная:

![image](https://user-images.githubusercontent.com/71285415/171170955-7d4813d0-648e-46f7-b59d-24d2c241e15d.png)

#### SVM:

Моя реализация:

![image](https://user-images.githubusercontent.com/71285415/171171164-1453ae65-7b03-4875-bc58-3166965589f6.png)

```python
Pipeline(steps=[('SVM', SVM(batch_size=10, epochs=10))])
```

Коробочная:

![image](https://user-images.githubusercontent.com/71285415/171171494-83701642-89b3-4b0e-93d4-cfafd1023736.png)

```python
Pipeline(steps=[('normalizer', Normalizer()), ('svm', SGDClassifier(eta0=0.1, learning_rate='constant'))])
```

#### Logistic Regression

Моя реализация:

![image](https://user-images.githubusercontent.com/71285415/171171720-23dc24af-15c1-4f89-b3a4-293c45e2e54b.png)

Коробочная:

![image](https://user-images.githubusercontent.com/71285415/171171787-b5d1a43d-c6b1-421d-9d00-972f67a46f05.png)













