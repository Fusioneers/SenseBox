# Laborbuch AI

## Struktur

In Folgendem sind alle Models aufgeführt, die wir für die SenseBox AI getestet
und trainiert haben. Es wird zuerst die Architektur des Models, d.h. die
Kombination der Layer, aufgeführt. Dann folgt die durchschnittliche Abweichung
der vorhergesagten Höhen von den Testdaten, und anschließend eine Grafik,
in der das Model auf das Datenset 'Fahrt' angewandt wird.

## Model 0

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

24.566537857055664m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![0.png](Laborbuch-AI-assets/0.png)

## Model 1

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

151.09603881835938m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![1.png](Laborbuch-AI-assets/1.png)

## Model 2

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

50.0474739074707m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![38.png](Laborbuch-AI-assets/2.png)

## Model 3

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 20)                100       
                                                                 
 dense_1 (Dense)             (None, 15)                315       
                                                                 
 dense_2 (Dense)             (None, 10)                160       
                                                                 
 dense_3 (Dense)             (None, 5)                 55        
                                                                 
 dense_4 (Dense)             (None, 1)                 6         
                                                                 
=================================================================
Total params: 636
Trainable params: 636
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

7.441730976104736m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![3.png](Laborbuch-AI-assets/3.png)

## Model 4

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 4)                 20        
                                                                 
 dense_1 (Dense)             (None, 4)                 20        
                                                                 
 dropout (Dropout)           (None, 4)                 0         
                                                                 
 dense_2 (Dense)             (None, 4)                 20        
                                                                 
 dense_3 (Dense)             (None, 1)                 5         
                                                                 
=================================================================
Total params: 65
Trainable params: 65
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

52.309898376464844m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![36.png](Laborbuch-AI-assets/4.png)

## Model 5

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

40.42742156982422m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![5.png](Laborbuch-AI-assets/5.png)

## Model 6

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

29.35040855407715m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![6.png](Laborbuch-AI-assets/6.png)

## Model 7

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

84.46340942382812m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![7.png](Laborbuch-AI-assets/7.png)

## Model 8

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

23.120187759399414m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![8.png](Laborbuch-AI-assets/8.png)

## Model 9

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

35.41854476928711m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![9.png](Laborbuch-AI-assets/9.png)

## Model 10

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

28.894609451293945m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![34.png](Laborbuch-AI-assets/10.png)

## Model 11

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

33.355709075927734m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![11.png](Laborbuch-AI-assets/11.png)

## Model 12

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

131.80239868164062m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![33.png](Laborbuch-AI-assets/12.png)

## Model 13

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

57.701053619384766m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![13.png](Laborbuch-AI-assets/13.png)

## Model 14

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

4.113324165344238m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![14.png](Laborbuch-AI-assets/14.png)

## Model 15

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 1)                 5         
                                                                 
=================================================================
Total params: 5
Trainable params: 5
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

194.7505645751953m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![15.png](Laborbuch-AI-assets/15.png)

## Model 16

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

46.39529037475586m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![32.png](Laborbuch-AI-assets/16.png)

## Model 17

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

30.151086807250977m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![17.png](Laborbuch-AI-assets/17.png)

## Model 18

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

10.006917953491211m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![18.png](Laborbuch-AI-assets/18.png)

## Model 19

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

31.255023956298828m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![19.png](Laborbuch-AI-assets/19.png)

## Model 20

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 5)                 25        
                                                                 
 dense_1 (Dense)             (None, 5)                 30        
                                                                 
 dense_2 (Dense)             (None, 5)                 30        
                                                                 
 dense_3 (Dense)             (None, 5)                 30        
                                                                 
 dense_4 (Dense)             (None, 1)                 6         
                                                                 
=================================================================
Total params: 121
Trainable params: 121
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

27.600261688232422m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![20.png](Laborbuch-AI-assets/20.png)

## Model 21

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 4)                 20        
                                                                 
 dense_1 (Dense)             (None, 4)                 20        
                                                                 
 dense_2 (Dense)             (None, 4)                 20        
                                                                 
 dense_3 (Dense)             (None, 4)                 20        
                                                                 
 dense_4 (Dense)             (None, 4)                 20        
                                                                 
 dense_5 (Dense)             (None, 1)                 5         
                                                                 
=================================================================
Total params: 105
Trainable params: 105
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

17.21582794189453m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![31.png](Laborbuch-AI-assets/21.png)

## Model 22

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

8.943251609802246m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![22.png](Laborbuch-AI-assets/22.png)

## Model 23

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

218.78134155273438m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![23.png](Laborbuch-AI-assets/23.png)

## Model 24

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

33.779266357421875m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![24.png](Laborbuch-AI-assets/24.png)

## Model 25

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 10)                110       
                                                                 
 dense_5 (Dense)             (None, 10)                110       
                                                                 
 dense_6 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 611
Trainable params: 611
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

9.034212112426758m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![30.png](Laborbuch-AI-assets/25.png)

## Model 26

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dropout (Dropout)           (None, 10)                0         
                                                                 
 batch_normalization (BatchN  (None, 10)               40        
 ormalization)                                                   
                                                                 
 activation (Activation)     (None, 10)                0         
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dropout_1 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_1 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_1 (Activation)   (None, 10)                0         
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dropout_2 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_2 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_2 (Activation)   (None, 10)                0         
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dropout_3 (Dropout)         (None, 10)                0         
                                                                 
 batch_normalization_3 (Batc  (None, 10)               40        
 hNormalization)                                                 
                                                                 
 activation_3 (Activation)   (None, 10)                0         
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 551
Trainable params: 471
Non-trainable params: 80
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

41.790836334228516m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![29.png](Laborbuch-AI-assets/26.png)

## Model 27

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 30)                150       
                                                                 
 dense_1 (Dense)             (None, 30)                930       
                                                                 
 dense_2 (Dense)             (None, 30)                930       
                                                                 
 dense_3 (Dense)             (None, 1)                 31        
                                                                 
=================================================================
Total params: 2,041
Trainable params: 2,041
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

6.168951034545898m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![27.png](Laborbuch-AI-assets/27.png)

## Model 28

### Model Architektur

```
Model: "sequential"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 dense (Dense)               (None, 10)                50        
                                                                 
 dense_1 (Dense)             (None, 10)                110       
                                                                 
 dense_2 (Dense)             (None, 10)                110       
                                                                 
 dense_3 (Dense)             (None, 10)                110       
                                                                 
 dense_4 (Dense)             (None, 1)                 11        
                                                                 
=================================================================
Total params: 391
Trainable params: 391
Non-trainable params: 0
_________________________________________________________________

```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

11.27298641204834m

### Daten 2022-05-03-0004-VG mit Model ausgewertet

![28.png](Laborbuch-AI-assets/28.png)
