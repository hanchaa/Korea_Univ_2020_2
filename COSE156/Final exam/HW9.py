import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

file = pd.read_excel("titanic.xlsx", engine="openpyxl")
titanic_list = pd.DataFrame(file)

titanic_size = titanic_list.pivot_table(index="who", columns="alive", aggfunc="size")
sns.heatmap(titanic_size, cmap=sns.light_palette('crimson', as_cmap=True), annot=True, fmt='d')

plt.show()
