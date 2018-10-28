# coding: utf-8

import warnings
warnings.filterwarnings('ignore')

## 保存したモデルでテストをする
# Kerasのコンポーネント
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPooling2D
from keras.utils import np_utils
from keras.models import load_model

# Sckit-learn, Pandas, Numpy, matplotlib
from sklearn.datasets import fetch_mldata
#import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt


# ## モデルを読み込む
model = load_model('emo.h5')

# 保存した画像を読み込む
from PIL import Image
from PIL import ImageOps

size = 48


# mnistデータは0が白，255が黒なので反転したりしてる
img = Image.open("./unko.jpg", 'r')
img = img.convert("L")
img = img.resize((size, size))

plt.imshow(img)
plt.show()

data = np.array(img)

# [0, 1]に変換
data = data.astype('float32')
data = data/255.0
print(data)
print(type(data))
print(data.shape)

# ## 読み込んだ画像でテスト
# ネットワーク入力の形に合わせる
data = data.reshape(1, size, size, 1)

pred = model.predict_classes(data)

emo = ["Neutral", "Angry", "Fear", "Happy", "Sadness", "Surprise"]
print(pred, emo[pred[0]])

